#include "Core.hpp"
#include <Junia/Core/Logger.hpp>

#include <cstdarg>
#include <cstdio>
#include <fstream>
#include <iostream>
#include <memory>
#include <ostream>
#include <utility>

#define ANSI_ESC_RESET  "\x1b[0m"
#define ANSI_ESC_WHITE  "\x1b[37;40m" // WHITE  BLACK
#define ANSI_ESC_GREEN  "\x1b[32;40m" // GREEN  BLACK
#define ANSI_ESC_ORANGE "\x1b[33;40m" // YELLOW BLACK
#define ANSI_ESC_RED    "\x1b[91;40m" // BRED   BLACK
#define ANSI_ESC_DRED   "\x1b[37;41m" // WHITE  RED

namespace Junia
{
	namespace Log
	{
		static std::ofstream emptystream = std::ofstream();
		static Logstream emptylogstream = Logstream(&emptystream);

		Logstream::Logstream(std::ostream* stream) : stream(stream) { }
		Logstream::Logstream(const Logstream& other) : stream(other.stream) { }
		Logstream::~Logstream() { (*stream) << ANSI_ESC_RESET << std::endl; }

		Logger::Logger() : name(""), stream(&std::cout) { }
		Logger::Logger(const std::string& name) : name(name), stream(&std::cout) { }
		Logger::Logger(const std::string& name, std::ostream* stream) : name(name), stream(stream) { }
		Logger::Logger(const std::string& name, const std::string& path) : name(name)
		{
			ownStream = true;
			stream = new std::ofstream(path, std::ios_base::out | std::ios_base::app);
		}
		Logger::Logger(const Logger& other) : name(other.name), stream(other.stream) { }

		Logger::~Logger()
		{
			if (ownStream) delete stream;
		}

		Logstream Logger::Trace()
		{
			if (maxLevel < LogLevel::Trace) return emptylogstream;
			(*stream) << "[" << name << "] " << ANSI_ESC_WHITE;
			return stream;
		}

		Logstream Logger::Info()
		{
			if (maxLevel < LogLevel::Info) return emptylogstream;
			(*stream) << "[" << name << "] " << ANSI_ESC_GREEN;
			return stream;
		}

		Logstream Logger::Warn()
		{
			if (maxLevel < LogLevel::Warn) return emptylogstream;
			(*stream) << "[" << name << "] " << ANSI_ESC_ORANGE;
			return stream;
		}

		Logstream Logger::Error()
		{
			if (maxLevel < LogLevel::Error) return emptylogstream;
			(*stream) << "[" << name << "] " << ANSI_ESC_RED;
			return stream;
		}

		Logstream Logger::Critical()
		{
			if (maxLevel < LogLevel::Critical) return emptylogstream;
			(*stream) << "[" << name << "] " << ANSI_ESC_DRED;
			return stream;
		}
	}
}
