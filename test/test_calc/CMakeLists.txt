# define project settings
cmake_minimum_required(VERSION 3.14)
project(gtestbox)
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(ROOT ./../..)

#----------------Test function-------------------
set(CalcLib "Calc")
message("target: " ${CalcLib})

# 헤더 파일이 있는 디렉토리 추가
include_directories(
    ${ROOT}/dev/include
)

#add_library(${PROJECT_NAME} STATIC
add_library(${PROJECT_NAME} SHARED
    ${ROOT}/dev/src/calc.cpp
)




link_directories(
    ${ROOT}/dev/src
)

#--------------Coverage------------------
#list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR})
#include(CodeCoverage)
#set(CMAKE_CXX_FLAGS "-g -O1 -fprofile-arcs -ftest-coverage")
#set(CMAKE_C_FLAGS "-g -O1 -fprofile-arcs -ftest-coverage")
#set(CMAKE_CXX_FLAGS "-g -O1 --coverage")
#set(CMAKE_C_FLAGS "-g -O1 --coverage")
set(CMAKE_CXX_FLAGS "-g -O1 --coverage")
set(CMAKE_C_FLAGS "-g -O1 --coverage")

option(ENABLE_COVERAGE "Enable coverage" OFF)

# --coverage 명령은 gcc 3.0 이상에서 지원
if(ENABLE_COVERAGE)
    add_compile_options(--coverage)
    add_link_options(--coverage)
endif()


#-------------GoogleTest-----------------
set(TEST_HOME ${ROOT}/test)
# hook and configure dependencies
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
#add_subdirectory(${TEST_HOME}/googletest EXCLUDE_FROM_ALL) #general Case
add_subdirectory(${TEST_HOME}/googletest ${TEST_HOME}/googletest EXCLUDE_FROM_ALL) #When specifying an out-of-tree source a binary directory must be explicitly specified
enable_testing()


#-------------Executables----------------
# add; link; and catalog test_hello tests
add_executable(test_defaults
    ${TEST_HOME}/test_calc/calc_test.cpp
)

target_include_directories(test_defaults PUBLIC
    ${CMAKE_SOURCE_DIR}
)

target_link_libraries(
    test_defaults
    gtest
    #gtest_main
    #gtest-all
    gmock_main
    #gmock-all
    ${PROJECT_NAME}
)

add_test(NAME test_defaults COMMAND test_defaults)