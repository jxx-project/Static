//
// Copyright (C) 2021 Dr. Michael Steffens
//
// SPDX-License-Identifier:     BSL-1.0
//


#ifndef Static_Format_h_INCLUDED
#define Static_Format_h_INCLUDED

#include "Static/FormatResult.h"
#include "Static/Span.h"
#include <array>
#include <charconv>
#include <chrono>
#include <cstddef>
#include <string_view>
#include <type_traits>

namespace Static {

class Format
{
public:
	template<std::size_t bufferSize>
	class Buffer
	{
	public:
		template<typename... Args>
		explicit Buffer(std::string_view fmt, Args const&... args) noexcept :
			result{Format::toBuffer(Span{buffer.data(), buffer.size()}, fmt, std::forward<Args const&>(args)...)}
		{
		}

		Buffer(Buffer const& other) noexcept :
			result{other.result.isTruncated, std::string_view(buffer.data(), other.result.str.size())}
		{
			std::copy(other.buffer.begin(), other.buffer.begin() + other.result.str.size(), buffer.begin());
		}

		Buffer& operator=(Buffer const& other) noexcept
		{
			if (this != &other) {
				std::copy(other.buffer.begin(), other.buffer.begin() + other.result.str.size(), buffer.begin());
				result = {other.result.isTruncated, std::string_view(buffer.data(), other.result.str.size())};
			}
			return *this;
		}

		~Buffer() noexcept = default;

		[[nodiscard]] FormatResult getResult() const noexcept
		{
			return result;
		}

		static constexpr std::size_t maxLength{bufferSize};

	private:
		std::array<char, bufferSize> buffer;
		FormatResult result;
	};

	template<typename... Args>
	[[nodiscard]] static FormatResult toBuffer(Span out, std::string_view fmt, Args const&... args)
	{
		char const* first{out.data()};
		bool isTruncated{(write(out, fmt, args) || ...) || write(out, fmt)};
		return {isTruncated, std::string_view{first, std::size_t(out.data() - first)}};
	}

	static constexpr std::string_view truncationSuffix{"[...]"};

private:
	template<typename T>
	static bool write(Span& out, std::string_view& fmt, T const& value) noexcept
	{
		std::size_t placeholderPos{fmt.find("{}")};
		bool isTruncated{write(out, std::string_view(fmt.data(), placeholderPos))};
		if (!isTruncated) {
			fmt.remove_prefix(placeholderPos + 2);
			isTruncated = write(out, value);
		}
		return isTruncated;
	}

	static bool write(Span& out, FormatResult const& value) noexcept;
	static bool write(Span& out, std::string_view const& value) noexcept;

	template<typename T, typename = typename std::enable_if<std::is_integral<T>::value && !std::is_same<T, bool>::value>::type>
	static bool write(Span& out, T const& value, int base = 10) noexcept
	{
		bool isTruncated{false};
		std::to_chars_result conversionResult{std::to_chars(out.data(), out.data() + out.size(), value, base)};
		if (conversionResult.ec == std::errc{}) {
			out = out.subspan(conversionResult.ptr - out.data());
		} else {
			isTruncated = true;
		}
		return isTruncated;
	}

	static bool write(Span& out, bool value) noexcept;
	static bool write(Span& out, double value) noexcept;
	static bool write(Span& out, char const* ptr) noexcept;
	static bool write(Span& out, void const* ptr) noexcept;
	static bool write(Span& out, std::chrono::nanoseconds duration) noexcept;
	static bool write(Span& out, std::chrono::microseconds duration) noexcept;
	static bool write(Span& out, std::chrono::milliseconds duration) noexcept;
	static bool write(Span& out, std::chrono::seconds duration) noexcept;
	static bool write(Span& out, std::chrono::minutes duration) noexcept;
	static bool write(Span& out, std::chrono::hours duration) noexcept;
};

} // namespace Static

#endif // Static_Format_h_INCLUDED
