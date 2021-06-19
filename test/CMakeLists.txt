#
# Copyright (C) 2021 Dr. Michael Steffens
#
# SPDX-License-Identifier:	BSL-1.0
#


find_package(GTest REQUIRED)

add_executable(testBasicLogger testBasicLogger.cpp)
target_include_directories(testBasicLogger PRIVATE $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>)
target_link_libraries(testBasicLogger Static GTest::GTest)
add_test(NAME BasicLoggerTest COMMAND testBasicLogger)

add_executable(testFormat testFormat.cpp)
target_include_directories(testFormat PRIVATE $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>)
target_link_libraries(testFormat Static GTest::GTest)
add_test(NAME FormatTest COMMAND testFormat)

add_executable(testOutputStrStream testOutputStrStream.cpp)
target_include_directories(testOutputStrStream PRIVATE $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>)
target_link_libraries(testOutputStrStream Static GTest::GTest)
add_test(NAME OutputStrStreamTest COMMAND testOutputStrStream)
