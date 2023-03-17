#pragma once

#include "Types.hpp"
#include <cstdint>

namespace JMath
{
	template<typename T>
	struct Vector<3, T>
	{
		//////////
		// DATA //
		//////////

		union { T x, r; };
		union { T y, g; };
		union { T z, b; };

		////////////
		// ACCESS //
		////////////

		#pragma region AccessFuncs
		static constexpr unsigned char length() { return 3; }

		constexpr T& operator[](unsigned char i)
		{
			switch (i)
			{
			default:
			case 0:
				return x;
			case 1:
				return y;
			case 2:
				return z;
			}
		}

		constexpr T const& operator[](unsigned char i) const
		{
			switch (i)
			{
			default:
			case 0:
				return x;
			case 1:
				return y;
			case 2:
				return z;
			}
		}
		#pragma endregion

		//////////////////
		// CONSTRUCTORS //
		//////////////////

		#pragma region ConstructorsBase
		constexpr Vector() = default;
		constexpr Vector(Vector const& v) = default;

		constexpr explicit Vector(T s) : x(s), y(s), z(s) { }
		constexpr Vector(T _x, T _y, T _z) : x(_x), y(_y), z(_z) { }

		template<typename U> constexpr explicit Vector(Vector<1, U> const& v) :
			x(static_cast<T>(v.x)),
			y(static_cast<T>(v.x)),
			z(static_cast<T>(v.x))
		{
		}
		#pragma endregion

		#pragma region ConstructorsScalar
		template<typename X, typename Y, typename Z> constexpr Vector(X _x, Y _y, Z _z) :
			x(static_cast<T>(_x)),
			y(static_cast<T>(_y)),
			z(static_cast<T>(_z))
		{
		}
		template<typename X, typename Y, typename Z> constexpr Vector(Vector<1, X> const& _x, Y _y, Z _z) :
			x(static_cast<T>(_x.x)),
			y(static_cast<T>(_y)),
			z(static_cast<T>(_z))
		{
		}
		template<typename X, typename Y, typename Z> constexpr Vector(X _x, Vector<1, Y> const& _y, Z _z) :
			x(static_cast<T>(_x)),
			y(static_cast<T>(_y.x)),
			z(static_cast<T>(_z))
		{
		}
		template<typename X, typename Y, typename Z> constexpr Vector(Vector<1, X> const& _x, Vector<1, Y> const& _y, Z _z) :
			x(static_cast<T>(_x.x)),
			y(static_cast<T>(_y.x)),
			z(static_cast<T>(_z))
		{
		}
		template<typename X, typename Y, typename Z> constexpr Vector(X _x, Y _y, Vector<1, Z> const& _z) :
			x(static_cast<T>(_x)),
			y(static_cast<T>(_y)),
			z(static_cast<T>(_z.x))
		{
		}
		template<typename X, typename Y, typename Z> constexpr Vector(Vector<1, X> const& _x, Y _y, Vector<1, Z> const& _z) :
			x(static_cast<T>(_x.x)),
			y(static_cast<T>(_y)),
			z(static_cast<T>(_z.x))
		{
		}
		template<typename X, typename Y, typename Z> constexpr Vector(X _x, Vector<1, Y> const& _y, Vector<1, Z> const& _z) :
			x(static_cast<T>(_x)),
			y(static_cast<T>(_y.x)),
			z(static_cast<T>(_z.x))
		{
		}
		template<typename X, typename Y, typename Z> constexpr Vector(Vector<1, X> const& _x, Vector<1, Y> const& _y, Vector<1, Z> const& _z) :
			x(static_cast<T>(_x.x)),
			y(static_cast<T>(_y.x)),
			z(static_cast<T>(_z.x))
		{
		}
		#pragma endregion

