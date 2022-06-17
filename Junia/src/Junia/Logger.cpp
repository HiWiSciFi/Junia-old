#include "Logger.hpp"

#include <cstdarg>
#include <utility>

namespace Junia
{
	Logger::Logger(std::string name) : name(std::move(name)) { }

	std::shared_ptr<Logger> Logger::Create(std::string name)
	{
		return std::make_shared<Logger>(std::move(name));
	}

	void Logger::Trace(const std::string fmt, ...) const
	{
		va_list args;
		va_start(args, fmt);
		const std::string fmts = "\x1b[37;40m[" + name + "]" + fmt + "\n\x1b[0m";
		vfprintf(stdout, fmts.c_str(), args);
		va_end(args);
	}

	void Logger::Info(const std::string fmt, ...) const
	{
		va_list args;
		va_start(args, fmt);
		vfprintf(stdout, ("\x1b[32;40m[" + name + "]" + fmt + "\n\x1b[0m").c_str(), args);
		va_end(args);
	}

	void Logger::Warn(const std::string fmt, ...) const
	{
		va_list args;
		va_start(args, fmt);
		vfprintf(stdout, ("\x1b[33;40m[" + name + "]" + fmt + "\n\x1b[0m").c_str(), args);
		va_end(args);
	}

	void Logger::Error(const std::string fmt, ...) const
	{
		va_list args;
		va_start(args, fmt);
		vfprintf(stdout, ("\x1b[31;40m[" + name + "]" + fmt + "\n\x1b[0m").c_str(), args);
		va_end(args);
	}

	void Logger::Critical(const std::string fmt, ...) const
	{
		va_list args;
		va_start(args, fmt);
		vfprintf(stdout, ("\x1b[37;41m[" + name + "]" + fmt + "\n\x1b[0m").c_str(), args);
		va_end(args);
	}
}
