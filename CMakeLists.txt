cmake_minimum_required(VERSION 3.1)

project(dbg_macro)

string(COMPARE EQUAL ${CMAKE_CURRENT_SOURCE_DIR} ${CMAKE_SOURCE_DIR} IS_MAIN_PROJECT)
option(DBG_MACRO_ENABLE_TESTS "Enable tests." ${IS_MAIN_PROJECT})

add_library(${PROJECT_NAME} INTERFACE)
target_include_directories(${PROJECT_NAME} INTERFACE ".")

if (DBG_MACRO_ENABLE_TESTS)
    add_subdirectory(tests/Catch2)
    list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_LIST_DIR}/tests/Catch2/contrib)

    include(CTest)
    include(Catch)

    # unit tests with dbg(...) enabled
    add_executable(${PROJECT_NAME}-tests tests/main.cpp tests/basic.cpp)
    target_compile_options(${PROJECT_NAME}-tests PRIVATE -Wall -pedantic -DDBG_MACRO_NO_WARNING)
    target_link_libraries(${PROJECT_NAME}-tests ${PROJECT_NAME} Catch2::Catch2)
    catch_discover_tests(${PROJECT_NAME}-tests)

    # unit tests with dbg(...) disabled
    add_executable(${PROJECT_NAME}-tests-macro_disabled tests/main.cpp tests/basic.cpp)
    target_compile_options(${PROJECT_NAME}-tests-macro_disabled PRIVATE -Wall -pedantic -DDBG_MACRO_NO_WARNING -DDBG_MACRO_DISABLE)
    target_link_libraries(${PROJECT_NAME}-tests-macro_disabled ${PROJECT_NAME} Catch2::Catch2)
    catch_discover_tests(${PROJECT_NAME}-tests-macro_disabled)

    # dbg(…) example file
    add_executable(${PROJECT_NAME}-example tests/example.cpp)
    target_compile_options(${PROJECT_NAME}-example PRIVATE -Wall -pedantic -DDBG_MACRO_NO_WARNING)
    target_link_libraries(${PROJECT_NAME}-example ${PROJECT_NAME})

    # dbg(…) demo file
    add_executable(${PROJECT_NAME}-demo tests/demo.cpp)
    target_compile_options(${PROJECT_NAME}-demo PRIVATE -Wall -pedantic -DDBG_MACRO_NO_WARNING)
    target_link_libraries(${PROJECT_NAME}-demo ${PROJECT_NAME})
    add_test(${PROJECT_NAME}-demo ${PROJECT_NAME}-demo)
endif()
