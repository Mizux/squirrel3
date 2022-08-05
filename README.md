Github-CI:<br>
[![Build Status][github_linux_status]][github_linux_link]
[![Build Status][github_macos_status]][github_macos_link]
[![Build Status][github_windows_status]][github_windows_link]<br>
[![Build Status][github_amd64_docker_status]][github_amd64_docker_link]
[![Build Status][github_aarch64_docker_status]][github_aarch64_docker_link]

[github_linux_status]: https://github.com/Mizux/squirrel3/actions/workflows/amd64_linux.yml/badge.svg
[github_linux_link]: https://github.com/Mizux/squirrel3/actions/workflows/amd64_linux.yml
[github_macos_status]: https://github.com/Mizux/squirrel3/actions/workflows/amd64_macos.yml/badge.svg
[github_macos_link]: https://github.com/Mizux/squirrel3/actions/workflows/amd64_macos.yml
[github_windows_status]: https://github.com/Mizux/squirrel3/actions/workflows/amd64_windows.yml/badge.svg
[github_windows_link]: https://github.com/Mizux/squirrel3/actions/workflows/amd64_windows.yml
[github_amd64_docker_status]: https://github.com/Mizux/squirrel3/actions/workflows/amd64_docker.yml/badge.svg
[github_amd64_docker_link]: https://github.com/Mizux/squirrel3/actions/workflows/amd64_docker.yml
[github_aarch64_docker_status]: https://github.com/Mizux/squirrel3/actions/workflows/aarch64_docker.yml/badge.svg
[github_aarch64_docker_link]: https://github.com/Mizux/squirrel3/actions/workflows/aarch64_docker.yml

# Introduction
<nav for="project"> |
<a href="#requirement">Requirement</a> |
<a href="#codemap">Codemap</a> |
<a href="#build">Build</a> |
<a href="ci/README.md">CI</a> |
<a href="#appendices">Appendices</a> |
<a href="#license">License</a> |
</nav>

This is an example of how to create a Modern [CMake](https://cmake.org/) C++ Project.

This project should run on GNU/Linux, MacOS and Windows.

## Requirement
You'll need:

* "CMake >= 3.16".

## Codemap
The project layout is as follow:

* [CMakeLists.txt](CMakeLists.txt) Top-level for [CMake](https://cmake.org/cmake/help/latest/) based build.
* [cmake](cmake) Subsidiary CMake files.

* [ci](ci) Root directory for continuous integration.

* [squirrel3](squirrel3) Root directory for `squirrel3` library.
  * [CMakeLists.txt](squirrel3/CMakeLists.txt) for `squirrel3`.
  * [include](squirrel3/include) public folder.
    * [squirrel3](squirrel3/include/squirrel3)
      * [squirrel3.hpp](squirrel3/include/squirrel3/squirrel3.hpp)
  * [src](squirrel3/src) private folder.
    * [src/squirrel3.cpp](squirrel3/src/squirrel3.cpp)

## Build
To build the C++ project, as usual:
```sh
cmake -S. -Bbuild -DCMAKE_BUILD_TYPE=Release
cmake --build build --config Release
```

## Appendices
Few links on the subject...

### Resources
Project layout:
* The Pitchfork Layout Revision 1 (cxx-pflR1)

CMake:
* https://llvm.org/docs/CMakePrimer.html
* https://cliutils.gitlab.io/modern-cmake/
* https://cgold.readthedocs.io/en/latest/

### Misc
Image has been generated using [plantuml](http://plantuml.com/):
```bash
plantuml -Tsvg docs/{file}.dot
```
So you can find the dot source files in [docs](docs).

## License
Apache 2. See the LICENSE file for details.

## Disclaimer
This is not an official Google product, it is just code that happens to be
owned by Google.

