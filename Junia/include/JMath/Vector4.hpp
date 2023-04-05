#pragma once

#include "Types.hpp"
#include <cstdint>

namespace JMath
{
	template<typename T>
	struct Vector<4, T>
	{
		//////////
		// DATA //
		//////////

		union { T x, r; };
		union { T y, g; };
		union { T z, b; };
		union { T w, a; };

		////////////
		// ACCESS //
		////////////

		#pragma region AccessFuncs
		static constexpr unsigned char length() { return 4; }

		constexpr T& operator[](unsigned char index)
		{
			switch (index)
			{
			default:
			case 0:
				return x;
			case 1:
				return y;
			case 2:
				return z;
			case 3:
				return w;
			}
		}

		constexpr T const& operator[](unsigned char index) const
		{
			switch (index)
			{
			default:
			case 0:
				return x;
			case 1:
				return y;
			case 2:
				return z;
			case 3:
				return w;
			}
		}
		#pragma endregion

		//////////////////
		// CONSTRUCTORS //
		//////////////////

		#pragma region ConstructorsBase
		constexpr Vector() = default;
		constexpr Vector(Vector const& v) = default;

		constexpr explicit Vector(T s) : x(s), y(s), z(s), w(s) { }
		constexpr Vector(T _x, T _y, T _z, T _w) : x(_x), y(_y), z(_z), w(_w) { }

		template<typename U> constexpr explicit Vector(Vector<1, U> const& v) :
			x(static_cast<T>(v.x)),
			y(static_cast<T>(v.x)),
			z(static_cast<T>(v.x)),
			w(static_cast<T>(v.x))
		{
		}
		#pragma endregion

		#pragma region ConstructorsScalar
		template<typename X, typename Y, typename Z, typename W> constexpr Vector(X _x, Y _y, Z _z, W _w) :
			x(static_cast<T>(_x)),
			y(static_cast<T>(_y)),
			z(static_cast<T>(_z)),
			w(static_cast<T>(_w))
		{
		}
		template<typename X, typename Y, typename Z, typename W> constexpr Vector(Vector<1, X> const& _x, Y _y, Z _z, W _w) :
			x(static_cast<T>(_x.x)),
			y(static_cast<T>(_y)),
			z(static_cast<T>(_z)),
			w(static_cast<T>(_w))
		{
		}
		template<typename X, typename Y, typename Z, typename W> constexpr Vector(X _x, Vector<1, Y> const& _y, Z _z, W _w) :
			x(static_cast<T>(_x)),
			y(static_cast<T>(_y.x)),
			z(static_cast<T>(_z)),
			w(static_cast<T>(_w))
		{
		}
		template<typename X, typename Y, typename Z, typename W> constexpr Vector(Vector<1, X> const& _x, Vector<1, Y> const& _y, Z _z, W _w) :
			x(static_cast<T>(_x.x)),
			y(static_cast<T>(_y.x)),
			z(static_cast<T>(_z)),
			w(static_cast<T>(_w))
		{
		}
		template<typename X, typename Y, typename Z, typename W> constexpr Vector(X _x, Y _y, Vector<1, Z> const& _z, W _w) :
			x(static_cast<T>(_x)),
			y(static_cast<T>(_y)),
			z(static_cast<T>(_z.x)),
			w(static_cast<T>(_w))
		{
		}
		template<typename X, typename Y, typename Z, typename W> constexpr Vector(Vector<1, X> const& _x, Y _y, Vector<1, Z> const& _z, W _w) :
			x(static_cast<T>(_x.x)),
			y(static_cast<T>(_y)),
			z(static_cast<T>(_z.x)),
			w(static_cast<T>(_w))
		{
		}
		template<typename X, typename Y, typename Z, typename W> constexpr Vector(X _x, Vector<1, Y> const& _y, Vector<1, Z> const& _z, W _w) :
			x(static_cast<T>(_x)),
			y(static_cast<T>(_y.x)),
			z(static_cast<T>(_z.x)),
			w(static_cast<T>(_w))
		{
		}
		template<typename X, typename Y, typename Z, typename W> constexpr Vector(Vector<1, X> const& _x, Vector<1, Y> const& _y, Vector<1, Z> const& _z, W _w) :
			x(static_cast<T>(_x.x)),
			y(static_cast<T>(_y.x)),
			z(static_cast<T>(_z.x)),
			w(static_cast<T>(_w))
		{
		}
		template<typename X, typename Y, typename Z, typename W> constexpr Vector(X _x, Y _y, Z _z, Vector<1, W> const& _w) :
			x(static_cast<T>(_x)),
			y(static_cast<T>(_y)),
			z(static_cast<T>(_z)),
			w(static_cast<T>(_w.x))
		{
		}
		template<typename X, typename Y, typename Z, typename W> constexpr Vector(Vector<1, X> const& _x, Y _y, Z _z, Vector<1, W> const& _w) :
			x(static_cast<T>(_x.x)),
			y(static_cast<T>(_y)),
			z(static_cast<T>(_z)),
			w(static_cast<T>(_w.x))
		{
		}
		template<typename X, typename Y, typename Z, typename W> constexpr Vector(X _x, Vector<1, Y> const& _y, Z _z, Vector<1, W> const& _w) :
			x(static_cast<T>(_x)),
			y(static_cast<T>(_y.x)),
			z(static_cast<T>(_z)),
			w(static_cast<T>(_w.x))
		{
		}
		template<typename X, typename Y, typename Z, typename W> constexpr Vector(Vector<1, X> const& _x, Vector<1, Y> const& _y, Z _z, Vector<1, W> const& _w) :
			x(static_cast<T>(_x.x)),
			y(static_cast<T>(_y.x)),
			z(static_cast<T>(_z)),
			w(static_cast<T>(_w.x))
		{
		}
		template<typename X, typename Y, typename Z, typename W> constexpr Vector(X _x, Y _y, Vector<1, Z> const& _z, Vector<1, W> const& _w) :
			x(static_cast<T>(_x)),
			y(static_cast<T>(_y)),
			z(static_cast<T>(_z.x)),
			w(static_cast<T>(_w.x))
		{
		}
		template<typename X, typename Y, typename Z, typename W> constexpr Vector(Vector<1, X> const& _x, Y _y, Vector<1, Z> const& _z, Vector<1, W> const& _w) :
			x(static_cast<T>(_x.x)),
			y(static_cast<T>(_y)),
			z(static_cast<T>(_z.x)),
			w(static_cast<T>(_w.x))
		{
		}
		template<typename X, typename Y, typename Z, typename W> constexpr Vector(X _x, Vector<1, Y> const& _y, Vector<1, Z> const& _z, Vector<1, W> const& _w) :
			x(static_cast<T>(_x)),
			y(static_cast<T>(_y.x)),
			z(static_cast<T>(_z.x)),
			w(static_cast<T>(_w.x))
		{
		}
		template<typename X, typename Y, typename Z, typename W> constexpr Vector(Vector<1, X> const& _x, Vector<1, Y> const& _y, Vector<1, Z> const& _z, Vector<1, W> const& _w) :
			x(static_cast<T>(_x.x)),
			y(static_cast<T>(_y.x)),
			z(static_cast<T>(_z.x)),
			w(static_cast<T>(_w.x))
		{
		}
		#pragma endregion

