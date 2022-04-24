#include "juniapch.hpp"
#include "Log.hpp"

#include "spdlog/spdlog.h"
#include "spdlog/sinks/stdout_color_sinks.h"

namespace Junia
{
	std::shared_ptr<spdlog::logger> Log::juniaLogger;
	std::shared_ptr<spdlog::logger> Log::applicationLogger;

	void Log::Init()
	{
		spdlog::set_pattern("%^[%Y-%m-%d %T] %n %v%$");

		juniaLogger = spdlog::stdout_color_mt("[Junia]");
		juniaLogger->set_level(spdlog::level::trace);

		applicationLogger = spdlog::stdout_color_mt("  [App]");
		applicationLogger->set_level(spdlog::level::trace);

		JELOG_BASE_WARN("Logger initialized!");
		JELOG_TRACE("Still works!");
		JELOG_INFO("idk how tbh...");
		JELOG_BASE_ERROR("err");
		JELOG_BASE_CRIT("REEE");
	}
}