		#pragma region ConstructorsVectors
		template<typename A, typename B> constexpr Vector(Vector<2, A> const& _xy, B _z) :
			x(static_cast<T>(_xy.x)),
			y(static_cast<T>(_xy.y)),
			z(static_cast<T>(_z))
		{
		}
		template<typename A, typename B> constexpr Vector(Vector<2, A> const& _xy, Vector<1, B> const& _z) :
			x(static_cast<T>(_xy.x)),
			y(static_cast<T>(_xy.y)),
			z(static_cast<T>(_z.x))
		{
		}
		template<typename A, typename B> constexpr Vector(A _x, Vector<2, B> const& _yz) :
			x(static_cast<T>(_x)),
			y(static_cast<T>(_yz.x)),
			z(static_cast<T>(_yz.y))
		{
		}
		template<typename A, typename B> constexpr Vector(Vector<1, A> const& _x, Vector<2, B> const& _yz) :
			x(static_cast<T>(_x.x)),
			y(static_cast<T>(_yz.x)),
			z(static_cast<T>(_yz.y))
		{
		}
		#pragma endregion

		#pragma region ConstructorsSize
		template<typename U> constexpr explicit Vector(Vector<3, U> const& v) :
			x(static_cast<T>(v.x)),
			y(static_cast<T>(v.y)),
			z(static_cast<T>(v.z))
		{
		}
		template<typename U> constexpr explicit Vector(Vector<4, U> const& v) :
			x(static_cast<T>(v.x)),
			y(static_cast<T>(v.y)),
			z(static_cast<T>(v.z))
		{
		}
		#pragma endregion

		//////////////////////////
		// ASSIGNMENT OPERATORS //
		//////////////////////////

		#pragma region AOperators=
		constexpr Vector<3, T>& operator=(Vector<3, T> const& v) = default;
		template<typename U> constexpr Vector<3, T>& operator=(Vector<3, U> const& v)
		{
			this->x = static_cast<T>(v.x);
			this->y = static_cast<T>(v.y);
			this->z = static_cast<T>(v.z);
			return *this;
		}
		#pragma endregion

		#pragma region AOperators+=
		template<typename U> constexpr Vector<3, T>& operator+=(U s)
		{
			this->x += static_cast<T>(s);
			this->y += static_cast<T>(s);
			this->z += static_cast<T>(s);
			return *this;
		}
		template<typename U> constexpr Vector<3, T>& operator+=(Vector<1, U> const& v)
		{
			this->x += static_cast<T>(v.x);
			this->y += static_cast<T>(v.x);
			this->z += static_cast<T>(v.x);
			return *this;
		}
		template<typename U> constexpr Vector<3, T>& operator+=(Vector<3, U> const& v)
		{
			this->x += static_cast<T>(v.x);
			this->y += static_cast<T>(v.y);
			this->z += static_cast<T>(v.z);
			return *this;
		}
		#pragma endregion

		#pragma region AOperators-=
		template<typename U> constexpr Vector<3, T>& operator-=(U s)
		{
			this->x -= static_cast<T>(s);
			this->y -= static_cast<T>(s);
			this->z -= static_cast<T>(s);
			return *this;
		}
		template<typename U> constexpr Vector<3, T>& operator-=(Vector<1, U> const& v)
		{
			this->x -= static_cast<T>(v.x);
			this->y -= static_cast<T>(v.x);
			this->z -= static_cast<T>(v.x);
			return *this;
		}
		template<typename U> constexpr Vector<3, T>& operator-=(Vector<3, U> const& v)
		{
			this->x -= static_cast<T>(v.x);
			this->y -= static_cast<T>(v.y);
			this->z -= static_cast<T>(v.z);
			return *this;
		}
		#pragma endregion

		#pragma region AOperators*=
		template<typename U> constexpr Vector<3, T>& operator*=(U s)
		{
			this->x *= static_cast<T>(s);
			this->y *= static_cast<T>(s);
			this->z *= static_cast<T>(s);
			return *this;
		}
		template<typename U> constexpr Vector<3, T>& operator*=(Vector<1, U> const& v)
		{
			this->x *= static_cast<T>(v.x);
			this->y *= static_cast<T>(v.x);
			this->z *= static_cast<T>(v.x);
			return *this;
		}
		template<typename U> constexpr Vector<3, T>& operator*=(Vector<3, U> const& v)
		{
			this->x *= static_cast<T>(v.x);
			this->y *= static_cast<T>(v.y);
			this->z *= static_cast<T>(v.z);
			return *this;
		}
		#pragma endregion

