//
// Copyright (C) 2021 Dr. Michael Steffens
//
// SPDX-License-Identifier:     BSL-1.0
//


#ifndef Static_Span_h_INCLUDED
#define Static_Span_h_INCLUDED

#include <cstddef>

namespace Static {

class Span
{
public:
	constexpr Span(char* first, std::size_t count) noexcept : first{first}, extent{count}
	{
	}

	[[nodiscard]] constexpr char* data() noexcept
	{
		return first;
	}

	[[nodiscard]] constexpr std::size_t size() const noexcept
	{
		return extent;
	}

	[[nodiscard]] constexpr Span subspan(std::size_t offset) noexcept
	{
		return Span{first + offset, extent - offset};
	}


private:
	char* first;
	std::size_t extent;
};

} // namespace Static

#endif // Static_Span_h_INCLUDED
