//
// Copyright (C) 2021 Dr. Michael Steffens
//
// SPDX-License-Identifier:     BSL-1.0
//


#include <Static/BasicLogger.h>
#include <Static/OutputStrStream.h>
#include <cmath>

using OutputStrStream = Static::OutputStrStream<Static::BasicLogger::bufferSize>;

class OutputStrStreamLogger : public Static::BasicLogger
{
public:
	~OutputStrStreamLogger() override = default;

	void operator()(OutputStrStream const& out) const noexcept
	{
		writeLine(out.getStringView());
	}
};

int main(int argc, char* argv[])
{
	OutputStrStreamLogger log;
	for (int i = 0; i < 10; ++i) {
		for (int j = 0; j < 10; ++j) {
			for (int k = 0; k < 10; ++k) {
				for (int l = 0; l < 10; ++l) {
					for (int m = 0; m < 10; ++m) {
						for (int n = 0; n < 10; ++n) {
							OutputStrStream out;
							out << "Output " << 123 << ", " << i << ", " << j << ", " << k << ", " << l << ", " << m << ", " << n
								<< ", " << std::sqrt(double(i * j * k * l * m * n));
							log(out);
						}
					}
				}
			}
		}
	}
	return 0;
}
