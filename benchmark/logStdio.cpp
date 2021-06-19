//
// Copyright (C) 2021 Dr. Michael Steffens
//
// SPDX-License-Identifier:     BSL-1.0
//


#include <Static/BasicLogger.h>
#include <cmath>
#include <cstdarg>

class StdioLogger : public Static::BasicLogger
{
public:
	~StdioLogger() override = default;

	void operator()(char const* fmt, ...) const noexcept
	{
		std::array<char, bufferSize> buffer;
		std::va_list argp;
		::va_start(argp, fmt);
		::ssize_t messageLengthOrError{std::vsnprintf(buffer.data(), buffer.size(), fmt, argp)};
		::va_end(argp);
		writeLine(std::string_view{buffer.data(), std::size_t(std::max(messageLengthOrError, ::ssize_t{0}))});
	}
};

int main(int argc, char* argv[])
{
	StdioLogger log;
	for (int i = 0; i < 10; ++i) {
		for (int j = 0; j < 10; ++j) {
			for (int k = 0; k < 10; ++k) {
				for (int l = 0; l < 10; ++l) {
					for (int m = 0; m < 10; ++m) {
						for (int n = 0; n < 10; ++n) {
							log("Output %d, %d, %d, %d, %d, %d, %d, %f",
								123,
								i,
								j,
								k,
								l,
								m,
								n,
								std::sqrt(double(i * j * k * l * m * n)));
						}
					}
				}
			}
		}
	}
	return 0;
}
