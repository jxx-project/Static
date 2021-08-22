//
// Copyright (C) 2021 Dr. Michael Steffens
//
// SPDX-License-Identifier:     BSL-1.0
//


#ifndef Static_Logger_h_INCLUDED
#define Static_Logger_h_INCLUDED

#include "Static/Format.h"
#include "Static/OperationType.h"
#include <chrono>

namespace Static {

class Logger
{
public:
	virtual ~Logger() = default;

	template<typename F>
	void operator()(F callback) const noexcept
	{
		log(FormattingCallback{callback});
	}

protected:
	class Formatter
	{
	public:
		virtual ~Formatter() noexcept = default;
		virtual Format operator()() const noexcept = 0;
	};

	template<typename F>
	class FormattingCallback : public Formatter
	{
	public:
		explicit FormattingCallback(F callback) : callback{callback}
		{
		}
		~FormattingCallback() noexcept override = default;

		Format operator()() const noexcept override
		{
			return callback();
		}

	private:
		F callback;
	};

	virtual void log(Formatter const& formatter) const noexcept = 0;
};

} // namespace Static

#endif // Static_Logger_h_INCLUDED
