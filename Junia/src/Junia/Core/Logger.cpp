#include <Junia/Core/Logger.hpp>

#include <cstdarg>
#include <cstdio>
#include <iostream>
#include <memory>
#include <utility>

#define ANSI_ESC_RESET  "\x1b[0m"
#define ANSI_ESC_WHITE  "\x1b[37;40m" // WHITE  BLACK
#define ANSI_ESC_GREEN  "\x1b[32;40m" // GREEN  BLACK
#define ANSI_ESC_ORANGE "\x1b[33;40m" // YELLOW BLACK
#define ANSI_ESC_RED    "\x1b[31;40m" // RED    BLACK
#define ANSI_ESC_DRED   "\x1b[37;41m" // WHITE  RED

namespace Junia
{
	Logstream::Logstream(FILE* _stream)
	{
		fp = _stream;
		stream = std::ofstream(_stream);
	}

	Logstream::Logstream(const Logstream& other)
	{
		fp = other.fp;
		stream = std::ofstream(other.fp);
	}

	Logstream::~Logstream()
	{
		stream << ANSI_ESC_RESET << std::endl;
		stream.flush();
	}

	Logger::Logger(const std::string& name) : name(name), stream(stdout)
	{ }

	std::shared_ptr<Logger> Logger::Create(const std::string& name)
	{
		return std::make_shared<Logger>(name);
	}

	Logger::~Logger()
	{
		stream << ANSI_ESC_RESET;
	}

	Logstream Logger::Trace()
	{
		stream << "[" << name << "] " << ANSI_ESC_WHITE;
		return stream;
	}

	Logstream Logger::Info()
	{
		stream << "[" << name << "] " << ANSI_ESC_GREEN;
		return stream;
	}

	Logstream Logger::Warn()
	{
		stream << "[" << name << "] " << ANSI_ESC_ORANGE;
		return stream;
	}

	Logstream Logger::Error()
	{
		stream << "[" << name << "] " << ANSI_ESC_RED;
		return stream;
	}

	Logstream Logger::Critical()
	{
		stream << "[" << name << "] " << ANSI_ESC_DRED;
		return stream;
	}
}
