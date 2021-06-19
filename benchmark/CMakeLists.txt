#
# Copyright (C) 2021 Dr. Michael Steffens
#
# SPDX-License-Identifier:	BSL-1.0
#

cmake_minimum_required(VERSION 3.13)
project(StaticBenchmark VERSION 0.0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS NO)

add_executable(logCerr logCerr.cpp)
target_include_directories(logCerr PRIVATE $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>)
target_link_libraries(logCerr Static)
target_compile_options(logCerr PRIVATE -fno-exceptions -fno-rtti)

add_executable(logFormat logFormat.cpp)
target_include_directories(logFormat PRIVATE $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>)
target_link_libraries(logFormat Static)
target_compile_options(logFormat PRIVATE -fno-exceptions -fno-rtti)

add_executable(logFormatLambda logFormatLambda.cpp)
target_include_directories(logFormatLambda PRIVATE $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>)
target_link_libraries(logFormatLambda Static)
target_compile_options(logFormatLambda PRIVATE -fno-exceptions -fno-rtti)

add_executable(logOutputStrStream logOutputStrStream.cpp)
target_include_directories(logOutputStrStream PRIVATE $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>)
target_link_libraries(logOutputStrStream Static)
target_compile_options(logOutputStrStream PRIVATE -fno-exceptions -fno-rtti)

add_executable(logStdio logStdio.cpp)
target_include_directories(logStdio PRIVATE $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>)
target_link_libraries(logStdio Static)
target_compile_options(logStdio PRIVATE -fno-exceptions -fno-rtti)
