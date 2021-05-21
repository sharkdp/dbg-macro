cmake_minimum_required(VERSION 3.1)

project(dbg_macro)

# Required to force MSVC to set __cplusplus to the correct value
# https://devblogs.microsoft.com/cppblog/msvc-now-correctly-reports-__cplusplus/
set(msvc_flags "/Zc:__cplusplus;-W4;")
set(gcc_like_flags "-Wall;-pedantic;")
add_compile_options("$<IF:$<CXX_COMPILER_ID:MSVC>,${msvc_flags},${gcc_like_flags}>")

include(GNUInstallDirs)

string(COMPARE EQUAL ${CMAKE_CURRENT_SOURCE_DIR} ${CMAKE_SOURCE_DIR} IS_MAIN_PROJECT)
option(DBG_MACRO_ENABLE_TESTS "Enable tests." ${IS_MAIN_PROJECT})

add_library(${PROJECT_NAME} INTERFACE)
target_include_directories(${PROJECT_NAME}
  INTERFACE
    $<BUILD_INTERFACE:${${PROJECT_NAME}_SOURCE_DIR}>
    $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
)

if (DBG_MACRO_ENABLE_TESTS)
    find_package(Catch2 CONFIG)
    if(NOT Catch2_FOUND)
        add_subdirectory(tests/Catch2)
        list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_LIST_DIR}/tests/Catch2/contrib)
    endif()

    include(CTest)
    include(Catch)

    # unit tests with dbg(...) enabled
    add_executable(${PROJECT_NAME}-tests tests/main.cpp tests/basic.cpp)
    target_compile_options(${PROJECT_NAME}-tests PRIVATE -DDBG_MACRO_NO_WARNING)
    target_link_libraries(${PROJECT_NAME}-tests ${PROJECT_NAME} Catch2::Catch2)
    catch_discover_tests(${PROJECT_NAME}-tests)

    # unit tests with dbg(...) disabled
    add_executable(${PROJECT_NAME}-tests-macro_disabled tests/main.cpp tests/basic.cpp)
    target_compile_options(${PROJECT_NAME}-tests-macro_disabled PRIVATE -DDBG_MACRO_NO_WARNING -DDBG_MACRO_DISABLE)
    target_link_libraries(${PROJECT_NAME}-tests-macro_disabled ${PROJECT_NAME} Catch2::Catch2)
    catch_discover_tests(${PROJECT_NAME}-tests-macro_disabled)

    # dbg(…) example file
    add_executable(${PROJECT_NAME}-example tests/example.cpp)
    target_compile_options(${PROJECT_NAME}-example PRIVATE -DDBG_MACRO_NO_WARNING)
    target_link_libraries(${PROJECT_NAME}-example ${PROJECT_NAME})

    # dbg(…) demo file
    add_executable(${PROJECT_NAME}-demo tests/demo.cpp)
    target_compile_options(${PROJECT_NAME}-demo PRIVATE -DDBG_MACRO_NO_WARNING)
    target_link_libraries(${PROJECT_NAME}-demo ${PROJECT_NAME})
    add_test(${PROJECT_NAME}-demo ${PROJECT_NAME}-demo)
endif()

set(target dbg_macro)

# install the target and create export-set
install(TARGETS ${target}
  EXPORT ${target}Targets
  LIBRARY DESTINATION lib
  ARCHIVE DESTINATION lib
  RUNTIME DESTINATION bin
  INCLUDES DESTINATION include
)

# install header file
install(FILES dbg.h DESTINATION include)

# generate and install export file
install(EXPORT ${target}Targets
  FILE ${target}Targets.cmake
  NAMESPACE ${target}::
  DESTINATION lib/cmake/${target}
)

# include CMakePackageConfigHelpers macro
include(CMakePackageConfigHelpers)

# set version
set(version 0.4.0)

set_property(TARGET ${target} PROPERTY VERSION ${version})
set_property(TARGET ${target} PROPERTY SOVERSION 0)
set_property(TARGET ${target} PROPERTY
  INTERFACE_${target}_MAJOR_VERSION 0)
set_property(TARGET ${target} APPEND PROPERTY
  COMPATIBLE_INTERFACE_STRING ${target}_MAJOR_VERSION
)

# generate the version file for the config file
write_basic_package_version_file(
  "${CMAKE_CURRENT_BINARY_DIR}/${target}ConfigVersion.cmake"
  VERSION "${version}"
  COMPATIBILITY AnyNewerVersion
)

# create config file
configure_package_config_file(${CMAKE_CURRENT_SOURCE_DIR}/cmake/${target}Config.cmake.in
  "${CMAKE_CURRENT_BINARY_DIR}/${target}Config.cmake"
  INSTALL_DESTINATION lib/cmake/${target}
)

# install config files
install(FILES
  "${CMAKE_CURRENT_BINARY_DIR}/${target}Config.cmake"
  "${CMAKE_CURRENT_BINARY_DIR}/${target}ConfigVersion.cmake"
  DESTINATION lib/cmake/${target}
)

# generate the export targets for the build tree
export(EXPORT ${target}Targets
  FILE "${CMAKE_CURRENT_BINARY_DIR}/cmake/${target}Targets.cmake"
  NAMESPACE ${target}::
)
