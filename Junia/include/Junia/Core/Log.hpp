#pragma once

#include "Logger.hpp"

namespace Junia
{
	namespace Log
	{
		extern Logger log;
		extern Logger corelog;
	}
}

#define JELOG_TRACE        Junia::Log::log.Trace()
#define JELOG_INFO         Junia::Log::log.Info()
#define JELOG_WARN         Junia::Log::log.Warn()
#define JELOG_ERROR        Junia::Log::log.Error()
#define JELOG_CRITICAL     Junia::Log::log.Critical()

#define JELOG_DBG_TRACE    Junia::Log::log.Trace()    << "[" << __FILE__ << ":" << __LINE__ << "] "
#define JELOG_DBG_INFO     Junia::Log::log.Info()     << "[" << __FILE__ << ":" << __LINE__ << "] "
#define JELOG_DBG_WARN     Junia::Log::log.Warn()     << "[" << __FILE__ << ":" << __LINE__ << "] "
#define JELOG_DBG_ERROR    Junia::Log::log.Error()    << "[" << __FILE__ << ":" << __LINE__ << "] "
#define JELOG_DBG_CRITICAL Junia::Log::log.Critical() << "[" << __FILE__ << ":" << __LINE__ << "] "

#ifdef BUILD_JUNIA
#define JELOG_CORE_TRACE        Junia::Log::corelog.Trace()
#define JELOG_CORE_INFO         Junia::Log::corelog.Info()
#define JELOG_CORE_WARN         Junia::Log::corelog.Warn()
#define JELOG_CORE_ERROR        Junia::Log::corelog.Error()
#define JELOG_CORE_CRITICAL     Junia::Log::corelog.Critical()

#define JELOG_CORE_DBG_TRACE    Junia::Log::corelog.Trace()    << "[" << __FILE__ << ":" << __LINE__ << "] "
#define JELOG_CORE_DBG_INFO     Junia::Log::corelog.Info()     << "[" << __FILE__ << ":" << __LINE__ << "] "
#define JELOG_CORE_DBG_WARN     Junia::Log::corelog.Warn()     << "[" << __FILE__ << ":" << __LINE__ << "] "
#define JELOG_CORE_DBG_ERROR    Junia::Log::corelog.Error()    << "[" << __FILE__ << ":" << __LINE__ << "] "
#define JELOG_CORE_DBG_CRITICAL Junia::Log::corelog.Critical() << "[" << __FILE__ << ":" << __LINE__ << "] "
#endif
