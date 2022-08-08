# Web port analysis

## Strength reduction
Nor JS nor TS wil perform strength reduction

### VanillaJS
```js
const BIT_NOISE1 = 0xB5297A4D;
const BIT_NOISE2 = 0x68E31DA4;
const BIT_NOISE3 = 0x1B56C4E9;
const CAP = 1 << 32;

function squirrel(x, seed) {
  let mangled = x;
  mangled *= BIT_NOISE1;
  mangled += seed;
  mangled ^= (mangled >> 8);
  mangled += BIT_NOISE2;
  mangled ^= (mangled << 8);
  mangled *= BIT_NOISE3;
  mangled ^= (mangled >> 8);
  return mangled;
}

function squirrel1(x) {
 let a = squirrel(x, 4);
 return a % CAP;
}

function squirrel2(x) {
 let a = squirrel(x, 4);
 return a & (CAP - 1);
}
```
bench: https://jsbench.me/opl6hz8m8l/1

so chrome engine won't perform `strength reduction` according to the performance
gap.

### TypeScript

```ts
const CAP : number = 1 << 32;
function slow(n: number): number {
    return n % CAP;
}
function fast(n: number): number {
    return n & (CAP - 1);
}
```

generated JS
```js
"use strict";
const CAP = 1 << 32;
function slow(n) {
    return n % CAP;
}
function fast(n) {
    return n & (CAP - 1);
}
```

### Assembly Script

Assembly script implementation
```ts
export function slow(x: u32): u32 {
 let a: u64 = squirrel(x, 4);
 return u32(a % CAP);
}

export function fast(x: u32): u32 {
 let a: u64 = squirrel(x, 4);
 return u32(a & (CAP - 1));
}

const BIT_NOISE1: u32 = 0xB5297A4D;
const BIT_NOISE2: u32 = 0x68E31DA4;
const BIT_NOISE3: u32 = 0x1B56C4E9;
const CAP: u64 = 1 << 32;

function squirrel(x: u32, seed: u32): u64 {
  let mangled: u64 = x;
  mangled *= BIT_NOISE1;
  mangled += seed;
  mangled ^= (mangled >> 8);
  mangled += BIT_NOISE2;
  mangled ^= (mangled << 8);
  mangled *= BIT_NOISE3;
  mangled ^= (mangled >> 8);
  
  return mangled;
}
```

generated wat:
```js
;; INFO asc module.ts --textFile module.wat --outFile module.wasm --bindings raw -O3 --runtime stub
(module
 (type $i32_=>_i32 (func (param i32) (result i32)))
 (memory $0 0)
 (export "slow" (func $module/slow))
 (export "fast" (func $module/slow))
 (export "memory" (memory $0))
 (func $module/slow (param $0 i32) (result i32)
  (local $1 i64)
  local.get $0
  i64.extend_i32_u
  i64.const 3039394381
  i64.mul
  i64.const 4
  i64.add
  local.tee $1
  local.get $1
  i64.const 8
  i64.shr_u
  i64.xor
  i64.const 1759714724
  i64.add
  local.tee $1
  local.get $1
  i64.const 8
  i64.shl
  i64.xor
  i64.const 458671337
  i64.mul
  local.tee $1
  local.get $1
  i64.const 8
  i64.shr_u
  i64.xor
  i64.const 4294967295
  i64.and
  i32.wrap_i64
 )
)
```

ref: https://www.assemblyscript.org/editor.html#IyFvcHRpbWl6ZT1zcGVlZCZydW50aW1lPXN0dWIKZXhwb3J0IGZ1bmN0aW9uIHNsb3coeDogdTMyKTogdTMyIHsKIGxldCBhOiB1NjQgPSBzcXVpcnJlbCh4LCA0KTsKIHJldHVybiB1MzIoYSAlIENBUCk7Cn0KCmV4cG9ydCBmdW5jdGlvbiBmYXN0KHg6IHUzMik6IHUzMiB7CiBsZXQgYTogdTY0ID0gc3F1aXJyZWwoeCwgNCk7CiByZXR1cm4gdTMyKGEgJiAoQ0FQIC0gMSkpOwp9Cgpjb25zdCBCSVRfTk9JU0UxOiB1MzIgPSAweEI1Mjk3QTREOwpjb25zdCBCSVRfTk9JU0UyOiB1MzIgPSAweDY4RTMxREE0Owpjb25zdCBCSVRfTk9JU0UzOiB1MzIgPSAweDFCNTZDNEU5Owpjb25zdCBDQVA6IHU2NCA9IDEgPDwgMzI7CgpmdW5jdGlvbiBzcXVpcnJlbCh4OiB1MzIsIHNlZWQ6IHUzMik6IHU2NCB7CiAgbGV0IG1hbmdsZWQ6IHU2NCA9IHg7CiAgbWFuZ2xlZCAqPSBCSVRfTk9JU0UxOwogIG1hbmdsZWQgKz0gc2VlZDsKICBtYW5nbGVkIF49IChtYW5nbGVkID4+IDgpOwogIG1hbmdsZWQgKz0gQklUX05PSVNFMjsKICBtYW5nbGVkIF49IChtYW5nbGVkIDw8IDgpOwogIG1hbmdsZWQgKj0gQklUX05PSVNFMzsKICBtYW5nbGVkIF49IChtYW5nbGVkID4+IDgpOwogIAogIHJldHVybiBtYW5nbGVkOwp9CiMhaHRtbAo8dGV4dGFyZWEgaWQ9Im91dHB1dCIgc3R5bGU9ImhlaWdodDogMTAwJTsgd2lkdGg6IDEwMCUiIHJlYWRvbmx5PjwvdGV4dGFyZWE+CjxzY3JpcHQgdHlwZT0ibW9kdWxlIj4KY29uc3QgZXhwb3J0cyA9IGF3YWl0IGluc3RhbnRpYXRlKGF3YWl0IGNvbXBpbGUoKSwgeyAvKiBpbXBvcnRzICovIH0pCmNvbnN0IG91dHB1dCA9IGRvY3VtZW50LmdldEVsZW1lbnRCeUlkKCdvdXRwdXQnKQpmb3IgKGxldCBpID0gMDsgaSA8PSAxMDA7ICsraSkgewogIG91dHB1dC52YWx1ZSArPSBgc2xvdygke2l9KSA9ICR7ZXhwb3J0cy5zbG93KGkpfVxuYDsKICBvdXRwdXQudmFsdWUgKz0gYGZhc3QoJHtpfSkgPSAke2V4cG9ydHMuZmFzdChpKX1cbmAKfQo8L3NjcmlwdD4=
