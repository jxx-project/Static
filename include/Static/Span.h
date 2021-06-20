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
	Span(char* first, std::size_t count) noexcept;

	[[nodiscard]] char* data() noexcept;
	[[nodiscard]] std::size_t size() const noexcept;
	[[nodiscard]] Span subspan(std::size_t offset) noexcept;

private:
	char* first;
	std::size_t extent;
};

} // namespace Static

#endif // Static_Span_h_INCLUDED
