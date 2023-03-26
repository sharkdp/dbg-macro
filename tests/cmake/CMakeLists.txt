# This is a sample project to test integration via add_subdirectory and CMakeConfig
cmake_minimum_required(VERSION 3.12)

project(dbg_macro-cmake)

# the dbg_macroTarget.cmake file that specifies
#  where to find all of the libraries and headers
#  is not written until install time (so that the targets file
#  can have the full paths). This means, testing whether fire
#  can be loaded by another CMake project cannot be folded into ctest
#  or (more accurately) should NOT be folded into ctest
find_package(dbg_macro REQUIRED)

add_executable(${PROJECT_NAME}-demo demo.cpp)
target_link_libraries(${PROJECT_NAME}-demo PRIVATE dbg_macro)
