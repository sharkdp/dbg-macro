cmake_minimum_required(VERSION 3.8)

project(dbg_macro LANGUAGES CXX)

# CMake Options

option(DBG_MACRO_BUILD_EXAMPLES OFF)
option(DBG_MACRO_BUILD_TESTS OFF)

# Add dbg_macro Library

add_library(${PROJECT_NAME} INTERFACE)
add_library(${PROJECT_NAME}::${PROJECT_NAME} ALIAS ${PROJECT_NAME})
target_include_directories(${PROJECT_NAME} INTERFACE
	$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
	$<INSTALL_INTERFACE:include>)
target_compile_features(${PROJECT_NAME} INTERFACE cxx_std_11)

# Build Examples

if(DBG_MACRO_BUILD_EXAMPLES)
	macro(dbg_macro_add_example EXAMPLENAME)
		add_executable(${EXAMPLENAME} ${ARGN})
		target_link_libraries(${EXAMPLENAME} PRIVATE dbg_macro::dbg_macro)
		set_target_properties(${EXAMPLENAME} PROPERTIES FOLDER examples)
	endmacro()
	add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/examples")
endif()

# Build Tests

if(DBG_MACRO_BUILD_TESTS)
	enable_testing()
	macro(dbg_macro_add_test TESTNAME)
		add_executable(${TESTNAME} ${ARGN})
		target_link_libraries(${TESTNAME} PRIVATE dbg_macro::dbg_macro)
		add_test(NAME ${TESTNAME} COMMAND ${TESTNAME})
		set_target_properties(${TESTNAME} PROPERTIES FOLDER tests)
	endmacro()
	add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/tests")
endif()

# Install

install(TARGETS dbg_macro EXPORT dbg_macroConfig)
install(EXPORT dbg_macroConfig NAMESPACE dbg_macro:: DESTINATION lib/cmake/dbg_macro)
install(DIRECTORY include DESTINATION .)
