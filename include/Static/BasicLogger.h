//
// Copyright (C) 2021 Dr. Michael Steffens
//
// SPDX-License-Identifier:     BSL-1.0
//


#ifndef Static_Logger_h_INCLUDED
#define Static_Logger_h_INCLUDED

#include "Static/Format.h"
#include <cstddef>

namespace Static {

class BasicLogger
{
public:
	virtual ~BasicLogger() noexcept = default;

	template<typename F>
	void operator()(F callback) const noexcept
	{
		log(FormattingCallback{callback});
	}

	void setActive(bool active) noexcept;
	static void writeLine(FormatResult const& message) noexcept;

	static constexpr std::size_t maxLength{1024};

protected:
	class Formatter
	{
	public:
		virtual ~Formatter() noexcept = default;
		virtual Format::Buffer<maxLength> operator()() const noexcept = 0;
	};

	template<typename F>
	class FormattingCallback : public Formatter
	{
	public:
		explicit FormattingCallback(F callback) : callback{callback}
		{
		}
		~FormattingCallback() noexcept override = default;

		Format::Buffer<maxLength> operator()() const noexcept override
		{
			return callback();
		}

	private:
		F callback;
	};

	virtual void log(Formatter const& formatter) const noexcept;

	bool active{true};
};

} // namespace Static

#endif // Static_BasicLogger_h_INCLUDED
