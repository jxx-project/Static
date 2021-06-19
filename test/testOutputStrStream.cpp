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
	EXPECT_EQ("testing output string", testee.getStringView());
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
	EXPECT_EQ("", other.getStringView());
	EXPECT_EQ("testing move stream", testee.getStringView());
}

int main(int argc, char* argv[])
{
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
