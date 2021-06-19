//
// Copyright (C) 2021 Dr. Michael Steffens
//
// SPDX-License-Identifier:     BSL-1.0
//


#ifndef Static_ParsePrimitives_h_INCLUDED
#define Static_ParsePrimitives_h_INCLUDED

#include <charconv>
#include <string_view>

namespace Static {

class ParsePrimitives
{
public:
	ParsePrimitives(std::string_view str) noexcept;
	virtual ~ParsePrimitives() noexcept = default;

protected:
	template<typename T>
	[[nodiscard]] T parse()
	{
		T result{};
		std::from_chars_result matchResult{std::from_chars(in.data(), in.data() + in.size(), result)};
		if (!static_cast<bool>(matchResult.ec)) {
			in.remove_prefix(matchResult.ptr - in.data());
		} else if (matchResult.ec == std::errc::result_out_of_range) {
			raiseError("value out of range");
		} else {
			raiseError("invalid value");
		}
		return result;
	}

	char parseDelimiter(std::string_view delimiters) noexcept;
	std::string_view parseIdentifier() noexcept;
	void skipSpaceChars() noexcept;
	[[nodiscard]] bool empty() const noexcept;
	[[nodiscard]] static bool isSpace(char c) noexcept;
	[[nodiscard]] static bool isAlpha(char c) noexcept;
	[[noreturn]] virtual void raiseError(std::string_view message) = 0;

private:
	std::string_view in;
};

} // namespace Static

#endif // Static_ParsePrimitives_h_INCLUDED