		#pragma region ConstructorsVectors
		template<typename A, typename B, typename C> constexpr Vector(Vector<2, A> const& _xy, B _z, C _w) :
			x(static_cast<T>(_xy.x)),
			y(static_cast<T>(_xy.y)),
			z(static_cast<T>(_z)),
			w(static_cast<T>(_w))
		{
		}
		template<typename A, typename B, typename C> constexpr Vector(Vector<2, A> const& _xy, Vector<1, B> const& _z, C _w) :
			x(static_cast<T>(_xy.x)),
			y(static_cast<T>(_xy.y)),
			z(static_cast<T>(_z.x)),
			w(static_cast<T>(_w))
		{
		}
		template<typename A, typename B, typename C> constexpr Vector(Vector<2, A> const& _xy, B _z, Vector<1, C> const& _w) :
			x(static_cast<T>(_xy.x)),
			y(static_cast<T>(_xy.y)),
			z(static_cast<T>(_z)),
			w(static_cast<T>(_w.x))
		{
		}
		template<typename A, typename B, typename C> constexpr Vector(Vector<2, A> const& _xy, Vector<1, B> const& _z, Vector<1, C> const& _w) :
			x(static_cast<T>(_xy.x)),
			y(static_cast<T>(_xy.y)),
			z(static_cast<T>(_z.x)),
			w(static_cast<T>(_w.x))
		{
		}
		template<typename A, typename B, typename C> constexpr Vector(A _x, Vector<2, B> const& _yz, C _w) :
			x(static_cast<T>(_x)),
			y(static_cast<T>(_yz.x)),
			z(static_cast<T>(_yz.y)),
			w(static_cast<T>(_w))
		{
		}
		template<typename A, typename B, typename C> constexpr Vector(Vector<1, A> const& _x, Vector<2, B> const& _yz, C _w) :
			x(static_cast<T>(_x.x)),
			y(static_cast<T>(_yz.x)),
			z(static_cast<T>(_yz.y)),
			w(static_cast<T>(_w))
		{
		}
		template<typename A, typename B, typename C> constexpr Vector(A _x, Vector<2, B> const& _yz, Vector<1, C> const& _w) :
			x(static_cast<T>(_x)),
			y(static_cast<T>(_yz.x)),
			z(static_cast<T>(_yz.y)),
			w(static_cast<T>(_w.x))
		{
		}
		template<typename A, typename B, typename C> constexpr Vector(Vector<1, A> const& _x, Vector<2, B> const& _yz, Vector<1, C> const& _w) :
			x(static_cast<T>(_x.x)),
			y(static_cast<T>(_yz.x)),
			z(static_cast<T>(_yz.y)),
			w(static_cast<T>(_w.x))
		{
		}
		template<typename A, typename B, typename C> constexpr Vector(A _x, B _y, Vector<2, C> const& _zw) :
			x(static_cast<T>(_x)),
			y(static_cast<T>(_y)),
			z(static_cast<T>(_zw.x)),
			w(static_cast<T>(_zw.y))
		{
		}
		template<typename A, typename B, typename C> constexpr Vector(Vector<1, A> const& _x, B _y, Vector<2, C> const& _zw) :
			x(static_cast<T>(_x.x)),
			y(static_cast<T>(_y)),
			z(static_cast<T>(_zw.x)),
			w(static_cast<T>(_zw.y))
		{
		}
		template<typename A, typename B, typename C> constexpr Vector(A _x, Vector<1, B> const& _y, Vector<2, C> const& _zw) :
			x(static_cast<T>(_x)),
			y(static_cast<T>(_y.x)),
			z(static_cast<T>(_zw.x)),
			w(static_cast<T>(_zw.y))
		{
		}
		template<typename A, typename B, typename C> constexpr Vector(Vector<1, A> const& _x, Vector<1, B> const& _y, Vector<2, C> const& _zw) :
			x(static_cast<T>(_x.x)),
			y(static_cast<T>(_y.x)),
			z(static_cast<T>(_zw.x)),
			w(static_cast<T>(_zw.y))
		{
		}
		template<typename A, typename B> constexpr Vector(Vector<3, A> const& _xyz, B _w) :
			x(static_cast<T>(_xyz.x)),
			y(static_cast<T>(_xyz.y)),
			z(static_cast<T>(_xyz.z)),
			w(static_cast<T>(_w))
		{
		}
		template<typename A, typename B> constexpr Vector(Vector<3, A> const& _xyz, Vector<1, B> const& _w) :
			x(static_cast<T>(_xyz.x)),
			y(static_cast<T>(_xyz.y)),
			z(static_cast<T>(_xyz.z)),
			w(static_cast<T>(_w.x))
		{
		}
		template<typename A, typename B> constexpr Vector(A _x, Vector<3, B> const& _yzw) :
			x(static_cast<T>(_x)),
			y(static_cast<T>(_yzw.x)),
			z(static_cast<T>(_yzw.y)),
			w(static_cast<T>(_yzw.z))
		{
		}
		template<typename A, typename B> constexpr Vector(Vector<1, A> const& _x, Vector<3, B> const& _yzw) :
			x(static_cast<T>(_x.x)),
			y(static_cast<T>(_yzw.x)),
			z(static_cast<T>(_yzw.y)),
			w(static_cast<T>(_yzw.z))
		{
		}
		template<typename A, typename B> constexpr Vector(Vector<2, A> _xy, Vector<2, B> const& _zw) :
			x(static_cast<T>(_xy.x)),
			y(static_cast<T>(_xy.y)),
			z(static_cast<T>(_zw.x)),
			w(static_cast<T>(_zw.y))
		{
		}
		#pragma endregion

