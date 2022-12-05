#pragma once
#include <memory>
#include <fstream>
#include <string>
#include <sstream>

namespace Junia
{
	namespace Log
	{
		enum class LogLevel : uint8_t
		{
			None = 0,
			Critical = 1,
			Error = 2,
			Warn = 3,
			Info = 4,
			Trace = 5
		};

		class Logstream
		{
		public:
			Logstream(std::ofstream& _stream);
			Logstream(const Logstream& other);
			~Logstream();

			template<typename T>
			Logstream& operator<<(T const& value)
			{
				stream << value;
				return *this;
			}

		private:
			std::ofstream& stream;
		};

		class Logger
		{
		public:
			Logger();
			explicit Logger(const std::string& name);
			explicit Logger(const std::string& name, const std::string& path);

			/// @brief DO NOT COPY LOGGERS
			Logger(const Logger& other);

			~Logger();

			Logstream Trace();
			Logstream Info();
			Logstream Warn();
			Logstream Error();
			Logstream Critical();

			LogLevel maxLevel = LogLevel::Trace;

		private:
			std::string name = "";
			std::ofstream stream;
		};
	}
}
