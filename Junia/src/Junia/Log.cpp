#include "Log.hpp"

#include <iostream>
#include <Junia/Base.hpp>

namespace Junia
{
	Ref<Logger> Log::juniaLogger;
	Ref<Logger> Log::applicationLogger;

	void Log::Init()
	{
		juniaLogger = Logger::Create("Junia");
		applicationLogger = Logger::Create(" App ");

	#ifdef JELOG_EXTENDED_INFO
		JE_ONLY_JELOG_MAX_TRACE(std::cout << "[Junia-preinit] [at " << __FILE__ << ":" << __LINE__ << "] Initializing Logger..." << std::endl);
	#else
		JE_ONLY_JELOG_MAX_TRACE(std::cout << "[Junia-preinit] Main function called" << std::endl);
	#endif

		//spdlog::set_pattern("%^[%Y-%m-%d %T] %n %v%$");

	#ifdef JELOG_EXTENDED_INFO
		JE_ONLY_JELOG_MAX_TRACE(std::cout << "[Junia-preinit] [at " << __FILE__ << ":" << __LINE__ << "] Creating Junia Logger..." << std::endl);
	#else
		JE_ONLY_JELOG_MAX_TRACE(std::cout << "[Junia-preinit] Creating Junia Logger..." << std::endl);
	#endif

	#ifdef JELOG_EXTENDED_INFO
		JE_ONLY_JELOG_MAX_TRACE(std::cout << "[Junia-preinit] [at " << __FILE__ << ":" << __LINE__ << "] Creating Application Logger..." << std::endl);
	#else
		JE_ONLY_JELOG_MAX_TRACE(std::cout << "[Junia-preinit] Creating Application Logger..." << std::endl);
	#endif

		JELOG_BASE_INFO("Logger initialized!");
	}
}