		#pragma region ConstructorsSize
		template<typename U> constexpr explicit Vector(Vector<4, U> const& v) :
			x(static_cast<T>(v.x)),
			y(static_cast<T>(v.y)),
			z(static_cast<T>(v.z)),
			w(static_cast<T>(v.w))
		{
		}
		#pragma endregion

		//////////////////////////
		// ASSIGNMENT OPERATORS //
		//////////////////////////

		#pragma region AOperators=
		constexpr Vector<4, T>& operator=(Vector<4, T> const& v) = default;
		template<typename U> constexpr Vector<4, T>& operator=(Vector<4, U> const& v)
		{
			this->x = static_cast<T>(v.x);
			this->y = static_cast<T>(v.y);
			this->z = static_cast<T>(v.z);
			this->w = static_cast<T>(v.w);
			return *this;
		}
		#pragma endregion

		#pragma region AOperators+=
		template<typename U> constexpr Vector<4, T>& operator+=(U s)
		{
			this->x += static_cast<T>(s);
			this->y += static_cast<T>(s);
			this->z += static_cast<T>(s);
			this->w += static_cast<T>(s);
			return *this;
		}
		template<typename U> constexpr Vector<4, T>& operator+=(Vector<1, U> const& v)
		{
			this->x += static_cast<T>(v.x);
			this->y += static_cast<T>(v.x);
			this->z += static_cast<T>(v.x);
			this->w += static_cast<T>(v.x);
			return *this;
		}
		template<typename U> constexpr Vector<4, T>& operator+=(Vector<4, U> const& v)
		{
			this->x += static_cast<T>(v.x);
			this->y += static_cast<T>(v.y);
			this->z += static_cast<T>(v.z);
			this->w += static_cast<T>(v.w);
			return *this;
		}
		#pragma endregion

