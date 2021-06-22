//
// Copyright (C) 2021 Dr. Michael Steffens
//
// SPDX-License-Identifier:     BSL-1.0
//


#include <Static/OutputStrStream.h>
#include <gtest/gtest.h>

TEST(OutputStrStream, outputString)
{
	Static::OutputStrStream<80> testee;
	testee << "testing"
		   << " "
		   << "output"
		   << " "
		   << "string";
	EXPECT_FALSE(testee.getResult().isTruncated);
	EXPECT_EQ("testing output string", testee.getResult().str);
}

TEST(OutputStrStream, moveStream)
{
	Static::OutputStrStream<80> other;
	other << "testing"
		  << " "
		  << "move"
		  << " "
		  << "stream";
	Static::OutputStrStream<80> testee{std::move(other)};
	EXPECT_EQ("", other.getResult().str);
	EXPECT_FALSE(testee.getResult().isTruncated);
	EXPECT_EQ("testing move stream", testee.getResult().str);
}

TEST(OutputStrStream, overflow)
{
	Static::OutputStrStream<11> testee;
	testee << "testing"
		   << " "
		   << "output"
		   << " "
		   << "string";
	EXPECT_TRUE(testee.getResult().isTruncated);
	EXPECT_EQ("testing out", testee.getResult().str);
}

int main(int argc, char* argv[])
{
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
