add_library(squirrel3)
target_sources(squirrel3
  PRIVATE
    include/squirrel3/squirrel3.hpp
    src/squirrel3.cpp)
target_include_directories(squirrel3
  PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>)
target_compile_features(squirrel3 PUBLIC cxx_std_17)
set_target_properties(squirrel3 PROPERTIES
  VERSION ${PROJECT_VERSION}
  PUBLIC_HEADER include/squirrel3/squirrel3.hpp)
#target_link_libraries(Foo PUBLIC ...)
add_library(${PROJECT_NAMESPACE}::squirrel3 ALIAS squirrel3)

add_subdirectory(tests)

# Install
install(TARGETS squirrel3
  EXPORT ${PROJECT_NAME}Targets
  PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/squirrel3
  )
