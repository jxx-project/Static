//
// Copyright (C) 2021 Dr. Michael Steffens
//
// SPDX-License-Identifier:     BSL-1.0
//


#include "Static/Format.h"

namespace Static {

bool Format::write(Span& out, Format::Result const& value) noexcept
{
	return write(out, value.str) || value.isTruncated && write(out, truncationSuffix);
}

bool Format::write(Span& out, std::string_view const& value) noexcept
{
	bool isTruncated{false};
	if (value.size() <= out.size()) {
		std::copy(value.begin(), value.begin() + value.size(), out.data());
		out = out.subspan(value.size());
	} else {
		isTruncated = true;
	}
	return isTruncated;
}

bool Format::write(Span& out, bool value) noexcept
{
	return value ? write(out, std::string_view("true")) : write(out, std::string_view("false"));
}

bool Format::write(Span& out, double value) noexcept
{
	bool isTruncated{false};
	::ssize_t lengthOrError{::snprintf(out.data(), out.size(), "%f", double(value))};
	if (lengthOrError >= 0 && lengthOrError <= out.size()) {
		out = out.subspan(lengthOrError);
	} else {
		isTruncated = true;
	}
	return isTruncated;
}

bool Format::write(Span& out, char const* ptr) noexcept
{
	return ptr == nullptr ? write(out, std::string_view("(nil)")) : write(out, std::string_view(ptr));
}

bool Format::write(Span& out, void const* ptr) noexcept
{
	return ptr == nullptr ? write(out, std::string_view("(nil)")) :
							write(out, std::string_view("0x")) || write(out, std::uintptr_t(ptr), 16);
}

bool Format::write(Span& out, std::chrono::nanoseconds duration) noexcept
{
	return write(out, duration.count()) || write(out, std::string_view("ns"));
}

bool Format::write(Span& out, std::chrono::microseconds duration) noexcept
{
	return write(out, duration.count()) || write(out, std::string_view("us"));
}

bool Format::write(Span& out, std::chrono::milliseconds duration) noexcept
{
	return write(out, duration.count()) || write(out, std::string_view("ms"));
}

bool Format::write(Span& out, std::chrono::seconds duration) noexcept
{
	return write(out, duration.count()) || write(out, std::string_view("s"));
}

bool Format::write(Span& out, std::chrono::minutes duration) noexcept
{
	return write(out, duration.count()) || write(out, std::string_view("min"));
}

bool Format::write(Span& out, std::chrono::hours duration) noexcept
{
	return write(out, duration.count()) || write(out, std::string_view("h"));
}

} // namespace Static
