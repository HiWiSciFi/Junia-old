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
				if (streamData.ansi) (*streamData.stream) << ANSI_ESC_WHITE;
			}
			return Logstream(&streams, LogLevel::Trace);
		}

		Logstream Logger::Info()
		{
			if (maxLevel < LogLevel::Info) return emptylogstream;
			for (const auto& streamData : streams)
			{
				(*streamData.stream) << "[" << name << "] ";
				if (streamData.ansi) (*streamData.stream) << ANSI_ESC_GREEN;
			}
			return Logstream(&streams, LogLevel::Info);
		}

		Logstream Logger::Warn()
		{
			if (maxLevel < LogLevel::Warn) return emptylogstream;
			for (const auto& streamData : streams)
			{
				(*streamData.stream) << "[" << name << "] ";
				if (streamData.ansi) (*streamData.stream) << ANSI_ESC_ORANGE;
			}
			return Logstream(&streams, LogLevel::Warn);
		}

		Logstream Logger::Error()
		{
			if (maxLevel < LogLevel::Error) return emptylogstream;
			for (const auto& streamData : streams)
			{
				(*streamData.stream) << "[" << name << "] ";
				if (streamData.ansi) (*streamData.stream) << ANSI_ESC_RED;
			}
			return Logstream(&streams, LogLevel::Error);
		}

		Logstream Logger::Critical()
		{
			if (maxLevel < LogLevel::Critical) return emptylogstream;
			for (const auto& streamData : streams)
			{
				(*streamData.stream) << "[" << name << "] ";
				if (streamData.ansi) (*streamData.stream) << ANSI_ESC_DRED;
			}
			return Logstream(&streams, LogLevel::Critical);
		}
	}
}
