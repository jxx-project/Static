//
// Copyright (C) 2021 Dr. Michael Steffens
//
// SPDX-License-Identifier:     BSL-1.0
//


#include <Static/Format.h>
#include <chrono>
#include <gtest/gtest.h>

using namespace std::chrono_literals;

TEST(Format, noArgument)
{
	Static::Format::Buffer<80> testee("This is a raw string");
	EXPECT_EQ("This is a raw string", testee.getResult().str);
}

TEST(Format, formatResult)
{
	Static::Format::Buffer<80> testee(
		"Static::FormatResult: {}, {}",
		Static::FormatResult{false, std::string_view{"not truncated"}},
		Static::FormatResult{true, std::string_view{"truncated"}});
	EXPECT_FALSE(testee.getResult().isTruncated);
	EXPECT_EQ("Static::FormatResult: not truncated, truncated[...]", testee.getResult().str);
}

TEST(Format, stringView)
{
	Static::Format::Buffer<80> testee("std::string_view values: {}", std::string_view{"string_view"});
	EXPECT_FALSE(testee.getResult().isTruncated);
	EXPECT_EQ("std::string_view values: string_view", testee.getResult().str);
}

TEST(Format, integralTypes)
{
	Static::Format::Buffer<80> testee(
		"Integral values: {}, {}, {}, {}, {}, {}, {}, {}",
		char{-1},
		(unsigned char){1},
		short{-2},
		(unsigned short){2},
		int{-3},
		(unsigned int){3},
		long{-4},
		(unsigned long){4});
	EXPECT_FALSE(testee.getResult().isTruncated);
	EXPECT_EQ("Integral values: -1, 1, -2, 2, -3, 3, -4, 4", testee.getResult().str);
}

TEST(Format, boolTypes)
{
	Static::Format::Buffer<80> testee("Boolean values: {}, {}", false, true);
	EXPECT_FALSE(testee.getResult().isTruncated);
	EXPECT_EQ("Boolean values: false, true", testee.getResult().str);
}

TEST(Format, floatTypes)
{
	Static::Format::Buffer<80> testee("Float values: {}", 3.14);
	EXPECT_FALSE(testee.getResult().isTruncated);
	EXPECT_EQ("Float values: 3.140000", testee.getResult().str);
}

TEST(Format, charPointerTypes)
{
	Static::Format::Buffer<80> testee(
		"Char pointer values: {}, {}, {}, {}",
		const_cast<char*>("char*"),
		static_cast<char*>(nullptr),
		(char const*){"char const*"},
		(char const*){nullptr});
	EXPECT_FALSE(testee.getResult().isTruncated);
	EXPECT_EQ("Char pointer values: char*, (nil), char const*, (nil)", testee.getResult().str);
}

TEST(Format, pointerTypes)
{
	Static::Format::Buffer<80> testee(
		"Pointer values: {}, {}, {}, {}",
		reinterpret_cast<void*>(0x1a2b3c),
		(void*){nullptr},
		reinterpret_cast<int*>(0x4d5f60),
		(int*){nullptr});
	EXPECT_FALSE(testee.getResult().isTruncated);
	EXPECT_EQ("Pointer values: 0x1a2b3c, (nil), 0x4d5f60, (nil)", testee.getResult().str);
}

TEST(Format, durationTypes)
{
	Static::Format::Buffer<80> testee("Duration values: {}, {}, {}, {}, {}, {}", 1ns, 2us, 3ms, 4s, 5min, 6h);
	EXPECT_FALSE(testee.getResult().isTruncated);
	EXPECT_EQ("Duration values: 1ns, 2us, 3ms, 4s, 5min, 6h", testee.getResult().str);
}

int main(int argc, char* argv[])
{
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
