//
// Copyright (C) 2021 Dr. Michael Steffens
//
// SPDX-License-Identifier:     BSL-1.0
//


#include <Static/BasicLogger.h>
#include <cmath>
#include <cstdarg>
#include <fmt/core.h>

class StdioLogger : public Static::BasicLogger
{
public:
	~StdioLogger() override = default;

	void operator()(std::string_view message) const noexcept
	{
		if (active) {
			writeLine({false, message});
		}
	}
};

int main(int argc, char* argv[])
{
	bool active{true};
	if (argc == 2) {
		if (argv[1] == std::string_view{"--active"}) {
			active = true;
		} else if (argv[1] == std::string_view{"--inactive"}) {
			active = false;
		} else {
			std::exit(1);
		}
	}

	StdioLogger log;
	log.setActive(active);
	for (int i = 0; i < 10; ++i) {
		for (int j = 0; j < 10; ++j) {
			for (int k = 0; k < 10; ++k) {
				for (int l = 0; l < 10; ++l) {
					for (int m = 0; m < 10; ++m) {
						for (int n = 0; n < 10; ++n) {
							std::array<char, 1024> buffer;
							
							log(std::string_view(buffer.data(), fmt::format_to_n(buffer.data(), buffer.size(), "Output {}, {}, {}, {}, {}, {}, {}, {}, {}",
								123,
								i,
								j,
								k,
								l,
								m,
								n,
								std::sqrt(std::log(std::sqrt(double(i * j * k * l * m * n)) + 17.18) + i + j + k + l + m + n),
								std::log(std::sqrt(std::sqrt(double(i + j * k + l * m + n)) + 18.19) + i * j + k * l + m * n)).size));;
						}
					}
				}
			}
		}
	}
	return 0;
}
