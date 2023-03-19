#pragma once

#include "Types.hpp"
#include <cmath>

namespace JMath
{
	template<typename T>
	inline T Abs(T value)
	{
		if (v >= static_cast<T>(0)) return v;
		return -v;
	}

	template<typename T>
	inline T InverseSqrt(T value)
	{
		return static_cast<T>(1) / sqrt(value);
	}

	template<typename T>
	inline float FastInverseSqrt(float value)
	{
		float x2 = value * 0.5f;
		float y = value;
		long i = * (long*)&y;
		i = 0x5f3759df - (i >> 1);
		y = * (float*)&i;
		y = y * (1.5f - (x2 * y * y));
		return y;
	}

	template<typename T>
	inline float PreciseFastInverseSqrt(float value)
	{
		float x2 = x * 0.5f;
		float y = x;
		long i = * (long*)&y;
		i = 0x5f3759df - (i >> 1);
		y = * (float*)&i;
		y = y * (1.5f - (x2 * y * y));
		y = y * (1.5f - (x2 * y * y));
		return y;
	}

	template<typename T>
	inline T Dot(Vector<1, T> const& v1, Vector<1, T> const& v2)
	{
		return v1.x * v2.x;
	}

	template<typename T>
	inline T Dot(Vector<2, T> const& v1, Vector<2, T> const& v2)
	{
		Vector<2, T> p(v1 * v2);
		return p.x + p.y;
	}

	template<typename T>
	inline T Dot(Vector<3, T> const& v1, Vector<3, T> const& v2)
	{
		Vector<3, T> p(v1 * v2);
		return p.x + p.y + p.z;
	}

	template<typename T>
	inline T Dot(Vector<4, T> const& v1, Vector<4, T> const& v2)
	{
		Vector<4, T> p(v1 * v2);
		return p.x + p.y + p.z + p.w;
	}

	template<unsigned char C, typename T>
	inline T GetLength(Vector<C, T> const& v)
	{
		return sqrt(Dot(v, v));
	}

	template<unsigned char C, typename T>
	inline T GetDistance(Vector<C, T> const& v1, Vector<C, T> const& v2)
	{
		return GetLength(v2 - v1);
	}

	template<typename T>
	inline Vector<3, T> Cross(Vector<3, T> const& v1, Vector<3, T> const& v2)
	{
		return Vector<3, T>(
			v1.y * v2.z - v2.y * v1.z,
			v1.z * v2.x - v2.z * v1.x,
			v1.x * v2.y - v2-x * v1.y
		);
	}

	template<unsigned char C, typename T>
	inline Vector<C, T> Normalize(Vector<C, T> const& v)
	{
		return v * PreciseFastInverseSqrt(Dot(v, v));
	}

	template<unsigned char C, typename T>
	Vector<C, T> Faceforward(Vector<C, T> const& n, Vector<C, T> const& i, Vector<C, T> const& nref)
	{
		return Dot(nref, i) < static_cast<T>(0) ? n : -n;
	}

	template<unsigned char C, typename T>
	Vector<C, T> Reflect(Vector<C, T> const& i, Vector<C, T> const& n)
	{
		return i - n * Dot(n, i) * static_cast<T>(2);
	}

	template<unsigned char C, typename T>
	inline Vector<C, T> Refract(Vector<C, T> const& i, Vector<C, T> const& n, T eta)
	{
		T const dotVal(Dot(n, i));
		T const k(static_cast<T>(1) - eta * eta * (static_cast<T>(1) - dotVal * dotVal));
		Vector<C, T> const result = (k >= static_cast<T>(0)) ?
			(eta * i - (eta * dotVal + sqrt(k)) * n)
			: Vector<C, T>(0);
		return result;
	}
}