		#pragma region AOperators/=
		template<typename U> constexpr Vector<3, T>& operator/=(U s)
		{
			this->x /= static_cast<T>(s);
			this->y /= static_cast<T>(s);
			this->z /= static_cast<T>(s);
			return *this;
		}
		template<typename U> constexpr Vector<3, T>& operator/=(Vector<1, U> const& v)
		{
			this->x /= static_cast<T>(v.x);
			this->y /= static_cast<T>(v.x);
			this->z /= static_cast<T>(v.x);
			return *this;
		}
		template<typename U> constexpr Vector<3, T>& operator/=(Vector<3, U> const& v)
		{
			this->x /= static_cast<T>(v.x);
			this->y /= static_cast<T>(v.y);
			this->z /= static_cast<T>(v.z);
			return *this;
		}
		#pragma endregion

		#pragma region AOperators%=
		template<typename U> constexpr Vector<3, T>& operator%=(U s)
		{
			this->x %= static_cast<T>(s);
			this->y %= static_cast<T>(s);
			this->z %= static_cast<T>(s);
			return *this;
		}
		template<typename U> constexpr Vector<3, T>& operator%=(Vector<1, U> v)
		{
			this->x %= static_cast<T>(v.x);
			this->y %= static_cast<T>(v.x);
			this->z %= static_cast<T>(v.x);
			return *this;
		}
		template<typename U> constexpr Vector<3, T>& operator%=(Vector<3, U> v)
		{
			this->x %= static_cast<T>(v.x);
			this->y %= static_cast<T>(v.y);
			this->z %= static_cast<T>(v.z);
			return *this;
		}
		#pragma endregion

		#pragma region AOperators&=
		template<typename U> constexpr Vector<3, T>& operator&=(U s)
		{
			this->x &= static_cast<T>(s);
			this->y &= static_cast<T>(s);
			this->z &= static_cast<T>(s);
			return *this;
		}
		template<typename U> constexpr Vector<3, T>& operator&=(Vector<1, U> v)
		{
			this->x &= static_cast<T>(v.x);
			this->y &= static_cast<T>(v.x);
			this->z &= static_cast<T>(v.x);
			return *this;
		}
		template<typename U> constexpr Vector<3, T>& operator&=(Vector<3, U> v)
		{
			this->x &= static_cast<T>(v.x);
			this->y &= static_cast<T>(v.y);
			this->z &= static_cast<T>(v.z);
			return *this;
		}
		#pragma endregion

		#pragma region AOperators|=
		template<typename U> constexpr Vector<3, T>& operator|=(U s)
		{
			this->x |= static_cast<T>(s);
			this->y |= static_cast<T>(s);
			this->z |= static_cast<T>(s);
			return *this;
		}
		template<typename U> constexpr Vector<3, T>& operator|=(Vector<1, U> v)
		{
			this->x |= static_cast<T>(v.x);
			this->y |= static_cast<T>(v.x);
			this->z |= static_cast<T>(v.x);
			return *this;
		}
		template<typename U> constexpr Vector<3, T>& operator|=(Vector<3, U> v)
		{
			this->x |= static_cast<T>(v.x);
			this->y |= static_cast<T>(v.y);
			this->z |= static_cast<T>(v.z);
			return *this;
		}
		#pragma endregion

		#pragma region AOperators^=
		template<typename U> constexpr Vector<3, T>& operator^=(U s)
		{
			this->x ^= static_cast<T>(s);
			this->y ^= static_cast<T>(s);
			this->z ^= static_cast<T>(s);
			return *this;
		}
		template<typename U> constexpr Vector<3, T>& operator^=(Vector<1, U> v)
		{
			this->x ^= static_cast<T>(v.x);
			this->y ^= static_cast<T>(v.x);
			this->z ^= static_cast<T>(v.x);
			return *this;
		}
		template<typename U> constexpr Vector<3, T>& operator^=(Vector<3, U> v)
		{
			this->x ^= static_cast<T>(v.x);
			this->y ^= static_cast<T>(v.y);
			this->z ^= static_cast<T>(v.z);
			return *this;
		}
		#pragma endregion

