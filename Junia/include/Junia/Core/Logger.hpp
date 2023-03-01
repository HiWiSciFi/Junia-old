#pragma once

#include <fstream>
#include <cinttypes>
#include <string>
#include <sstream>
#include <vector>

namespace Junia
{
	namespace Log
	{
		/**
		* @brief The Log level of a message (can be compared with &lt; and &gt;)
		*/
		enum class LogLevel : uint8_t
		{
			None = 0,     /** @brief LogLevel for no output */
			Critical = 1, /** @brief LogLevel for Critical messages */
			Error = 2,    /** @brief LogLevel for Error messages */
			Warn = 3,     /** @brief LogLevel for Warning messages */
			Info = 4,     /** @brief LogLevel for Info messages */
			Trace = 5     /** @brief LogLevel for Trace messages */
		};

		namespace Internal
		{
			struct StreamData
			{
				bool own = false;
				bool ansi = false;
				std::ostream* const stream;
			};
		}

		class Logstream
		{
		public:
			/**
			* @brief Create a Logstream from an std::ostream*
			*/
			Logstream(std::vector<Internal::StreamData>* streams, LogLevel level);
			/**
			* @brief Copy a Logstream
			*/
			Logstream(const Logstream& other);
			/**
			* @brief Reset ANSI Escape codes, adds a linebreak and flushes the
			*        stream
			*/
			~Logstream();

			/**
			* @brief Insert a value into the log buffer
			* @return a reference to this Logstream
			*/
			template<typename T> Logstream& operator<<(T const& value)
			{
				if (streams == nullptr) return *this;
				for (auto const& streamData : *streams) (*streamData.stream) << value;
				return *this;
			}

		private:
			LogLevel level;
			std::vector<Internal::StreamData>* streams = nullptr;
		};

		class Logger
		{
		public:
			/**
			* @brief Create a Logger with an empty name writing to stdout
			*/
			Logger();
			/**
			* @brief Create a Logger writing to stdout
			* @param name the name for the Logger
			*/
			Logger(const std::string& name);
			/**
			* @brief Create a Logger writing to an existing stream
			* @param name the name for the Logger
			* @param stream a pointer to an opened stream that this Logger shall
			*        write to
			* @param ansi if the stream should include ANSI Escape Sequences
			*/
			Logger(const std::string& name, std::ostream* const stream, bool ansi = true);
			/**
			* @brief Create a Logger writing to a file
			* @param name the name for the Logger
			* @param path the path to the file the Logger should write to. The
			*        file will be created if it doesn't exist.
			* @param ansi if the file should include ANSI Escape Sequences
			*/
			Logger(const std::string& name, const std::string& path, bool ansi = false);

			/**
			* @brief Dispose of the stream the Logger is writing to if it was
			*        opened by the Logger
			*/
			~Logger();

			/**
			* @brief Add an output stream the logger
			* @param stream a pointer to an opened stream that this Logger shall
			*        write to
			* @param ansi if the stream should include ANSI Escape Sequences
			*/
			void AddStream(std::ostream* const stream, bool ansi = true);

			/**
			* @brief Add a file output to the logger
			* @param path the path to the file the Logger should write to. The
			*        file will be created if it doesn't exist.
			* @param ansi if the file should include ANSI Escape Sequences
			*/
			void AddStream(const std::string& path, bool ansi = false);

			/**
			* @brief Write a trace message if the Logger::maxLevel &ge;
			*        LogLevel::Trace
			* @return a Logstream to write to (linebreak will be added upon
			*         disposal)
			*/
			Logstream Trace();
			/**
			* @brief Write an informative message if the Logger::maxLevel &ge;
			*        LogLevel::Info
			* @return a Logstream to write to (linebreak will be added upon
			*         disposal)
			*/
			Logstream Info();
			/**
			* @brief Write a warning message if the Logger::maxLevel &ge;
			*        LogLevel::Warn
			* @return a Logstream to write to (linebreak will be added upon
			*         disposal)
			*/
			Logstream Warn();
			/**
			* @brief Write an error message if the Logger::maxLevel &ge;
			*        LogLevel::Error
			* @return a Logstream to write to (linebreak will be added upon
			*         disposal)
			*/
			Logstream Error();
			/**
			* @brief Write a critical message if the Logger::maxLevel &ge;
			*        LogLevel::Critical
			* @return a Logstream to write to (linebreak will be added upon
			*         disposal)
			*/
			Logstream Critical();

			/**
			* @brief The maximum LogLevel that will be written by this Logger
			*/
			LogLevel maxLevel = LogLevel::Trace;

		private:
			Logger(const Logger& other);

			std::string name = "";
			std::vector<Internal::StreamData> streams{ };
		};
	}
}
