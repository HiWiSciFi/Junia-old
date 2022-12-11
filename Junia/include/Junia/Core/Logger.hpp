#pragma once
#include <fstream>
#include <string>
#include <sstream>

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

		class Logstream
		{
		public:
			/**
			* @brief Creates a Logstream from an std::ostream*
			*/
			Logstream(std::ostream* stream);
			/**
			* @brief Copies a Logstream
			*/
			Logstream(const Logstream& other);
			/**
			* @brief Resets ANSI Escape codes, adds a linebreak and flushes the
			*        stream
			*/
			~Logstream();

			/**
			* @brief Inserts a value into the log buffer
			* @return a reference to this Logstream
			*/
			template<typename T> Logstream& operator<<(T const& value)
			{
				(*stream) << value;
				return *this;
			}

		private:
			std::ostream* stream = nullptr;
		};

		class Logger
		{
		public:
			/**
			* @brief Creates a Logger with an empty name writing to stdout
			*/
			Logger();
			/**
			* @brief Creates a Logger writing to stdout
			* @param name the name for the Logger
			*/
			Logger(const std::string& name);
			/**
			* @brief Creates a Logger writing to an existing stream
			* @param name the name for the Logger
			* @param stream a pointer to an opened stream that this Logger shall
			*        write to
			*/
			Logger(const std::string& name, std::ostream* stream);
			/**
			* @brief Creates a Logger writing to a file
			* @param name the name for the Logger
			* @param path the path to the file the Logger should write to. The
			*        file will be created if it doesn't exist.
			*/
			Logger(const std::string& name, const std::string& path);

			/**
			* @brief disposes of the stream the Logger is writing to if it was
			*        opened by the Logger
			*/
			~Logger();

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
			bool ownStream = false;
			std::ostream* stream;
		};
	}
}
