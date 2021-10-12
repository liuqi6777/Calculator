cmake_minimum_required(VERSION 3.0.0)
project(calculator VERSION 0.1.0)

set(CMAKE_CXX_STANDARD 11) 
set(CMAKE_CXX_STANDARD_REQUIRED True) 

include(CTest)
enable_testing()

aux_source_directory(. DIR_SRCS)
add_executable(calculator main.cpp)
target_link_libraries(calculator)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