		#pragma region AOperators-=
		template<typename U> constexpr Vector<4, T>& operator-=(U s)
		{
			this->x -= static_cast<T>(s);
			this->y -= static_cast<T>(s);
			this->z -= static_cast<T>(s);
			this->w -= static_cast<T>(s);
			return *this;
		}
		template<typename U> constexpr Vector<4, T>& operator-=(Vector<1, U> const& v)
		{
			this->x -= static_cast<T>(v.x);
			this->y -= static_cast<T>(v.x);
			this->z -= static_cast<T>(v.x);
			this->w -= static_cast<T>(v.x);
			return *this;
		}
		template<typename U> constexpr Vector<4, T>& operator-=(Vector<4, U> const& v)
		{
			this->x -= static_cast<T>(v.x);
			this->y -= static_cast<T>(v.y);
			this->z -= static_cast<T>(v.z);
			this->w -= static_cast<T>(v.w);
			return *this;
		}
		#pragma endregion

		#pragma region AOperators*=
		template<typename U> constexpr Vector<4, T>& operator*=(U s)
		{
			this->x *= static_cast<T>(s);
			this->y *= static_cast<T>(s);
			this->z *= static_cast<T>(s);
			this->w *= static_cast<T>(s);
			return *this;
		}
		template<typename U> constexpr Vector<4, T>& operator*=(Vector<1, U> const& v)
		{
			this->x *= static_cast<T>(v.x);
			this->y *= static_cast<T>(v.x);
			this->z *= static_cast<T>(v.x);
			this->w *= static_cast<T>(v.x);
			return *this;
		}
		template<typename U> constexpr Vector<4, T>& operator*=(Vector<4, U> const& v)
		{
			this->x *= static_cast<T>(v.x);
			this->y *= static_cast<T>(v.y);
			this->z *= static_cast<T>(v.z);
			this->w *= static_cast<T>(v.w);
			return *this;
		}
		#pragma endregion

		#pragma region AOperators/=
		template<typename U> constexpr Vector<4, T>& operator/=(U s)
		{
			this->x /= static_cast<T>(s);
			this->y /= static_cast<T>(s);
			this->z /= static_cast<T>(s);
			this->w /= static_cast<T>(s);
			return *this;
		}
		template<typename U> constexpr Vector<4, T>& operator/=(Vector<1, U> const& v)
		{
			this->x /= static_cast<T>(v.x);
			this->y /= static_cast<T>(v.x);
			this->z /= static_cast<T>(v.x);
			this->w /= static_cast<T>(v.x);
			return *this;
		}
		template<typename U> constexpr Vector<4, T>& operator/=(Vector<4, U> const& v)
		{
			this->x /= static_cast<T>(v.x);
			this->y /= static_cast<T>(v.y);
			this->z /= static_cast<T>(v.z);
			this->w /= static_cast<T>(v.w);
			return *this;
		}
		#pragma endregion

		#pragma region AOperators%=
		template<typename U> constexpr Vector<4, T>& operator%=(U s)
		{
			this->x %= static_cast<T>(s);
			this->y %= static_cast<T>(s);
			this->z %= static_cast<T>(s);
			this->w %= static_cast<T>(s);
			return *this;
		}
		template<typename U> constexpr Vector<4, T>& operator%=(Vector<1, U> v)
		{
			this->x %= static_cast<T>(v.x);
			this->y %= static_cast<T>(v.x);
			this->z %= static_cast<T>(v.x);
			this->w %= static_cast<T>(v.x);
			return *this;
		}
		template<typename U> constexpr Vector<4, T>& operator%=(Vector<4, U> v)
		{
			this->x %= static_cast<T>(v.x);
			this->y %= static_cast<T>(v.y);
			this->z %= static_cast<T>(v.z);
			this->w %= static_cast<T>(v.w);
			return *this;
		}
		#pragma endregion

		#pragma region AOperators&=
		template<typename U> constexpr Vector<4, T>& operator&=(U s)
		{
			this->x &= static_cast<T>(s);
			this->y &= static_cast<T>(s);
			this->z &= static_cast<T>(s);
			this->w &= static_cast<T>(s);
			return *this;
		}
		template<typename U> constexpr Vector<4, T>& operator&=(Vector<1, U> v)
		{
			this->x &= static_cast<T>(v.x);
			this->y &= static_cast<T>(v.x);
			this->z &= static_cast<T>(v.x);
			this->w &= static_cast<T>(v.x);
			return *this;
		}
		template<typename U> constexpr Vector<4, T>& operator&=(Vector<4, U> v)
		{
			this->x &= static_cast<T>(v.x);
			this->y &= static_cast<T>(v.y);
			this->z &= static_cast<T>(v.z);
			this->w &= static_cast<T>(v.w);
			return *this;
		}
		#pragma endregion

