//
// Copyright (C) 2021 Dr. Michael Steffens
//
// SPDX-License-Identifier:     BSL-1.0
//


#include "Static/BasicLogger.h"
#include "Static/Format.h"
#include <algorithm>
#include <cerrno>
#include <unistd.h>

namespace Static {

void BasicLogger::log(Formatter const& formatter) const noexcept
{
	Format::Buffer message{formatter()};
	writeLine(message.getResult());
}

void BasicLogger::writeLine(std::string_view message) const noexcept
{
	std::array<char, bufferSize> buffer;
	std::size_t length{std::min(message.size(), buffer.size() - 1)};
	std::copy(message.begin(), message.begin() + length, buffer.data());
	buffer[length++] = '\n';

	int propagateErrno{errno};

	std::size_t totalBytesWritten{0};
	::ssize_t bytesWritten{0};
	while ((bytesWritten = ::write(STDERR_FILENO, &buffer[totalBytesWritten], length - totalBytesWritten)) > 0) {
		totalBytesWritten += bytesWritten;
	}

	errno = propagateErrno;
}

} // namespace Static
