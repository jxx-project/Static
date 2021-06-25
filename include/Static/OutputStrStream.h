#ifndef Static_OutputStrStream_h_INCLUDED
#define Static_OutputStrStream_h_INCLUDED

#include "Static/FormatResult.h"
#include <array>
#include <ostream>
#include <string_view>

namespace Static {

template<std::size_t bufferSize>
class OutputStrStream : public std::basic_ostream<char>
{
public:
	OutputStrStream() : std::basic_ostream<char>{&buffer}
	{
	}

	OutputStrStream(OutputStrStream&& other) noexcept : buffer{std::move(other.buffer)}, std::basic_ostream<char>{&buffer}
	{
	}

	~OutputStrStream() noexcept override = default;

	FormatResult getResult() const noexcept
	{
		return buffer.getResult();
	}

private:
	class Buffer : public std::basic_streambuf<char>
	{
	public:
		Buffer() noexcept
		{
			setp(buffer.data(), buffer.data() + buffer.size());
		}

		Buffer(Buffer const& other) noexcept
		{
			setp(buffer.data(), buffer.data() + buffer.size());
			sputn(other.buffer.data(), other.pptr() - other.pbase());
			isTruncated = other.isTruncated;
		}

		~Buffer() noexcept override = default;

		int_type overflow(int_type c) noexcept override
		{
			isTruncated = true;
			return std::basic_streambuf<char>::overflow(c);
		}

		FormatResult getResult() const noexcept
		{
			return {isTruncated, std::string_view(pbase(), pptr() - pbase())};
		}

	private:
		std::array<char, bufferSize> buffer;
		bool isTruncated{false};
	};

	Buffer buffer;
};

} // namespace Static

#endif // Static_OutputStrStream_h_INCLUDED
