//
// Copyright (C) 2021 Dr. Michael Steffens
//
// SPDX-License-Identifier:     BSL-1.0
//


#include "Static/BasicLogger.h"
#include <cmath>

using Message = Static::Format::Buffer<Static::BasicLogger::bufferSize>;

int main(int argc, char* argv[])
{
	Static::BasicLogger log;
	for (int i = 0; i < 10; ++i) {
		for (int j = 0; j < 10; ++j) {
			for (int k = 0; k < 10; ++k) {
				for (int l = 0; l < 10; ++l) {
					for (int m = 0; m < 10; ++m) {
						for (int n = 0; n < 10; ++n) {
							log([&] {
								return Message(
									"Output {}, {}, {}, {}, {}, {}, {}, {}",
									123,
									i,
									j,
									k,
									l,
									m,
									n,
									std::sqrt(double(i * j * k * l * m * n)));
							});
						}
					}
				}
			}
		}
	}
	return 0;
}