		#pragma region AOperators|=
		template<typename U> constexpr Vector<4, T>& operator|=(U s)
		{
			this->x |= static_cast<T>(s);
			this->y |= static_cast<T>(s);
			this->z |= static_cast<T>(s);
			this->w |= static_cast<T>(s);
			return *this;
		}
		template<typename U> constexpr Vector<4, T>& operator|=(Vector<1, U> v)
		{
			this->x |= static_cast<T>(v.x);
			this->y |= static_cast<T>(v.x);
			this->z |= static_cast<T>(v.x);
			this->w |= static_cast<T>(v.x);
			return *this;
		}
		template<typename U> constexpr Vector<4, T>& operator|=(Vector<4, U> v)
		{
			this->x |= static_cast<T>(v.x);
			this->y |= static_cast<T>(v.y);
			this->z |= static_cast<T>(v.z);
			this->w |= static_cast<T>(v.w);
			return *this;
		}
		#pragma endregion

		#pragma region AOperators^=
		template<typename U> constexpr Vector<4, T>& operator^=(U s)
		{
			this->x ^= static_cast<T>(s);
			this->y ^= static_cast<T>(s);
			this->z ^= static_cast<T>(s);
			this->w ^= static_cast<T>(s);
			return *this;
		}
		template<typename U> constexpr Vector<4, T>& operator^=(Vector<1, U> v)
		{
			this->x ^= static_cast<T>(v.x);
			this->y ^= static_cast<T>(v.x);
			this->z ^= static_cast<T>(v.x);
			this->w ^= static_cast<T>(v.x);
			return *this;
		}
		template<typename U> constexpr Vector<4, T>& operator^=(Vector<4, U> v)
		{
			this->x ^= static_cast<T>(v.x);
			this->y ^= static_cast<T>(v.y);
			this->z ^= static_cast<T>(v.z);
			this->w ^= static_cast<T>(v.w);
			return *this;
		}
		#pragma endregion

		#pragma region AOperators<<=
		template<typename U> constexpr Vector<4, T>& operator<<=(U s)
		{
			this->x <<= static_cast<T>(s);
			this->y <<= static_cast<T>(s);
			this->z <<= static_cast<T>(s);
			this->w <<= static_cast<T>(s);
			return *this;
		}
		template<typename U> constexpr Vector<4, T>& operator<<=(Vector<1, U> v)
		{
			this->x <<= static_cast<T>(v.x);
			this->y <<= static_cast<T>(v.x);
			this->z <<= static_cast<T>(v.x);
			this->w <<= static_cast<T>(v.x);
			return *this;
		}
		template<typename U> constexpr Vector<4, T>& operator<<=(Vector<4, U> v)
		{
			this->x <<= static_cast<T>(v.x);
			this->y <<= static_cast<T>(v.y);
			this->z <<= static_cast<T>(v.z);
			this->w <<= static_cast<T>(v.w);
			return *this;
		}
		#pragma endregion

		#pragma region AOperators>>=
		template<typename U> constexpr Vector<4, T>& operator>>=(U s)
		{
			this->x >>= static_cast<T>(s);
			this->y >>= static_cast<T>(s);
			this->z >>= static_cast<T>(s);
			this->w >>= static_cast<T>(s);
			return *this;
		}
		template<typename U> constexpr Vector<4, T>& operator>>=(Vector<1, U> v)
		{
			this->x >>= static_cast<T>(v.x);
			this->y >>= static_cast<T>(v.x);
			this->z >>= static_cast<T>(v.x);
			this->w >>= static_cast<T>(v.x);
			return *this;
		}
		template<typename U> constexpr Vector<4, T>& operator>>=(Vector<4, U> v)
		{
			this->x >>= static_cast<T>(v.x);
			this->y >>= static_cast<T>(v.y);
			this->z >>= static_cast<T>(v.z);
			this->w >>= static_cast<T>(v.w);
			return *this;
		}
		#pragma endregion

		/////////////////////////
		// INCREMENT OPERATORS //
		/////////////////////////

		#pragma region IOperators
		constexpr Vector<4, T>& operator++()
		{
			++this->x;
			++this->y;
			++this->z;
			++this->w;
			return *this;
		}
		constexpr Vector<4, T>& operator--()
		{
			--this->x;
			--this->y;
			--this->z;
			--this->w;
			return *this;
		}
		constexpr const Vector<4, T> operator++(int)
		{
			Vector<4, T> result(*this);
			++(*this);
			return result;
		}
		constexpr const Vector<4, T> operator--(int)
		{
			Vector<4, T> result(*this);
			--(*this);
			return result;
		}
		#pragma endregion
	};

	////////////////////
	// CALC OPERATORS //
	////////////////////

