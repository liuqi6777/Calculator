cmake_minimum_required(VERSION 3.0.0)
project(calculator VERSION 0.1.0)

set(CMAKE_CXX_STANDARD 17) 
set(CMAKE_CXX_STANDARD_REQUIRED True) 

aux_source_directory(. DIR_SRCS)
add_executable(calculator main.cpp)
target_link_libraries(calculator)

include(CTest)
enable_testing()
add_executable(test_c test.cpp)
add_test(NAME test_all COMMAND test_c)
SET_TESTS_PROPERTIES(test_all PROPERTIES ENVIRONMENT "CTEST_OUTPUT_ON_FAILURE=1")

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
