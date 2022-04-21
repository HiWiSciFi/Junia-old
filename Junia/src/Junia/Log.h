#pragma once

#include "Core.h"
#include "spdlog/spdlog.h"
#include "spdlog/fmt/ostr.h"

namespace Junia {
	class JUNIA_API Log
	{
	public:
		static void Init();

		inline static std::shared_ptr<spdlog::logger>& GetCoreLogger() { return s_CoreLogger; }
		inline static std::shared_ptr<spdlog::logger>& GetClientLogger() { return s_ClientLogger; }

	private:
		static std::shared_ptr<spdlog::logger> s_CoreLogger;
		static std::shared_ptr<spdlog::logger> s_ClientLogger;
	};
}

// Core log macros
#define JE_CORE_TRACE(...)    ::Junia::Log::GetCoreLogger()->trace(__VA_ARGS__)
#define JE_CORE_INFO(...)     ::Junia::Log::GetCoreLogger()->info(__VA_ARGS__)
#define JE_CORE_WARN(...)     ::Junia::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define JE_CORE_ERROR(...)    ::Junia::Log::GetCoreLogger()->error(__VA_ARGS__)
#define JE_CORE_FATAL(...)    ::Junia::Log::GetCoreLogger()->fatal(__VA_ARGS__)

// Client log macros
#define JE_TRACE(...)         ::Junia::Log::GetClientLogger()->trace(__VA_ARGS__)
#define JE_INFO(...)          ::Junia::Log::GetClientLogger()->info(__VA_ARGS__)
#define JE_WARN(...)          ::Junia::Log::GetClientLogger()->warn(__VA_ARGS__)
#define JE_ERROR(...)         ::Junia::Log::GetClientLogger()->error(__VA_ARGS__)
#define JE_FATAL(...)         ::Junia::Log::GetClientLogger()->fatal(__VA_ARGS__)