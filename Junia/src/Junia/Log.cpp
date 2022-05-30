#include "Log.hpp"

#include <iostream>

#include <spdlog/spdlog.h>
#include <spdlog/sinks/stdout_color_sinks.h>

namespace Junia
{
	std::shared_ptr<spdlog::logger> Log::juniaLogger;
	std::shared_ptr<spdlog::logger> Log::applicationLogger;

	void Log::Init()
	{
	#ifdef JELOG_EXTENDED_INFO
		JE_ONLY_JELOG_MAX_TRACE(std::cout << "[Junia-preinit] [at " << __FILE__ << ":" << __LINE__ << "] Initializing Logger..." << std::endl);
	#else
		JE_ONLY_JELOG_MAX_TRACE(std::cout << "[Junia-preinit] Main function called" << std::endl);
	#endif

		spdlog::set_pattern("%^[%Y-%m-%d %T] %n %v%$");

	#ifdef JELOG_EXTENDED_INFO
		JE_ONLY_JELOG_MAX_TRACE(std::cout << "[Junia-preinit] [at " << __FILE__ << ":" << __LINE__ << "] Creating Junia Logger..." << std::endl);
	#else
		JE_ONLY_JELOG_MAX_TRACE(std::cout << "[Junia-preinit] Creating Junia Logger..." << std::endl);
	#endif

		juniaLogger = spdlog::stdout_color_mt("[Junia]");
		juniaLogger->set_level(spdlog::level::trace);

	#ifdef JELOG_EXTENDED_INFO
		JE_ONLY_JELOG_MAX_TRACE(std::cout << "[Junia-preinit] [at " << __FILE__ << ":" << __LINE__ << "] Creating Application Logger..." << std::endl);
	#else
		JE_ONLY_JELOG_MAX_TRACE(std::cout << "[Junia-preinit] Creating Application Logger..." << std::endl);
	#endif

		applicationLogger = spdlog::stdout_color_mt(" [App] ");
		applicationLogger->set_level(spdlog::level::trace);

		JELOG_BASE_INFO("Logger initialized!");
	}
}
