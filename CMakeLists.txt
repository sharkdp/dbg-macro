cmake_minimum_required(VERSION 3.1)

project(dbg_macro)

set(CMAKE_CXX_STANDARD 11)

string(COMPARE EQUAL ${CMAKE_CURRENT_SOURCE_DIR} ${CMAKE_SOURCE_DIR} IS_MAIN_PROJECT)
option(DBG_MACRO_ENABLE_TESTS "Enable tests." ${IS_MAIN_PROJECT})

add_library(${PROJECT_NAME} INTERFACE)
target_include_directories(${PROJECT_NAME} INTERFACE ".")

if (DBG_MACRO_ENABLE_TESTS)
    add_executable(${PROJECT_NAME}-example tests/example.cpp)
    target_compile_options(${PROJECT_NAME}-example PRIVATE -Wall -pedantic -DDBG_MACRO_NO_WARNING)
    target_link_libraries(${PROJECT_NAME}-example ${PROJECT_NAME})

    add_executable(${PROJECT_NAME}-tests tests/tests.cpp)
    target_compile_options(${PROJECT_NAME}-tests PRIVATE -Wall -pedantic -DDBG_MACRO_NO_WARNING)
    target_link_libraries(${PROJECT_NAME}-tests ${PROJECT_NAME})

    add_executable(${PROJECT_NAME}-tests-macro_disabled tests/tests.cpp)
    target_compile_options(${PROJECT_NAME}-tests-macro_disabled PRIVATE -Wall -pedantic -DDBG_MACRO_NO_WARNING -DDBG_MACRO_DISABLE)
    target_link_libraries(${PROJECT_NAME}-tests-macro_disabled ${PROJECT_NAME})

    enable_testing()
    add_test(${PROJECT_NAME} ${PROJECT_NAME}-tests)
    add_test(${PROJECT_NAME}-macro_disabled ${PROJECT_NAME}-tests-macro_disabled)
endif()
