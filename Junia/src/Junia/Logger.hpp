#pragma once
#include <string>
#include <sstream>

namespace Junia
{
	class Logger
	{
	public:
		Logger(std::string name);

		~Logger() = default;

		static std::shared_ptr<Logger> Create(std::string name = "Logger");

		void Trace    (const std::string fmt, ...) const;
		void Info     (const std::string fmt, ...) const;
		void Warn     (const std::string fmt, ...) const;
		void Error    (const std::string fmt, ...) const;
		void Critical (const std::string fmt, ...) const;

	private:
		std::string name;
	};
}
