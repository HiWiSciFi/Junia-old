#include "juniapch.h"
#include "Log.h"

//#include <spdlog/sinks/stdout_color_sinks.h>
#include <plog/Log.h>
#include "plog/Initializers/RollingFileInitializer.h"
#include "plog/Appenders/ColorConsoleAppender.h"

namespace Junia
{
	/*std::shared_ptr<spdlog::logger> Log::s_CoreLogger;
	std::shared_ptr<spdlog::logger> Log::s_ClientLogger;*/

	void Log::Init()
	{
		static plog::ColorConsoleAppender<plog::TxtFormatter> consoleAppender;
		plog::init(plog::debug, &consoleAppender); // Step2: initialize the logger

		// Step3: write log messages using a special macro
		// There are several log macros, use the macro you liked the most

		PLOGD << "Hello log!"; // short macro
		PLOG_DEBUG << "Hello log!"; // long macro
		PLOG(plog::debug) << "Hello log!"; // function-style macro

		// Also you can use LOG_XXX macro but it may clash with other logging libraries
		LOGD << "Hello log!"; // short macro
		LOG_DEBUG << "Hello log!"; // long macro
		LOG(plog::debug) << "Hello log!"; // function-style macro
	}
}
