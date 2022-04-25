#pragma once

#include <spdlog/logger.h>
#include <spdlog/fmt/ostr.h>

#include "Base.hpp"

#ifndef JELOG_NONE
	#if defined(JELOG_MAX_TRACE)
		#define JELOG_BASE_TRACE(str, ...) Junia::Log::JuniaLogTrace (__FILE__, __LINE__, str, __VA_ARGS__)
		#define JELOG_TRACE(str, ...)      Junia::Log::LogTrace      (__FILE__, __LINE__, str, __VA_ARGS__)
	#else
		#define JELOG_BASE_TRACE(...)
		#define JELOG_TRACE(...)
	#endif

	#if defined(JELOG_MAX_TRACE) || defined(JELOG_MAX_INFO)
		#define JELOG_BASE_INFO(str, ...)  Junia::Log::JuniaLogInfo  (__FILE__, __LINE__, str, __VA_ARGS__)
		#define JELOG_INFO(str, ...)       Junia::Log::LogInfo       (__FILE__, __LINE__, str, __VA_ARGS__)
	#else
		#define JELOG_BASE_INFO(str, ...)
		#define JELOG_INFO(str, ...)
	#endif

	#if defined(JELOG_MAX_TRACE) || defined(JELOG_MAX_INFO) || defined(JELOG_MAX_WARN)
		#define JELOG_BASE_WARN(str, ...)  Junia::Log::JuniaLogWarn  (__FILE__, __LINE__, str, __VA_ARGS__)
		#define JELOG_WARN(str, ...)       Junia::Log::LogWarn       (__FILE__, __LINE__, str, __VA_ARGS__)
	#else
		#define JELOG_BASE_WARN(...)
		#define JELOG_WARN(...)
	#endif

	#if defined(JELOG_MAX_TRACE) || defined(JELOG_MAX_INFO) || defined(JELOG_MAX_WARN) || defined(JELOG_MAX_ERROR)
		#define JELOG_BASE_ERROR(str, ...) Junia::Log::JuniaLogError (__FILE__, __LINE__, str, __VA_ARGS__)
		#define JELOG_ERROR(str, ...)      Junia::Log::LogError      (__FILE__, __LINE__, str, __VA_ARGS__)
	#else
		#define JELOG_BASE_ERROR(...)
		#define JELOG_ERROR(...)
	#endif

	#if defined(JELOG_MAX_TRACE) || defined(JELOG_MAX_INFO) || defined(JELOG_MAX_WARN) || defined(JELOG_MAX_ERROR) || defined(JELOG_MAX_CRIT)
		#define JELOG_BASE_CRIT(str, ...)  Junia::Log::JuniaLogCrit  (__FILE__, __LINE__, str, __VA_ARGS__)
		#define JELOG_CRIT(str, ...)       Junia::Log::LogCrit       (__FILE__, __LINE__, str, __VA_ARGS__)
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

#if defined(JELOG_EXTENDED_INFO)
		template<typename... Args> static void JuniaLogTrace (const char* file, const size_t line, const char* str, Args... args) {          juniaLogger->trace ("[at " + std::string(file) + ":" + std::to_string(line) + "] " + std::string(str), args...); }
		template<typename... Args> static void LogTrace      (const char* file, const size_t line, const char* str, Args... args) {    applicationLogger->trace ("[at " + std::string(file) + ":" + std::to_string(line) + "] " + std::string(str), args...); }
		template<typename... Args> static void JuniaLogInfo  (const char* file, const size_t line, const char* str, Args... args) {           juniaLogger->info ("[at " + std::string(file) + ":" + std::to_string(line) + "] " + std::string(str), args...); }
		template<typename... Args> static void LogInfo       (const char* file, const size_t line, const char* str, Args... args) {     applicationLogger->info ("[at " + std::string(file) + ":" + std::to_string(line) + "] " + std::string(str), args...); }
		template<typename... Args> static void JuniaLogWarn  (const char* file, const size_t line, const char* str, Args... args) {           juniaLogger->warn ("[at " + std::string(file) + ":" + std::to_string(line) + "] " + std::string(str), args...); }
		template<typename... Args> static void LogWarn       (const char* file, const size_t line, const char* str, Args... args) {     applicationLogger->warn ("[at " + std::string(file) + ":" + std::to_string(line) + "] " + std::string(str), args...); }
		template<typename... Args> static void JuniaLogError (const char* file, const size_t line, const char* str, Args... args) {          juniaLogger->error ("[at " + std::string(file) + ":" + std::to_string(line) + "] " + std::string(str), args...); }
		template<typename... Args> static void LogError      (const char* file, const size_t line, const char* str, Args... args) {    applicationLogger->error ("[at " + std::string(file) + ":" + std::to_string(line) + "] " + std::string(str), args...); }
		template<typename... Args> static void JuniaLogCrit  (const char* file, const size_t line, const char* str, Args... args) {       juniaLogger->critical ("[at " + std::string(file) + ":" + std::to_string(line) + "] " + std::string(str), args...); }
		template<typename... Args> static void LogCrit       (const char* file, const size_t line, const char* str, Args... args) { applicationLogger->critical ("[at " + std::string(file) + ":" + std::to_string(line) + "] " + std::string(str), args...); }
#else
		template<typename... Args> static void JuniaLogTrace (const char* file, const size_t line, const char* str, Args... args) {           juniaLogger->trace(str, args...); }
		template<typename... Args> static void LogTrace      (const char* file, const size_t line, const char* str, Args... args) {     applicationLogger->trace(str, args...); }
		template<typename... Args> static void JuniaLogInfo  (const char* file, const size_t line, const char* str, Args... args) {            juniaLogger->info(str, args...); }
		template<typename... Args> static void LogInfo       (const char* file, const size_t line, const char* str, Args... args) {      applicationLogger->info(str, args...); }
		template<typename... Args> static void JuniaLogWarn  (const char* file, const size_t line, const char* str, Args... args) {            juniaLogger->warn(str, args...); }
		template<typename... Args> static void LogWarn       (const char* file, const size_t line, const char* str, Args... args) {      applicationLogger->warn(str, args...); }
		template<typename... Args> static void JuniaLogError (const char* file, const size_t line, const char* str, Args... args) {           juniaLogger->error(str, args...); }
		template<typename... Args> static void LogError      (const char* file, const size_t line, const char* str, Args... args) {     applicationLogger->error(str, args...); }
		template<typename... Args> static void JuniaLogCrit  (const char* file, const size_t line, const char* str, Args... args) {        juniaLogger->critical(str, args...); }
		template<typename... Args> static void LogCrit       (const char* file, const size_t line, const char* str, Args... args) {  applicationLogger->critical(str, args...); }
#endif

	private:
		static std::shared_ptr<spdlog::logger> juniaLogger;
		static std::shared_ptr<spdlog::logger> applicationLogger;
	};
}