	#pragma region COperators+
	template<typename T> constexpr Vector<4, T> operator+(Vector<4, T> const& v)
	{
		return v;
	}
	template<typename T> constexpr Vector<4, T> operator+(Vector<4, T> const& v, T s)
	{
		return Vector<4, T>(v.x + s, v.y + s, v.z + s, v.w + s);
	}
	template<typename T> constexpr Vector<4, T> operator+(Vector<4, T> const& v, Vector<1, T> const& s)
	{
		return Vector<4, T>(v.x + s.x, v.y + s.x, v.z + s.x, v.w + s.x);
	}
	template<typename T> constexpr Vector<4, T> operator+(T s, Vector<4, T> const& v)
	{
		return Vector<4, T>(s + v.x, s + v.y, s + v.z, s + v.w);
	}
	template<typename T> constexpr Vector<4, T> operator+(Vector<1, T> const& s, Vector<4, T> const& v)
	{
		return Vector<4, T>(s.x + v.x, s.x + v.y, s.x + v.z, s.x + v.w);
	}
	template<typename T> constexpr Vector<4, T> operator+(Vector<4, T> const& v1, Vector<4, T> const& v2)
	{
		return Vector<4, T>(v1.x + v2.x, v1.y + v2.y, v1.z + v2.z, v1.w + v2.w);
	}
	#pragma endregion

	#pragma region COperators-
	template<typename T> constexpr Vector<4, T> operator-(Vector<4, T> const& v)
	{
		return Vector<3, T>(-v.x, -v.y, -v.z, -v.w);
	}
	template<typename T> constexpr Vector<4, T> operator-(Vector<4, T> const& v, T s)
	{
		return Vector<4, T>(v.x - s, v.y - s, v.z - s, v.w - s);
	}
	template<typename T> constexpr Vector<4, T> operator-(Vector<4, T> const& v, Vector<1, T> const& s)
	{
		return Vector<4, T>(v.x - s.x, v.y - s.x, v.z - s.x, v.w - s.x);
	}
	template<typename T> constexpr Vector<4, T> operator-(T s, Vector<4, T> const& v)
	{
		return Vector<4, T>(s - v.x, s - v.y, s - v.z, s - v.w);
	}
	template<typename T> constexpr Vector<4, T> operator-(Vector<1, T> const& s, Vector<4, T> const& v)
	{
		return Vector<4, T>(s.x - v.x, s.x - v.y, s.x - v.z, s.x - v.w);
	}
	template<typename T> constexpr Vector<4, T> operator-(Vector<4, T> const& v1, Vector<4, T> const& v2)
	{
		return Vector<4, T>(v1.x - v2.x, v1.y - v2.y, v1.z - v2.z, v1.w - v2.w);
	}
	#pragma endregion

	#pragma region COperators*
	template<typename T> constexpr Vector<4, T> operator*(Vector<4, T> const& v, T s)
	{
		return Vector<4, T>(v.x * s, v.y * s, v.z * s, v.w * s);
	}
	template<typename T> constexpr Vector<4, T> operator*(Vector<4, T> const& v, Vector<1, T> const& s)
	{
		return Vector<4, T>(v.x * s.x, v.y * s.x, v.z * s.x, v.w * s.x);
	}
	template<typename T> constexpr Vector<4, T> operator*(T s, Vector<4, T> const& v)
	{
		return Vector<4, T>(s * v.x, s * v.y, s * v.z, s * v.w);
	}
	template<typename T> constexpr Vector<4, T> operator*(Vector<1, T> const& s, Vector<4, T> const& v)
	{
		return Vector<4, T>(s.x * v.x, s.x * v.y, s.x * v.z, s.x * v.w);
	}
	template<typename T> constexpr Vector<4, T> operator*(Vector<4, T> const& v1, Vector<4, T> const& v2)
	{
		return Vector<4, T>(v1.x * v2.x, v1.y * v2.y, v1.z * v2.z, v1.w * v2.w);
	}
	#pragma endregion

	#pragma region COperators/
	template<typename T> constexpr Vector<4, T> operator/(Vector<4, T> const& v, T s)
	{
		return Vector<4, T>(v.x / s, v.y / s, v.z / s, v.w / s);
	}
	template<typename T> constexpr Vector<4, T> operator/(Vector<4, T> const& v, Vector<1, T> const& s)
	{
		return Vector<4, T>(v.x / s.x, v.y / s.x, v.z / s.x, v.w / s.x);
	}
	template<typename T> constexpr Vector<4, T> operator/(T s, Vector<4, T> const& v)
	{
		return Vector<4, T>(s / v.x, s / v.y, s / v.z, s / v.w);
	}
	template<typename T> constexpr Vector<4, T> operator/(Vector<1, T> const& s, Vector<4, T> const& v)
	{
		return Vector<4, T>(s.x / v.x, s.x / v.y, s.x / v.z, s.x / v.w);
	}
	template<typename T> constexpr Vector<4, T> operator/(Vector<4, T> const& v1, Vector<4, T> const& v2)
	{
		return Vector<4, T>(v1.x / v2.x, v1.y / v2.y, v1.z / v2.z, v1.w / v2.w);
	}
	#pragma endregion

