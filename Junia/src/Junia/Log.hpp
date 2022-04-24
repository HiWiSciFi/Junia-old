#pragma once

#include <spdlog/logger.h>
#include <spdlog/fmt/ostr.h>

#include "Base.hpp"

#ifndef JELOG_NONE
	#if defined(JELOG_MAX_TRACE)
		#define JELOG_BASE_TRACE(...) Junia::Log::JuniaLogTrace (__FILE__, __FUNCTION__, __LINE__, __VA_ARGS__)
		#define JELOG_TRACE(...)      Junia::Log::LogTrace      (__FILE__, __FUNCTION__, __LINE__, __VA_ARGS__)
	#else
		#define JELOG_BASE_TRACE(...)
		#define JELOG_TRACE(...)
	#endif

	#if defined(JELOG_MAX_TRACE) || defined(JELOG_MAX_INFO)
		#define JELOG_BASE_INFO(...)  Junia::Log::JuniaLogInfo  (__FILE__, __FUNCTION__, __LINE__, __VA_ARGS__)
		#define JELOG_INFO(...)       Junia::Log::LogInfo       (__FILE__, __FUNCTION__, __LINE__, __VA_ARGS__)
	#else
		#define JELOG_BASE_INFO(...)
		#define JELOG_INFO(...)
	#endif

	#if defined(JELOG_MAX_TRACE) || defined(JELOG_MAX_INFO) || defined(JELOG_MAX_WARN)
		#define JELOG_BASE_WARN(...)  Junia::Log::JuniaLogWarn  (__FILE__, __FUNCTION__, __LINE__, __VA_ARGS__)
		#define JELOG_WARN(...)       Junia::Log::LogWarn       (__FILE__, __FUNCTION__, __LINE__, __VA_ARGS__)
	#else
		#define JELOG_BASE_WARN(...)
		#define JELOG_WARN(...)
	#endif

	#if defined(JELOG_MAX_TRACE) || defined(JELOG_MAX_INFO) || defined(JELOG_MAX_WARN) || defined(JELOG_MAX_ERROR)
		#define JELOG_BASE_ERROR(...) Junia::Log::JuniaLogError (__FILE__, __FUNCTION__, __LINE__, __VA_ARGS__)
		#define JELOG_ERROR(...)      Junia::Log::LogError      (__FILE__, __FUNCTION__, __LINE__, __VA_ARGS__)
	#else
		#define JELOG_BASE_ERROR(...)
		#define JELOG_ERROR(...)
	#endif

	#if defined(JELOG_MAX_TRACE) || defined(JELOG_MAX_INFO) || defined(JELOG_MAX_WARN) || defined(JELOG_MAX_ERROR) || defined(JELOG_MAX_CRIT)
		#define JELOG_BASE_CRIT(...)  Junia::Log::JuniaLogCrit  (__FILE__, __FUNCTION__, __LINE__, __VA_ARGS__)
		#define JELOG_CRIT(...)       Junia::Log::LogCrit       (__FILE__, __FUNCTION__, __LINE__, __VA_ARGS__)
	#else
		#define JELOG_BASE_CRIT(...)
		#define JELOG_CRIT(...)
	#endif
#endif

namespace Junia {
	class JE_API_IO Log
	{
	public:
		static void Init();

		template<typename... Args> static void JuniaLogTrace (const char* file, const char* func, const size_t line, Args... args) {          juniaLogger->trace (args...); }
		template<typename... Args> static void LogTrace      (const char* file, const char* func, const size_t line, Args... args) {    applicationLogger->trace (args...); }
		template<typename... Args> static void JuniaLogInfo  (const char* file, const char* func, const size_t line, Args... args) {           juniaLogger->info (args...); }
		template<typename... Args> static void LogInfo       (const char* file, const char* func, const size_t line, Args... args) {     applicationLogger->info (args...); }
		template<typename... Args> static void JuniaLogWarn  (const char* file, const char* func, const size_t line, Args... args) {           juniaLogger->warn (args...); }
		template<typename... Args> static void LogWarn       (const char* file, const char* func, const size_t line, Args... args) {     applicationLogger->warn (args...); }
		template<typename... Args> static void JuniaLogError (const char* file, const char* func, const size_t line, Args... args) {          juniaLogger->error (args...); }
		template<typename... Args> static void LogError      (const char* file, const char* func, const size_t line, Args... args) {    applicationLogger->error (args...); }
		template<typename... Args> static void JuniaLogCrit  (const char* file, const char* func, const size_t line, Args... args) {       juniaLogger->critical (args...); }
		template<typename... Args> static void LogCrit       (const char* file, const char* func, const size_t line, Args... args) { applicationLogger->critical (args...); }

	private:
		static std::shared_ptr<spdlog::logger> juniaLogger;
		static std::shared_ptr<spdlog::logger> applicationLogger;
	};
}
