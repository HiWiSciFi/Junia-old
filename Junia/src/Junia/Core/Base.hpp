#pragma once

#include <memory>

#if defined(JELOG_MAX_TRACE)
	#define JE_ONLY_JELOG_MAX_TRACE(f) f
#else
	#define JE_ONLY_JELOG_MAX_TRACE(f) while(0)
#endif
#if defined(JELOG_MAX_TRACE) || defined(JELOG_MAX_INFO)
	#define JE_ONLY_JELOG_MAX_INFO(f)  f
#else
	#define JE_ONLY_JELOG_MAX_INFO(f) while(0)
#endif
#if defined(JELOG_MAX_TRACE) || defined(JELOG_MAX_INFO) || defined(JELOG_MAX_WARN)
	#define JE_ONLY_JELOG_MAX_WARN(f)  f
#else
	#define JE_ONLY_JELOG_MAX_WARN(f) while(0)
#endif
#if defined(JELOG_MAX_TRACE) || defined(JELOG_MAX_INFO) || defined(JELOG_MAX_WARN) || defined(JELOG_MAX_ERROR)
	#define JE_ONLY_JELOG_MAX_ERROR(f) f
#else
	#define JE_ONLY_JELOG_MAX_ERROR(f) while(0)
#endif
#if defined(JELOG_MAX_TRACE) || defined(JELOG_MAX_INFO) || defined(JELOG_MAX_WARN) || defined(JELOG_MAX_ERROR) || defined(JELOG_MAX_CRIT)
	#define JE_ONLY_JELOG_MAX_CRIT(f)  f
#else
	#define JE_ONLY_JELOG_MAX_CRIT(f) while(0)
#endif

namespace Junia
{
	template<typename T>
	using Scope = std::unique_ptr<T>;
	template<typename T, typename ...Args>
	constexpr Scope<T> CreateScope(Args&& ...args) { return std::make_unique<T>(std::forward<Args>(args)...); }

	template<typename T>
	using Ref = std::shared_ptr<T>;
	template <typename T, typename ...Args>
	constexpr Ref<T> CreateRef(Args&& ...args) { return std::make_shared<T>(std::forward<Args>(args)...); }
}
