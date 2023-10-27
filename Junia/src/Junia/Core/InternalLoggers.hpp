#pragma once

#include <Junia/Core/Logger.hpp>

namespace Junia::Log { extern Logger corelog; }

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

namespace Junia::Vulkan::Log { extern Junia::Log::Logger vkLog; }

#define VKLOG_TRACE        Junia::Vulkan::Log::vkLog.Trace()
#define VKLOG_INFO         Junia::Vulkan::Log::vkLog.Info()
#define VKLOG_WARN         Junia::Vulkan::Log::vkLog.Warn()
#define VKLOG_ERROR        Junia::Vulkan::Log::vkLog.Error()
#define VKLOG_CRITICAL     Junia::Vulkan::Log::vkLog.Critical()

#define VKLOG_DBG_TRACE    Junia::Vulkan::Log::vkLog.Trace()    << "[" << __FILE__ << ":" << __LINE__ << "] "
#define VKLOG_DBG_INFO     Junia::Vulkan::Log::vkLog.Info()     << "[" << __FILE__ << ":" << __LINE__ << "] "
#define VKLOG_DBG_WARN     Junia::Vulkan::Log::vkLog.Warn()     << "[" << __FILE__ << ":" << __LINE__ << "] "
#define VKLOG_DBG_ERROR    Junia::Vulkan::Log::vkLog.Error()    << "[" << __FILE__ << ":" << __LINE__ << "] "
#define VKLOG_DBG_CRITICAL Junia::Vulkan::Log::vkLog.Critical() << "[" << __FILE__ << ":" << __LINE__ << "] "

namespace GLFW::Log { extern Junia::Log::Logger glfwLog; }

#define GLFWLOG_TRACE        GLFW::Log::glfwLog.Trace()
#define GLFWLOG_INFO         GLFW::Log::glfwLog.Info()
#define GLFWLOG_WARN         GLFW::Log::glfwLog.Warn()
#define GLFWLOG_ERROR        GLFW::Log::glfwLog.Error()
#define GLFWLOG_CRITICAL     GLFW::Log::glfwLog.Critical()

#define GLFWLOG_DBG_TRACE    GLFW::Log::glfwLog.Trace()    << "[" << __FILE__ << ":" << __LINE__ << "] "
#define GLFWLOG_DBG_INFO     GLFW::Log::glfwLog.Info()     << "[" << __FILE__ << ":" << __LINE__ << "] "
#define GLFWLOG_DBG_WARN     GLFW::Log::glfwLog.Warn()     << "[" << __FILE__ << ":" << __LINE__ << "] "
#define GLFWLOG_DBG_ERROR    GLFW::Log::glfwLog.Error()    << "[" << __FILE__ << ":" << __LINE__ << "] "
#define GLFWLOG_DBG_CRITICAL GLFW::Log::glfwLog.Critical() << "[" << __FILE__ << ":" << __LINE__ << "] "