	#pragma region COperators%
	template<typename T> constexpr Vector<4, T> operator%(Vector<4, T> const& v, T s)
	{
		return Vector<4, T>(v.x % s, v.y % s, v.z % s, v.w % s);
	}
	template<typename T> constexpr Vector<4, T> operator%(Vector<4, T> const& v, Vector<1, T> const& s)
	{
		return Vector<4, T>(v.x % s.x, v.y % s.x, v.z % s.x, v.w % s.x);
	}
	template<typename T> constexpr Vector<4, T> operator%(T s, Vector<4, T> const& v)
	{
		return Vector<4, T>(s % v.x, s % v.y, s % v.z, s % v.w);
	}
	template<typename T> constexpr Vector<4, T> operator%(Vector<1, T> const& s, Vector<4, T> const& v)
	{
		return Vector<4, T>(s.x % v.x, s.x % v.y, s.x % v.z, s.x % v.w);
	}
	template<typename T> constexpr Vector<4, T> operator%(Vector<4, T> const& v1, Vector<4, T> const& v2)
	{
		return Vector<4, T>(v1.x % v2.x, v1.y % v2.y, v1.z % v2.z, v1.w % v2.w);
	}
	#pragma endregion

	#pragma region COperators&
	template<typename T> constexpr Vector<4, T> operator&(Vector<4, T> const& v, T s)
	{
		return Vector<4, T>(v.x & s, v.y & s, v.z & s, v.w & s);
	}
	template<typename T> constexpr Vector<4, T> operator&(Vector<4, T> const& v, Vector<1, T> const& s)
	{
		return Vector<4, T>(v.x & s.x, v.y & s.x, v.z & s.x, v.w & s.x);
	}
	template<typename T> constexpr Vector<4, T> operator&(T s, Vector<4, T> const& v)
	{
		return Vector<4, T>(s & v.x, s & v.y, s & v.z, s & v.w);
	}
	template<typename T> constexpr Vector<4, T> operator&(Vector<1, T> const& s, Vector<4, T> const& v)
	{
		return Vector<4, T>(s.x & v.x, s.x & v.y, s.x & v.z, s.x & v.w);
	}
	template<typename T> constexpr Vector<4, T> operator&(Vector<4, T> const& v1, Vector<4, T> const& v2)
	{
		return Vector<4, T>(v1.x & v2.x, v1.y & v2.y, v1.z & v2.z, v1.w & v2.w);
	}
	#pragma endregion

	#pragma region COperators|
	template<typename T> constexpr Vector<4, T> operator|(Vector<4, T> const& v, T s)
	{
		return Vector<4, T>(v.x | s, v.y | s, v.z | s, v.w | s);
	}
	template<typename T> constexpr Vector<4, T> operator|(Vector<4, T> const& v, Vector<1, T> const& s)
	{
		return Vector<4, T>(v.x | s.x, v.y | s.x, v.z | s.x, v.w | s.x);
	}
	template<typename T> constexpr Vector<4, T> operator|(T s, Vector<4, T> const& v)
	{
		return Vector<4, T>(s | v.x, s | v.y, s | v.z, s | v.w);
	}
	template<typename T> constexpr Vector<4, T> operator|(Vector<1, T> const& s, Vector<4, T> const& v)
	{
		return Vector<4, T>(s.x | v.x, s.x | v.y, s.x | v.z, s.x | v.w);
	}
	template<typename T> constexpr Vector<4, T> operator|(Vector<4, T> const& v1, Vector<4, T> const& v2)
	{
		return Vector<4, T>(v1.x | v2.x, v1.y | v2.y, v1.z | v2.z, v1.w | v2.w);
	}
	#pragma endregion

	#pragma region COperators^
	template<typename T> constexpr Vector<4, T> operator^(Vector<4, T> const& v, T s)
	{
		return Vector<4, T>(v.x ^ s, v.y ^ s, v.z ^ s, v.w ^ s);
	}
	template<typename T> constexpr Vector<4, T> operator^(Vector<4, T> const& v, Vector<1, T> const& s)
	{
		return Vector<4, T>(v.x ^ s.x, v.y ^ s.x, v.z ^ s.x, v.w ^ s.x);
	}
	template<typename T> constexpr Vector<4, T> operator^(T s, Vector<4, T> const& v)
	{
		return Vector<4, T>(s ^ v.x, s ^ v.y, s ^ v.z, s ^ v.w);
	}
	template<typename T> constexpr Vector<4, T> operator^(Vector<1, T> const& s, Vector<4, T> const& v)
	{
		return Vector<4, T>(s.x ^ v.x, s.x ^ v.y, s.x ^ v.z, s.x ^ v.w);
	}
	template<typename T> constexpr Vector<4, T> operator^(Vector<4, T> const& v1, Vector<4, T> const& v2)
	{
		return Vector<4, T>(v1.x ^ v2.x, v1.y ^ v2.y, v1.z ^ v2.z, v1.w ^ v2.w);
	}
	#pragma endregion

