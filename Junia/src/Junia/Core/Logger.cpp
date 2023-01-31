#include "Core.hpp"
#include <Junia/Core/Logger.hpp>

#include <cstdarg>
#include <cstdio>
#include <fstream>
#include <iostream>
#include <memory>
#include <ostream>
#include <utility>

#define ANSI_ESC_RESET "\x1b[0m"     // RESET
#define ANSI_ESC_TRACE "\x1b[90m"    // FG: bright_gray  |
#define ANSI_ESC_INFO  "\x1b[37m"    // FG: white        |
#define ANSI_ESC_WARN  "\x1b[33m"    // FG: yellow       |
#define ANSI_ESC_ERROR "\x1b[91m"    // FG: bright_red   |
#define ANSI_ESC_CRIT  "\x1b[37;41m" // FG: white        | BG: RED

namespace Junia
{
	namespace Log
	{
		static Logstream emptylogstream = Logstream(nullptr, LogLevel::None);

		Logstream::Logstream(std::vector<Internal::StreamData>* streams, LogLevel level) :
			streams(streams), level(level) { }

		Logstream::Logstream(const Logstream& other) : streams(other.streams), level(other.level) { }

		Logstream::~Logstream()
		{
			if (streams == nullptr) return;
			for (const auto& streamData : *streams)
			{
				if (streamData.ansi) (*streamData.stream) << ANSI_ESC_RESET;
				(*streamData.stream) << std::endl;
			}
		}

		Logger::Logger() : name("")
		{
			streams.push_back({ false, true, &std::cout });
		}

		Logger::Logger(const std::string& name) : name(name)
		{
			streams.push_back({ false, true, &std::cout });
		}

		Logger::Logger(const std::string& name, std::ostream* const stream, bool ansi) : name(name)
		{
			streams.push_back({ false, ansi, stream });
		}

		Logger::Logger(const std::string& name, const std::string& path, bool ansi) : name(name)
		{
			std::ofstream* stream = new std::ofstream(path, std::ios_base::out | std::ios_base::app);
			streams.push_back({ true, ansi, stream });
		}

		Logger::Logger(const Logger& other) : name(other.name), streams(other.streams)
		{
			for (auto& streamData : streams) streamData.own = false;
		}

		void Logger::AddStream(std::ostream* const stream, bool ansi)
		{
			streams.push_back({ false, ansi, stream });
		}

		void Logger::AddStream(const std::string& path, bool ansi)
		{
			std::ofstream* stream = new std::ofstream(path, std::ios_base::out | std::ios_base::app);
			streams.push_back({ true, ansi, stream });
		}

		Logger::~Logger()
		{
			for (const auto& streamData : streams)
			{
				if (streamData.own) delete streamData.stream;
			}
		}

		Logstream Logger::Trace()
		{
			if (maxLevel < LogLevel::Trace) return emptylogstream;
			for (const auto& streamData : streams)
			{
				(*streamData.stream) << "[" << name << "] ";
				if (streamData.ansi) (*streamData.stream) << ANSI_ESC_TRACE;
			}
			return Logstream(&streams, LogLevel::Trace);
		}

		Logstream Logger::Info()
		{
			if (maxLevel < LogLevel::Info) return emptylogstream;
			for (const auto& streamData : streams)
			{
				(*streamData.stream) << "[" << name << "] ";
				if (streamData.ansi) (*streamData.stream) << ANSI_ESC_INFO;
			}
			return Logstream(&streams, LogLevel::Info);
		}

		Logstream Logger::Warn()
		{
			if (maxLevel < LogLevel::Warn) return emptylogstream;
			for (const auto& streamData : streams)
			{
				(*streamData.stream) << "[" << name << "] ";
				if (streamData.ansi) (*streamData.stream) << ANSI_ESC_WARN;
			}
			return Logstream(&streams, LogLevel::Warn);
		}

		Logstream Logger::Error()
		{
			if (maxLevel < LogLevel::Error) return emptylogstream;
			for (const auto& streamData : streams)
			{
				(*streamData.stream) << "[" << name << "] ";
				if (streamData.ansi) (*streamData.stream) << ANSI_ESC_ERROR;
			}
			return Logstream(&streams, LogLevel::Error);
		}

		Logstream Logger::Critical()
		{
			if (maxLevel < LogLevel::Critical) return emptylogstream;
			for (const auto& streamData : streams)
			{
				(*streamData.stream) << "[" << name << "] ";
				if (streamData.ansi) (*streamData.stream) << ANSI_ESC_CRIT;
			}
			return Logstream(&streams, LogLevel::Critical);
		}
	}
}
