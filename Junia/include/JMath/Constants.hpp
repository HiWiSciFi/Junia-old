#pragma once

#include <limits>

namespace JMath
{
	/**
	 * @brief Get the numerical distance between 1 and the next number
	 *        representable by a numerical datatype
	 * @tparam T a floating-point datatype to get the epsilon value for
	 * @return the minimum positive value representable by the datatype
	*/
	template<typename T>
	inline constexpr T epsilon()
	{
		return std::numeric_limits<T>::epsilon();
	}

	/**
	 * @brief Get e constant
	 * @tparam T the datatype as which to return the constant
	 * @return e constant cast to the datatype
	*/
	template<typename T>
	inline constexpr T e()
	{
		return static_cast<T>(2.718281828459045);
	}

	/**
	 * @brief Get eulers constant
	 * @tparam T the datatype as which to return the constant
	 * @return euler constant cast to the datatype
	*/
	template<typename T>
	inline constexpr T euler()
	{
		return static_cast<T>(0.5772156649015329);
	}

	/**
	 * @brief Get golden ratio
	 * @tparam T the datatype as which to return the constant
	 * @return golden ratio constant cast to the datatype
	*/
	template<typename T>
	inline constexpr T golden_ratio()
	{
		return static_cast<T>(1.618033988749895);
	}

	template<typename T>
	inline constexpr T pi()
	{
		return static_cast<T>(3.141592653589793);
	}
}
