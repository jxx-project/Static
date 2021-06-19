#ifndef Static_OutputStrStream_h_INCLUDED
#define Static_OutputStrStream_h_INCLUDED

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

	std::string_view getStringView() const noexcept
	{
		return buffer.getStringView();
	}

private:
	class Buffer : public std::basic_streambuf<char>
	{
	public:
		Buffer() noexcept
		{
			setp(buffer.data(), buffer.data() + buffer.size());
		}

		Buffer(Buffer&& other) noexcept
		{
			setp(buffer.data(), buffer.data() + buffer.size());
			sputn(other.buffer.data(), other.pptr() - other.pbase());
			other.setp(nullptr, nullptr);
		}

		virtual ~Buffer() = default;

		std::string_view getStringView() const noexcept
		{
			return std::string_view(pbase(), pptr() - pbase());
		}

	private:
		std::array<char, bufferSize> buffer;
	};

	Buffer buffer;
};

} // namespace Static

#endif // Static_OutputStrStream_h_INCLUDED
