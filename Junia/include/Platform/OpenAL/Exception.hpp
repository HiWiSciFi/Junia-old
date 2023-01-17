#pragma once

#include <exception>

namespace OpenAL
{
	class Exception : public std::exception
	{
	private:
		const char* msg;

	public:
		Exception(const char* msg) : msg(msg) { }
		virtual const char* what() const override { return msg; }
	};
}
