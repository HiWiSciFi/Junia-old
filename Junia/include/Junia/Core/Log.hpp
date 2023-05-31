#pragma once

#include "Logger.hpp"

namespace Junia::Log {
	extern Logger log;
} // namespace Junia::Log

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
