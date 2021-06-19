#
# Copyright (C) 2021 Dr. Michael Steffens
#
# SPDX-License-Identifier:	BSL-1.0
#

cmake_minimum_required(VERSION 3.13)
project(Static VERSION 0.0.1 LANGUAGES CXX)

include(GNUInstallDirs)
include(CMakePackageConfigHelpers)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS NO)

file(GLOB Static_SRCS_G src/Static/*.cpp)
add_library(Static STATIC ${Static_SRCS_G})
set_target_properties(Static PROPERTIES DEBUG_POSTFIX d)
target_compile_options(Static PRIVATE -fPIC -fno-exceptions -fno-rtti)
target_include_directories(Static PUBLIC
	$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
	$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src>
	$<INSTALL_INTERFACE:include>)

install(TARGETS Static EXPORT StaticTargets
	RUNTIME DESTINATION ${CMAKE_INSTALL_LIBDIR})
install(DIRECTORY include/ DESTINATION ${CMAKE_INSTALL_INCLUDEDIR} FILES_MATCHING PATTERN "*.h")
install(EXPORT StaticTargets NAMESPACE ${PROJECT_NAME}:: DESTINATION share/Static/cmake)
configure_file(cmake/StaticConfig.cmake.in StaticConfig.cmake @ONLY)
write_basic_package_version_file(${CMAKE_CURRENT_BINARY_DIR}/StaticConfigVersion.cmake COMPATIBILITY SameMajorVersion)
install(FILES
	${CMAKE_CURRENT_BINARY_DIR}/StaticConfig.cmake
	${CMAKE_CURRENT_BINARY_DIR}/StaticConfigVersion.cmake
	DESTINATION share/Static/cmake)

enable_testing()
add_subdirectory(test)
