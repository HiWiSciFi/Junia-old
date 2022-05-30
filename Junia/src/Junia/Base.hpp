#pragma once

#if defined(JELOG_MAX_TRACE)
	#define JE_ONLY_JELOG_MAX_TRACE(f) f
#else
	#define JE_ONLY_JELOG_MAX_TRACE(f)
#endif
#if defined(JELOG_MAX_TRACE) || defined(JELOG_MAX_INFO)
	#define JE_ONLY_JELOG_MAX_INFO(f)  f
#else
	#define JE_ONLY_JELOG_MAX_INFO(f)
#endif
#if defined(JELOG_MAX_TRACE) || defined(JELOG_MAX_INFO) || defined(JELOG_MAX_WARN)
	#define JE_ONLY_JELOG_MAX_WARN(f)  f
#else
	#define JE_ONLY_JELOG_MAX_WARN(f)
#endif
#if defined(JELOG_MAX_TRACE) || defined(JELOG_MAX_INFO) || defined(JELOG_MAX_WARN) || defined(JELOG_MAX_ERROR)
	#define JE_ONLY_JELOG_MAX_ERROR(f) f
#else
	#define JE_ONLY_JELOG_MAX_ERROR(f)
#endif
#if defined(JELOG_MAX_TRACE) || defined(JELOG_MAX_INFO) || defined(JELOG_MAX_WARN) || defined(JELOG_MAX_ERROR) || defined(JELOG_MAX_CRIT)
	#define JE_ONLY_JELOG_MAX_CRIT(f)  f
#else
	#define JE_ONLY_JELOG_MAX_CRIT(f)
#endif
