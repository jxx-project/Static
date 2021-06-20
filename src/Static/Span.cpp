//
// Copyright (C) 2021 Dr. Michael Steffens
//
// SPDX-License-Identifier:     BSL-1.0
//


#include "Static/Span.h"

namespace Static {

Span::Span(char* first, std::size_t count) noexcept : first{first}, extent{count}
{
}

char* Span::data() noexcept
{
	return first;
}

std::size_t Span::size() const noexcept
{
	return extent;
}

Span Span::subspan(std::size_t offset) noexcept
{
	return Span{first + offset, extent - offset};
}

} // namespace Static