		#pragma region AOperators<<=
		template<typename U> constexpr Vector<3, T>& operator<<=(U s)
		{
			this->x <<= static_cast<T>(s);
			this->y <<= static_cast<T>(s);
			this->z <<= static_cast<T>(s);
			return *this;
		}
		template<typename U> constexpr Vector<3, T>& operator<<=(Vector<1, U> v)
		{
			this->x <<= static_cast<T>(v.x);
			this->y <<= static_cast<T>(v.x);
			this->z <<= static_cast<T>(v.x);
			return *this;
		}
		template<typename U> constexpr Vector<3, T>& operator<<=(Vector<3, U> v)
		{
			this->x <<= static_cast<T>(v.x);
			this->y <<= static_cast<T>(v.y);
			this->z <<= static_cast<T>(v.z);
			return *this;
		}
		#pragma endregion

		#pragma region AOperators>>=
		template<typename U> constexpr Vector<3, T>& operator>>=(U s)
		{
			this->x >>= static_cast<T>(s);
			this->y >>= static_cast<T>(s);
			this->z >>= static_cast<T>(s);
			return *this;
		}
		template<typename U> constexpr Vector<3, T>& operator>>=(Vector<1, U> v)
		{
			this->x >>= static_cast<T>(v.x);
			this->y >>= static_cast<T>(v.x);
			this->z >>= static_cast<T>(v.x);
			return *this;
		}
		template<typename U> constexpr Vector<3, T>& operator>>=(Vector<3, U> v)
		{
			this->x >>= static_cast<T>(v.x);
			this->y >>= static_cast<T>(v.y);
			this->z >>= static_cast<T>(v.z);
			return *this;
		}
		#pragma endregion

		/////////////////////////
		// INCREMENT OPERATORS //
		/////////////////////////

		#pragma region IOperators
		constexpr Vector<3, T>& operator++()
		{
			++this->x;
			++this->y;
			++this->z;
			return *this;
		}
		constexpr Vector<3, T>& operator--()
		{
			--this->x;
			--this->y;
			--this->z;
			return *this;
		}
		constexpr Vector<3, T> operator++(int)
		{
			Vector<3, T> result(*this);
			++(*this);
			return result;
		}
		constexpr Vector<3, T> operator--(int)
		{
			Vector<3, T> result(*this);
			--(*this);
			return result;
		}
		#pragma endregion
	};

	////////////////////
	// CALC OPERATORS //
	////////////////////

	#pragma region COperators+
	template<typename T> constexpr Vector<3, T> operator+(Vector<3, T> const& v)
	{
		return v;
	}
	template<typename T> constexpr Vector<3, T> operator+(Vector<3, T> const& v, T s)
	{
		return Vector<3, T>(v.x + s, v.y + s, v.z + s);
	}
	template<typename T> constexpr Vector<3, T> operator+(Vector<3, T> const& v, Vector<1, T> const& s)
	{
		return Vector<3, T>(v.x + s.x, v.y + s.x, v.z + s.x);
	}
	template<typename T> constexpr Vector<3, T> operator+(T s, Vector<3, T> const& v)
	{
		return Vector<3, T>(s + v.x, s + v.y, s + v.z);
	}
	template<typename T> constexpr Vector<3, T> operator+(Vector<1, T> const& s, Vector<3, T> const& v)
	{
		return Vector<3, T>(s.x + v.x, s.x + v.y, s.x + v.z);
	}
	template<typename T> constexpr Vector<3, T> operator+(Vector<3, T> const& v1, Vector<3, T> const& v2)
	{
		return Vector<3, T>(v1.x + v2.x, v1.y + v2.y, v1.z + v2.z);
	}
	#pragma endregion

