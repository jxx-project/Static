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

void BasicLogger::setActive(bool active) noexcept
{
	this->active = active;
}

void BasicLogger::log(Formatter const& formatter) const noexcept
{
	if (active) {
		Format::Buffer message{formatter()};
		writeLine(message.getResult());
	}
}

void BasicLogger::writeLine(Format::Result const& message) const noexcept
{
	std::array<char, maxLength + Format::truncationSuffix.size() + 1> buffer;
	Span out{buffer.data(), buffer.size()};
	std::size_t length{message.str.size()};
	if (length <= maxLength) {
		std::copy(message.str.begin(), message.str.begin() + length, out.data());
		out = out.subspan(length);
	}
	if (length > maxLength || message.isTruncated) {
		std::copy(Format::truncationSuffix.begin(), Format::truncationSuffix.begin() + Format::truncationSuffix.size(), out.data());
		out = out.subspan(Format::truncationSuffix.size());
	}
	*out.data() = '\n';
	std::size_t totalLength(out.data() - buffer.data() + 1);

	int propagateErrno{errno};

	std::size_t totalBytesWritten{0};
	::ssize_t bytesWritten{0};
	while ((bytesWritten = ::write(STDERR_FILENO, buffer.data() + totalBytesWritten, totalLength - totalBytesWritten)) > 0) {
		totalBytesWritten += bytesWritten;
	}

	errno = propagateErrno;
}

} // namespace Static