	#pragma region COperators<<
	template<typename T> constexpr Vector<4, T> operator<<(Vector<4, T> const& v, T s)
	{
		return Vector<4, T>(v.x << s, v.y << s, v.z << s, v.w << s);
	}
	template<typename T> constexpr Vector<4, T> operator<<(Vector<4, T> const& v, Vector<1, T> const& s)
	{
		return Vector<4, T>(v.x << s.x, v.y << s.x, v.z << s.x, v.w << s.x);
	}
	template<typename T> constexpr Vector<4, T> operator<<(T s, Vector<4, T> const& v)
	{
		return Vector<4, T>(s << v.x, s << v.y, s << v.z, s << v.w);
	}
	template<typename T> constexpr Vector<4, T> operator<<(Vector<1, T> const& s, Vector<4, T> const& v)
	{
		return Vector<4, T>(s.x << v.x, s.x << v.y, s.x << v.z, s.x << v.w);
	}
	template<typename T> constexpr Vector<4, T> operator<<(Vector<4, T> const& v1, Vector<4, T> const& v2)
	{
		return Vector<4, T>(v1.x << v2.x, v1.y << v2.y, v1.z << v2.z, v1.w << v2.w);
	}
	#pragma endregion

	#pragma region COperators>>
	template<typename T> constexpr Vector<4, T> operator>>(Vector<4, T> const& v, T s)
	{
		return Vector<4, T>(v.x >> s, v.y >> s, v.z >> s, v.w >> s);
	}
	template<typename T> constexpr Vector<4, T> operator>>(Vector<4, T> const& v, Vector<1, T> const& s)
	{
		return Vector<4, T>(v.x >> s.x, v.y >> s.x, v.z >> s.x, v.w >> s.x);
	}
	template<typename T> constexpr Vector<4, T> operator>>(T s, Vector<4, T> const& v)
	{
		return Vector<4, T>(s >> v.x, s >> v.y, s >> v.z, s >> v.w);
	}
	template<typename T> constexpr Vector<4, T> operator>>(Vector<1, T> const& s, Vector<4, T> const& v)
	{
		return Vector<4, T>(s.x >> v.x, s.x >> v.y, s.x >> v.z, s.x >> v.w);
	}
	template<typename T> constexpr Vector<4, T> operator>>(Vector<4, T> const& v1, Vector<4, T> const& v2)
	{
		return Vector<4, T>(v1.x >> v2.x, v1.y >> v2.y, v1.z >> v2.z, v1.w >> v2.w);
	}
	#pragma endregion

	#pragma region COperators~
	template<typename T> constexpr Vector<4, T> operator~(Vector<4, T> const& v)
	{
		return Vector<4, T>(~v.x, ~v.y, ~v.z, ~v.w);
	}
	#pragma endregion

	///////////////////////
	// BOOLEAN OPERATORS //
	///////////////////////

	#pragma region BOperators
	template<typename T> constexpr bool operator==(Vector<4, T> const& v1, Vector<4, T> const& v2)
	{
		return (v1.x == v2.x) && (v1.y == v2.y) && (v1.z == v2.z) && (v1.w == v2.w);
	}
	template<typename T> constexpr bool operator!=(Vector<4, T> const& v1, Vector<4, T> const& v2)
	{
		return (v1.x != v2.x) || (v1.y != v2.y) || (v1.z != v2.z) || (v1.w != v2.w);
	}
	template<typename T> constexpr Vector<4, bool> operator&&(Vector<4, T> const& v1, Vector<4, T> const& v2)
	{
		return Vector<4, bool>(v1.x && v2.x, v1.y && v2.y, v1.z && v2.z, v1.w && v2.w);
	}
	template<typename T> constexpr Vector<4, bool> operator||(Vector<4, T> const& v1, Vector<4, T> const& v2)
	{
		return Vector<4, bool>(v1.x || v2.x, v1.y || v2.y, v1.z || v2.z, v1.w || v2.w);
	}
	#pragma endregion

	//////////////////////
	// TYPE DEFINITIONS //
	//////////////////////

	typedef Vector< 4, float    >   Vec4;
	typedef Vector< 4, float    >  fVec4;
	typedef Vector< 4, double   >  dVec4;
	typedef Vector< 4, int32_t  >  iVec4;
	typedef Vector< 4, uint32_t > uiVec4;
	typedef Vector< 4, bool     >  bVec4;
} // namespace JMath