	#pragma region COperators-
	template<typename T> constexpr Vector<3, T> operator-(Vector<3, T> const& v)
	{
		return Vector<3, T>(-v.x, -v.y, -v.z);
	}
	template<typename T> constexpr Vector<3, T> operator-(Vector<3, T> const& v, T s)
	{
		return Vector<3, T>(v.x - s, v.y - s, v.z - s);
	}
	template<typename T> constexpr Vector<3, T> operator-(Vector<3, T> const& v, Vector<1, T> const& s)
	{
		return Vector<3, T>(v.x - s.x, v.y - s.x, v.z - s.x);
	}
	template<typename T> constexpr Vector<3, T> operator-(T s, Vector<3, T> const& v)
	{
		return Vector<3, T>(s - v.x, s - v.y, s - v.z);
	}
	template<typename T> constexpr Vector<3, T> operator-(Vector<1, T> const& s, Vector<3, T> const& v)
	{
		return Vector<3, T>(s.x - v.x, s.x - v.y, s.x - v.z);
	}
	template<typename T> constexpr Vector<3, T> operator-(Vector<3, T> const& v1, Vector<3, T> const& v2)
	{
		return Vector<3, T>(v1.x - v2.x, v1.y - v2.y, v1.z - v2.z);
	}
	#pragma endregion

	#pragma region COperators*
	template<typename T> constexpr Vector<3, T> operator*(Vector<3, T> const& v, T s)
	{
		return Vector<3, T>(v.x * s, v.y * s, v.z * s);
	}
	template<typename T> constexpr Vector<3, T> operator*(Vector<3, T> const& v, Vector<1, T> const& s)
	{
		return Vector<3, T>(v.x * s.x, v.y * s.x, v.z * s.x);
	}
	template<typename T> constexpr Vector<3, T> operator*(T s, Vector<3, T> const& v)
	{
		return Vector<3, T>(s * v.x, s * v.y, s * v.z);
	}
	template<typename T> constexpr Vector<3, T> operator*(Vector<1, T> const& s, Vector<3, T> const& v)
	{
		return Vector<3, T>(s.x * v.x, s.x * v.y, s.x * v.z);
	}
	template<typename T> constexpr Vector<3, T> operator*(Vector<3, T> const& v1, Vector<3, T> const& v2)
	{
		return Vector<3, T>(v1.x * v2.x, v1.y * v2.y, v1.z * v2.z);
	}
	#pragma endregion

	#pragma region COperators/
	template<typename T> constexpr Vector<3, T> operator/(Vector<3, T> const& v, T s)
	{
		return Vector<3, T>(v.x / s, v.y / s, v.z / s);
	}
	template<typename T> constexpr Vector<3, T> operator/(Vector<3, T> const& v, Vector<1, T> const& s)
	{
		return Vector<3, T>(v.x / s.x, v.y / s.x, v.z / s.x);
	}
	template<typename T> constexpr Vector<3, T> operator/(T s, Vector<3, T> const& v)
	{
		return Vector<3, T>(s / v.x, s / v.y, s / v.z);
	}
	template<typename T> constexpr Vector<3, T> operator/(Vector<1, T> const& s, Vector<3, T> const& v)
	{
		return Vector<3, T>(s.x / v.x, s.x / v.y, s.x / v.z);
	}
	template<typename T> constexpr Vector<3, T> operator/(Vector<3, T> const& v1, Vector<3, T> const& v2)
	{
		return Vector<3, T>(v1.x / v2.x, v1.y / v2.y, v1.z / v2.z);
	}
	#pragma endregion

	#pragma region COperators%
	template<typename T> constexpr Vector<3, T> operator%(Vector<3, T> const& v, T s)
	{
		return Vector<3, T>(v.x % s, v.y % s, v.z % s);
	}
	template<typename T> constexpr Vector<3, T> operator%(Vector<3, T> const& v, Vector<1, T> const& s)
	{
		return Vector<3, T>(v.x % s.x, v.y % s.x, v.z % s.x);
	}
	template<typename T> constexpr Vector<3, T> operator%(T s, Vector<3, T> const& v)
	{
		return Vector<3, T>(s % v.x, s % v.y, s % v.z);
	}
	template<typename T> constexpr Vector<3, T> operator%(Vector<1, T> const& s, Vector<3, T> const& v)
	{
		return Vector<3, T>(s.x % v.x, s.x % v.y, s.x % v.z);
	}
	template<typename T> constexpr Vector<3, T> operator%(Vector<3, T> const& v1, Vector<3, T> const& v2)
	{
		return Vector<3, T>(v1.x % v2.x, v1.y % v2.y, v1.z % v2.z);
	}
	#pragma endregion

