cmake_minimum_required(VERSION 3.9.0 FATAL_ERROR)

project(StrUtilsTests)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -pedantic -std=c++1z")
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -O0")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -Ofast -DNDEBUG")

set(CMAKE_INCLUDE_CURRENT_DIR ON)

enable_testing()
find_package(GTest REQUIRED)

SET(SRC_DIR ${CMAKE_SOURCE_DIR}/../src)
SET(TST_DIR ${CMAKE_SOURCE_DIR})

SET(SPLIT_HEADERS ${SRC_DIR}/split.hpp)
SET(JOIN_HEADERS ${SRC_DIR}/join.hpp)

set(TEST_HEADERS ${TST_DIR}/split_tst.hpp ${TST_DIR}/join_tst.hpp ${TST_DIR}/helpers.hpp)
set(TEST_SOURCES ${TST_DIR}/main.cpp)

include_directories(${SRC_DIR} ${TST_DIR})

add_executable(run_tests ${SPLIT_HEADERS} ${JOIN_HEADERS} ${TEST_HEADERS} ${TEST_SOURCES})

target_link_libraries(run_tests ${GTEST_LIBRARIES} pthread)

set_property(TARGET run_tests PROPERTY CXX_STANDARD 17)
set_property(TARGET run_tests PROPERTY CXX_EXTENSIONS OFF)
