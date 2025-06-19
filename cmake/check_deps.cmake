# Check dependencies

if(NOT TARGET absl::base)
  message(FATAL_ERROR "Target absl::base not available.")
endif()

if(NOT TARGET re2::re2)
  message(FATAL_ERROR "Target re2::re2 not available.")
endif()

# CXX Test
if(BUILD_TESTING)
  if(NOT TARGET GTest::gtest_main)
    message(FATAL_ERROR "Target GTest::gtest_main not available.")
  endif()
endif()
