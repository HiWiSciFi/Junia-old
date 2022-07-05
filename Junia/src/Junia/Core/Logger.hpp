#pragma once
#include <string>
#include <sstream>
#include <Junia/Core/Base.hpp>

namespace Junia
{
	class Logger
	{
	public:
		explicit Logger(const std::string& name);

		~Logger() = default;

		static Ref<Logger> Create(const std::string& name = "Logger");

		void Trace    (const std::string fmt, ...) const;
		void Info     (const std::string fmt, ...) const;
		void Warn     (const std::string fmt, ...) const;
		void Error    (const std::string fmt, ...) const;
		void Critical (const std::string fmt, ...) const;

	private:
		std::string name = "";
	};
}