	#pragma region COperators&
	template<typename T> constexpr Vector<3, T> operator&(Vector<3, T> const& v, T s)
	{
		return Vector<3, T>(v.x & s, v.y & s, v.z & s);
	}
	template<typename T> constexpr Vector<3, T> operator&(Vector<3, T> const& v, Vector<1, T> const& s)
	{
		return Vector<3, T>(v.x & s.x, v.y & s.x, v.z & s.x);
	}
	template<typename T> constexpr Vector<3, T> operator&(T s, Vector<3, T> const& v)
	{
		return Vector<3, T>(s & v.x, s & v.y, s & v.z);
	}
	template<typename T> constexpr Vector<3, T> operator&(Vector<1, T> const& s, Vector<3, T> const& v)
	{
		return Vector<3, T>(s.x & v.x, s.x & v.y, s.x & v.z);
	}
	template<typename T> constexpr Vector<3, T> operator&(Vector<3, T> const& v1, Vector<3, T> const& v2)
	{
		return Vector<3, T>(v1.x & v2.x, v1.y & v2.y, v1.z & v2.z);
	}
	#pragma endregion

	#pragma region COperators|
	template<typename T> constexpr Vector<3, T> operator|(Vector<3, T> const& v, T s)
	{
		return Vector<3, T>(v.x | s, v.y | s, v.z | s);
	}
	template<typename T> constexpr Vector<3, T> operator|(Vector<3, T> const& v, Vector<1, T> const& s)
	{
		return Vector<3, T>(v.x | s.x, v.y | s.x, v.z | s.x);
	}
	template<typename T> constexpr Vector<3, T> operator|(T s, Vector<3, T> const& v)
	{
		return Vector<3, T>(s | v.x, s | v.y, s | v.z);
	}
	template<typename T> constexpr Vector<3, T> operator|(Vector<1, T> const& s, Vector<3, T> const& v)
	{
		return Vector<3, T>(s.x | v.x, s.x | v.y, s.x | v.z);
	}
	template<typename T> constexpr Vector<3, T> operator|(Vector<3, T> const& v1, Vector<3, T> const& v2)
	{
		return Vector<3, T>(v1.x | v2.x, v1.y | v2.y, v1.z | v2.z);
	}
	#pragma endregion

	#pragma region COperators^
	template<typename T> constexpr Vector<3, T> operator^(Vector<3, T> const& v, T s)
	{
		return Vector<3, T>(v.x ^ s, v.y ^ s, v.z ^ s);
	}
	template<typename T> constexpr Vector<3, T> operator^(Vector<3, T> const& v, Vector<1, T> const& s)
	{
		return Vector<3, T>(v.x ^ s.x, v.y ^ s.x, v.z ^ s.x);
	}
	template<typename T> constexpr Vector<3, T> operator^(T s, Vector<3, T> const& v)
	{
		return Vector<3, T>(s ^ v.x, s ^ v.y, s ^ v.z);
	}
	template<typename T> constexpr Vector<3, T> operator^(Vector<1, T> const& s, Vector<3, T> const& v)
	{
		return Vector<3, T>(s.x ^ v.x, s.x ^ v.y, s.x ^ v.z);
	}
	template<typename T> constexpr Vector<3, T> operator^(Vector<3, T> const& v1, Vector<3, T> const& v2)
	{
		return Vector<3, T>(v1.x ^ v2.x, v1.y ^ v2.y, v1.z ^ v2.z);
	}
	#pragma endregion

