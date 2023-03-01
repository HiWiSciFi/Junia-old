#define BUILD_JUNIA

//#include <functional>
//
//template<uint32_t Id, typename RT, typename... TArgs>
//struct ClikeFunction
//{
//	static std::function<RT(TArgs...)> function;
//
//	static void Bind(const std::function<RT(TArgs...)>& f)
//	{
//		if (!function)
//		{
//			function = f;
//			function(nullptr, 0);
//		}
//		else
//		{
//			throw std::runtime_error("Cannot rebind function - consider using another id");
//		}
//	}
//
//	static RT Invoke(TArgs... args)
//	{
//		return function(args...);
//	}
//
//	private:
//		ClikeFunction() { }
//};
//
//template<uint32_t Id, typename RT, typename... TArgs>
//std::function<RT(TArgs...)> ClikeFunction<Id, RT, TArgs...>::function{ };
