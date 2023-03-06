#pragma once

#include <Junia/Core/Logger.hpp>

namespace Junia { namespace Log { extern Logger corelog; } }

#define JECORELOG_TRACE        Junia::Log::corelog.Trace()
#define JECORELOG_INFO         Junia::Log::corelog.Info()
#define JECORELOG_WARN         Junia::Log::corelog.Warn()
#define JECORELOG_ERROR        Junia::Log::corelog.Error()
#define JECORELOG_CRITICAL     Junia::Log::corelog.Critical()

#define JECORELOG_DBG_TRACE    Junia::Log::corelog.Trace()    << "[" << __FILE__ << ":" << __LINE__ << "] "
#define JECORELOG_DBG_INFO     Junia::Log::corelog.Info()     << "[" << __FILE__ << ":" << __LINE__ << "] "
#define JECORELOG_DBG_WARN     Junia::Log::corelog.Warn()     << "[" << __FILE__ << ":" << __LINE__ << "] "
#define JECORELOG_DBG_ERROR    Junia::Log::corelog.Error()    << "[" << __FILE__ << ":" << __LINE__ << "] "
#define JECORELOG_DBG_CRITICAL Junia::Log::corelog.Critical() << "[" << __FILE__ << ":" << __LINE__ << "] "

namespace Vulkan { namespace Log { extern Junia::Log::Logger vkLog; } }

#define VKLOG_TRACE        Vulkan::Log::vkLog.Trace()
#define VKLOG_INFO         Vulkan::Log::vkLog.Info()
#define VKLOG_WARN         Vulkan::Log::vkLog.Warn()
#define VKLOG_ERROR        Vulkan::Log::vkLog.Error()
#define VKLOG_CRITICAL     Vulkan::Log::vkLog.Critical()

#define VKLOG_DBG_TRACE    Vulkan::Log::vkLog.Trace()    << "[" << __FILE__ << ":" << __LINE__ << "] "
#define VKLOG_DBG_INFO     Vulkan::Log::vkLog.Info()     << "[" << __FILE__ << ":" << __LINE__ << "] "
#define VKLOG_DBG_WARN     Vulkan::Log::vkLog.Warn()     << "[" << __FILE__ << ":" << __LINE__ << "] "
#define VKLOG_DBG_ERROR    Vulkan::Log::vkLog.Error()    << "[" << __FILE__ << ":" << __LINE__ << "] "
#define VKLOG_DBG_CRITICAL Vulkan::Log::vkLog.Critical() << "[" << __FILE__ << ":" << __LINE__ << "] "