	#pragma region COperators<<
	template<typename T> constexpr Vector<3, T> operator<<(Vector<3, T> const& v, T s)
	{
		return Vector<3, T>(v.x << s, v.y << s, v.z << s);
	}
	template<typename T> constexpr Vector<3, T> operator<<(Vector<3, T> const& v, Vector<1, T> const& s)
	{
		return Vector<3, T>(v.x << s.x, v.y << s.x, v.z << s.x);
	}
	template<typename T> constexpr Vector<3, T> operator<<(T s, Vector<3, T> const& v)
	{
		return Vector<3, T>(s << v.x, s << v.y, s << v.z);
	}
	template<typename T> constexpr Vector<3, T> operator<<(Vector<1, T> const& s, Vector<3, T> const& v)
	{
		return Vector<3, T>(s.x << v.x, s.x << v.y, s.x << v.z);
	}
	template<typename T> constexpr Vector<3, T> operator<<(Vector<3, T> const& v1, Vector<3, T> const& v2)
	{
		return Vector<3, T>(v1.x << v2.x, v1.y << v2.y, v1.z << v2.z);
	}
	#pragma endregion

	#pragma region COperators>>
	template<typename T> constexpr Vector<3, T> operator>>(Vector<3, T> const& v, T s)
	{
		return Vector<3, T>(v.x >> s, v.y >> s, v.z >> s);
	}
	template<typename T> constexpr Vector<3, T> operator>>(Vector<3, T> const& v, Vector<1, T> const& s)
	{
		return Vector<3, T>(v.x >> s.x, v.y >> s.x, v.z >> s.x);
	}
	template<typename T> constexpr Vector<3, T> operator>>(T s, Vector<3, T> const& v)
	{
		return Vector<3, T>(s >> v.x, s >> v.y, s >> v.z);
	}
	template<typename T> constexpr Vector<3, T> operator>>(Vector<1, T> const& s, Vector<3, T> const& v)
	{
		return Vector<3, T>(s.x >> v.x, s.x >> v.y, s.x >> v.z);
	}
	template<typename T> constexpr Vector<3, T> operator>>(Vector<3, T> const& v1, Vector<3, T> const& v2)
	{
		return Vector<3, T>(v1.x >> v2.x, v1.y >> v2.y, v1.z >> v2.z);
	}
	#pragma endregion

	#pragma region COperators~
	template<typename T> constexpr Vector<3, T> operator~(Vector<3, T> const& v)
	{
		return Vector<3, T>(~v.x, ~v.y, ~v.z);
	}
	#pragma endregion

	///////////////////////
	// BOOLEAN OPERATORS //
	///////////////////////

	#pragma region BOperators
	template<typename T> constexpr bool operator==(Vector<3, T> const& v1, Vector<3, T> const& v2)
	{
		return (v1.x == v2.x) && (v1.y == v2.y) && (v1.z == v2.z);
	}
	template<typename T> constexpr bool operator!=(Vector<3, T> const& v1, Vector<3, T> const& v2)
	{
		return (v1.x != v2.x) || (v1.y != v2.y) || (v1.z != v2.z);
	}
	template<typename T> constexpr Vector<3, bool> operator&&(Vector<3, T> const& v1, Vector<3, T> const& v2)
	{
		return Vector<3, bool>(v1.x && v2.x, v1.y && v2.y, v1.z && v2.z);
	}
	template<typename T> constexpr Vector<3, bool> operator||(Vector<3, T> const& v1, Vector<3, T> const& v2)
	{
		return Vector<3, bool>(v1.x || v2.x, v1.y || v2.y, v1.z || v2.z);
	}
	#pragma endregion

	//////////////////////
	// TYPE DEFINITIONS //
	//////////////////////

	typedef Vector< 3, float    >   Vec3;
	typedef Vector< 3, float    >  fVec3;
	typedef Vector< 3, double   >  dVec3;
	typedef Vector< 3, int32_t  >  iVec3;
	typedef Vector< 3, uint32_t > uiVec3;
	typedef Vector< 3, bool     >  bVec3;
}
