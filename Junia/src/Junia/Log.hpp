#pragma once

#include <Junia/Logger.hpp>

#define JELOG_CHAR       "%s"
#define JELOG_CSTR        "%s"
#define JELOG_SHORT      "%hi"
#define JELOG_USHORT     "%hu"
#define JELOG_LONGDOUBLE "%Lf"
#define JELOG_NONE       "%n"
#define JELOG_INT_B10    "%d"
#define JELOG_INT        "%i" // detects base automatically
#define JELOG_INT_B8     "%o"
#define JELOG_INT_B16    "%x"
#define JELOG_PTR        "%p"
#define JELOG_FLOAT      "%f"
#define JELOG_UINT       "%u"
#define JELOG_SFLOAT     "%e"
#define JELOG_PERCENT    "%%"

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
	#define JELOG_BASE_INFO(...)
	#define JELOG_INFO(...)
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

namespace Junia {
	class Log
	{
	public:
		static void Init();

#if defined(JELOG_EXTENDED_INFO)
		template<typename... Args> static void JuniaLogTrace (const char* file, const size_t line, const char* str, Args... args) {          juniaLogger->Trace ("[at " + std::string(file) + ":" + std::to_string(line) + "] " + std::string(str), args...); }
		template<typename... Args> static void LogTrace      (const char* file, const size_t line, const char* str, Args... args) {    applicationLogger->Trace ("[at " + std::string(file) + ":" + std::to_string(line) + "] " + std::string(str), args...); }
		template<typename... Args> static void JuniaLogInfo  (const char* file, const size_t line, const char* str, Args... args) {           juniaLogger->Info ("[at " + std::string(file) + ":" + std::to_string(line) + "] " + std::string(str), args...); }
		template<typename... Args> static void LogInfo       (const char* file, const size_t line, const char* str, Args... args) {     applicationLogger->Info ("[at " + std::string(file) + ":" + std::to_string(line) + "] " + std::string(str), args...); }
		template<typename... Args> static void JuniaLogWarn  (const char* file, const size_t line, const char* str, Args... args) {           juniaLogger->Warn ("[at " + std::string(file) + ":" + std::to_string(line) + "] " + std::string(str), args...); }
		template<typename... Args> static void LogWarn       (const char* file, const size_t line, const char* str, Args... args) {     applicationLogger->Warn ("[at " + std::string(file) + ":" + std::to_string(line) + "] " + std::string(str), args...); }
		template<typename... Args> static void JuniaLogError (const char* file, const size_t line, const char* str, Args... args) {          juniaLogger->Error ("[at " + std::string(file) + ":" + std::to_string(line) + "] " + std::string(str), args...); }
		template<typename... Args> static void LogError      (const char* file, const size_t line, const char* str, Args... args) {    applicationLogger->Error ("[at " + std::string(file) + ":" + std::to_string(line) + "] " + std::string(str), args...); }
		template<typename... Args> static void JuniaLogCrit  (const char* file, const size_t line, const char* str, Args... args) {       juniaLogger->Critical ("[at " + std::string(file) + ":" + std::to_string(line) + "] " + std::string(str), args...); }
		template<typename... Args> static void LogCrit       (const char* file, const size_t line, const char* str, Args... args) { applicationLogger->Critical ("[at " + std::string(file) + ":" + std::to_string(line) + "] " + std::string(str), args...); }
#else
		template<typename... Args> static void JuniaLogTrace (const char* file, const size_t line, const char* str, Args... args) {           juniaLogger->Trace(str, args...); }
		template<typename... Args> static void LogTrace      (const char* file, const size_t line, const char* str, Args... args) {     applicationLogger->Trace(str, args...); }
		template<typename... Args> static void JuniaLogInfo  (const char* file, const size_t line, const char* str, Args... args) {            juniaLogger->Info(str, args...); }
		template<typename... Args> static void LogInfo       (const char* file, const size_t line, const char* str, Args... args) {      applicationLogger->Info(str, args...); }
		template<typename... Args> static void JuniaLogWarn  (const char* file, const size_t line, const char* str, Args... args) {            juniaLogger->Warn(str, args...); }
		template<typename... Args> static void LogWarn       (const char* file, const size_t line, const char* str, Args... args) {      applicationLogger->Warn(str, args...); }
		template<typename... Args> static void JuniaLogError (const char* file, const size_t line, const char* str, Args... args) {           juniaLogger->Error(str, args...); }
		template<typename... Args> static void LogError      (const char* file, const size_t line, const char* str, Args... args) {     applicationLogger->Error(str, args...); }
		template<typename... Args> static void JuniaLogCrit  (const char* file, const size_t line, const char* str, Args... args) {        juniaLogger->Critical(str, args...); }
		template<typename... Args> static void LogCrit       (const char* file, const size_t line, const char* str, Args... args) {  applicationLogger->Critical(str, args...); }
#endif

	private:
		static std::shared_ptr<Logger> juniaLogger;
		static std::shared_ptr<Logger> applicationLogger;
	};
}
