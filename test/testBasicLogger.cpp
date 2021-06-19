//
// Copyright (C) 2021 Dr. Michael Steffens
//
// SPDX-License-Identifier:     BSL-1.0
//


#include <Static/BasicLogger.h>
#include <gtest/gtest.h>

using Message = Static::Format::Buffer<Static::BasicLogger::bufferSize>;

TEST(BasicLogger, logPlain)
{
	Static::BasicLogger log;
	testing::internal::CaptureStderr();
	log([] { return Message("testing {}", "plain"); });
	std::string capturedStderr{testing::internal::GetCapturedStderr()};
	EXPECT_TRUE(testing::IsSubstring("", "", "testing plain", capturedStderr));
}

int main(int argc, char* argv[])
{
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
