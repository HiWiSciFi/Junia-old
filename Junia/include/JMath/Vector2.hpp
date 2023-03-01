#pragma once

#include "Types.hpp"

namespace JMath
{
	template<typename T>
	struct Vector<2, T>
	{
		//////////
		// DATA //
		//////////

		union { T x, r; };
		union { T y, g; };

		////////////
		// ACCESS //
		////////////

		#pragma region AccessFuncs
		static constexpr unsigned char length() { return 2; }

		constexpr T& operator[](unsigned char i)
		{
			switch (i)
			{
			default:
			case 0:
				return x;
			case 1:
				return y;
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
			}
		}
		#pragma endregion

		//////////////////
		// CONSTRUCTORS //
		//////////////////

		#pragma region ConstructorsBase
		constexpr Vector() = default;
		constexpr Vector(Vector const& v) = default;

		constexpr explicit Vector(T s) : x(s), y(s) { }
		constexpr Vector(T _x, T _y) : x(_x), y(_y) { }

		template<typename U> constexpr explicit Vector(Vector<1, U> const& v) :
			x(static_cast<T>(v.x)),
			y(static_cast<T>(v.x))
		{
		}
		#pragma endregion

		#pragma region ConstructorsScalar
		template<typename X, typename Y> constexpr Vector(X _x, Y _y) :
			x(static_cast<T>(_x)),
			y(static_cast<T>(_y))
		{
		}
		template<typename X, typename Y> constexpr Vector(Vector<1, X> const& _x, Y _y) :
			x(static_cast<T>(_x.x)),
			y(static_cast<T>(_y))
		{
		}
		template<typename X, typename Y> constexpr Vector(X _x, Vector<1, Y> const& _y) :
			x(static_cast<T>(_x)),
			y(static_cast<T>(_y.x))
		{
		}
		template<typename X, typename Y> constexpr Vector(Vector<1, X> const& _x, Vector<1, Y> const& _y) :
			x(static_cast<T>(_x.x)),
			y(static_cast<T>(_y.x))
		{
		}
		#pragma endregion

		#pragma region ConstructorsSize
		template<typename U> constexpr explicit Vector(Vector<2, U> const& v) :
			x(static_cast<T>(v.x)),
			y(static_cast<T>(v.y))
		{
		}
		template<typename U> constexpr explicit Vector(Vector<3, U> const& v) :
			x(static_cast<T>(v.x)),
			y(static_cast<T>(v.y))
		{
		}
		template<typename U> constexpr explicit Vector(Vector<4, U> const& v) :
			x(static_cast<T>(v.x)),
			y(static_cast<T>(v.y))
		{
		}
		#pragma endregion

		//////////////////////////
		// ASSIGNMENT OPERATORS //
		//////////////////////////

		#pragma region AOperators=
		constexpr Vector<2, T>& operator=(Vector<2, T> const& v) = default;
		template<typename U> constexpr Vector<2, T>& operator=(Vector<2, U> const& v)
		{
			this->x = static_cast<T>(v.x);
			this->y = static_cast<T>(v.y);
			return *this;
		}
		#pragma endregion

		#pragma region AOperators+=
		template<typename U> constexpr Vector<2, T>& operator+=(U s)
		{
			this->x += static_cast<T>(s);
			this->y += static_cast<T>(s);
			return *this;
		}
		template<typename U> constexpr Vector<2, T>& operator+=(Vector<1, U> const& v)
		{
			this->x += static_cast<T>(v.x);
			this->y += static_cast<T>(v.x);
			return *this;
		}
		template<typename U> constexpr Vector<2, T>& operator+=(Vector<2, U> const& v)
		{
			this->x += static_cast<T>(v.x);
			this->y += static_cast<T>(v.y);
			return *this;
		}
		#pragma endregion

		#pragma region AOperators-=
		template<typename U> constexpr Vector<2, T>& operator-=(U s)
		{
			this->x -= static_cast<T>(s);
			this->y -= static_cast<T>(s);
			return *this;
		}
		template<typename U> constexpr Vector<2, T>& operator-=(Vector<1, U> const& v)
		{
			this->x -= static_cast<T>(v.x);
			this->y -= static_cast<T>(v.x);
			return *this;
		}
		template<typename U> constexpr Vector<2, T>& operator-=(Vector<2, U> const& v)
		{
			this->x -= static_cast<T>(v.x);
			this->y -= static_cast<T>(v.y);
			return *this;
		}
		#pragma endregion

		#pragma region AOperators*=
		template<typename U> constexpr Vector<2, T>& operator*=(U s)
		{
			this->x *= static_cast<T>(s);
			this->y *= static_cast<T>(s);
			return *this;
		}
		template<typename U> constexpr Vector<2, T>& operator*=(Vector<1, U> const& v)
		{
			this->x *= static_cast<T>(v.x);
			this->y *= static_cast<T>(v.x);
			return *this;
		}
		template<typename U> constexpr Vector<2, T>& operator*=(Vector<2, U> const& v)
		{
			this->x *= static_cast<T>(v.x);
			this->y *= static_cast<T>(v.y);
			return *this;
		}
		#pragma endregion

		#pragma region AOperators/=
		template<typename U> constexpr Vector<2, T>& operator/=(U s)
		{
			this->x /= static_cast<T>(s);
			this->y /= static_cast<T>(s);
			return *this;
		}
		template<typename U> constexpr Vector<2, T>& operator/=(Vector<1, U> const& v)
		{
			this->x /= static_cast<T>(v.x);
			this->y /= static_cast<T>(v.x);
			return *this;
		}
		template<typename U> constexpr Vector<2, T>& operator/=(Vector<2, U> const& v)
		{
			this->x /= static_cast<T>(v.x);
			this->y /= static_cast<T>(v.y);
			return *this;
		}
		#pragma endregion

		#pragma region AOperators%=
		template<typename U> constexpr Vector<2, T>& operator%=(U s)
		{
			this->x %= static_cast<T>(s);
			this->y %= static_cast<T>(s);
			return *this;
		}
		template<typename U> constexpr Vector<2, T>& operator%=(Vector<1, U> v)
		{
			this->x %= static_cast<T>(v.x);
			this->y %= static_cast<T>(v.x);
			return *this;
		}
		template<typename U> constexpr Vector<2, T>& operator%=(Vector<2, U> v)
		{
			this->x %= static_cast<T>(v.x);
			this->y %= static_cast<T>(v.y);
			return *this;
		}
		#pragma endregion

		#pragma region AOperators&=
		template<typename U> constexpr Vector<2, T>& operator&=(U s)
		{
			this->x &= static_cast<T>(s);
			this->y &= static_cast<T>(s);
			return *this;
		}
		template<typename U> constexpr Vector<2, T>& operator&=(Vector<1, U> v)
		{
			this->x &= static_cast<T>(v.x);
			this->y &= static_cast<T>(v.x);
			return *this;
		}
		template<typename U> constexpr Vector<2, T>& operator&=(Vector<2, U> v)
		{
			this->x &= static_cast<T>(v.x);
			this->y &= static_cast<T>(v.y);
			return *this;
		}
		#pragma endregion

		#pragma region AOperators|=
		template<typename U> constexpr Vector<2, T>& operator|=(U s)
		{
			this->x |= static_cast<T>(s);
			this->y |= static_cast<T>(s);
			return *this;
		}
		template<typename U> constexpr Vector<2, T>& operator|=(Vector<1, U> v)
		{
			this->x |= static_cast<T>(v.x);
			this->y |= static_cast<T>(v.x);
			return *this;
		}
		template<typename U> constexpr Vector<2, T>& operator|=(Vector<2, U> v)
		{
			this->x |= static_cast<T>(v.x);
			this->y |= static_cast<T>(v.y);
			return *this;
		}
		#pragma endregion

		#pragma region AOperators^=
		template<typename U> constexpr Vector<2, T>& operator^=(U s)
		{
			this->x ^= static_cast<T>(s);
			this->y ^= static_cast<T>(s);
			return *this;
		}
		template<typename U> constexpr Vector<2, T>& operator^=(Vector<1, U> v)
		{
			this->x ^= static_cast<T>(v.x);
			this->y ^= static_cast<T>(v.x);
			return *this;
		}
		template<typename U> constexpr Vector<2, T>& operator^=(Vector<2, U> v)
		{
			this->x ^= static_cast<T>(v.x);
			this->y ^= static_cast<T>(v.y);
			return *this;
		}
		#pragma endregion

		#pragma region AOperators<<=
		template<typename U> constexpr Vector<2, T>& operator<<=(U s)
		{
			this->x <<= static_cast<T>(s);
			this->y <<= static_cast<T>(s);
			return *this;
		}
		template<typename U> constexpr Vector<2, T>& operator<<=(Vector<1, U> v)
		{
			this->x <<= static_cast<T>(v.x);
			this->y <<= static_cast<T>(v.x);
			return *this;
		}
		template<typename U> constexpr Vector<2, T>& operator<<=(Vector<2, U> v)
		{
			this->x <<= static_cast<T>(v.x);
			this->y <<= static_cast<T>(v.y);
			return *this;
		}
		#pragma endregion

		#pragma region AOperators>>=
		template<typename U> constexpr Vector<2, T>& operator>>=(U s)
		{
			this->x >>= static_cast<T>(s);
			this->y >>= static_cast<T>(s);
			return *this;
		}
		template<typename U> constexpr Vector<2, T>& operator>>=(Vector<1, U> v)
		{
			this->x >>= static_cast<T>(v.x);
			this->y >>= static_cast<T>(v.x);
			return *this;
		}
		template<typename U> constexpr Vector<2, T>& operator>>=(Vector<2, U> v)
		{
			this->x >>= static_cast<T>(v.x);
			this->y >>= static_cast<T>(v.y);
			return *this;
		}
		#pragma endregion

		/////////////////////////
		// INCREMENT OPERATORS //
		/////////////////////////

		#pragma region IOperators
		constexpr Vector<2, T>& operator++()
		{
			++this->x;
			++this->y;
			return *this;
		}
		constexpr Vector<2, T>& operator--()
		{
			--this->x;
			--this->y;
			return *this;
		}
		constexpr Vector<2, T> operator++(int)
		{
			Vector<2, T> result(*this);
			++(*this);
			return result;
		}
		constexpr Vector<2, T> operator--(int)
		{
			Vector<2, T> result(*this);
			--(*this);
			return result;
		}
		#pragma endregion
	};

	////////////////////
	// CALC OPERATORS //
	////////////////////

	#pragma region COperators+
	template<typename T> constexpr Vector<2, T> operator+(Vector<2, T> const& v)
	{
		return v;
	}
	template<typename T> constexpr Vector<2, T> operator+(Vector<2, T> const& v, T s)
	{
		return Vector<2, T>(v.x + s, v.y + s);
	}
	template<typename T> constexpr Vector<2, T> operator+(Vector<2, T> const& v, Vector<1, T> const& s)
	{
		return Vector<2, T>(v.x + s.x, v.y + s.x);
	}
	template<typename T> constexpr Vector<2, T> operator+(T s, Vector<2, T> const& v)
	{
		return Vector<2, T>(s + v.x, s + v.y);
	}
	template<typename T> constexpr Vector<2, T> operator+(Vector<1, T> const& s, Vector<2, T> const& v)
	{
		return Vector<2, T>(s.x + v.x, s.x + v.y);
	}
	template<typename T> constexpr Vector<2, T> operator+(Vector<2, T> const& v1, Vector<2, T> const& v2)
	{
		return Vector<2, T>(v1.x + v2.x, v1.y + v2.y);
	}
	#pragma endregion

	#pragma region COperators-
	template<typename T> constexpr Vector<2, T> operator-(Vector<2, T> const& v)
	{
		return Vector<2, T>(-v.x, -v.y);
	}
	template<typename T> constexpr Vector<2, T> operator-(Vector<2, T> const& v, T s)
	{
		return Vector<2, T>(v.x - s, v.y - s);
	}
	template<typename T> constexpr Vector<2, T> operator-(Vector<2, T> const& v, Vector<1, T> const& s)
	{
		return Vector<2, T>(v.x - s.x, v.y - s.x);
	}
	template<typename T> constexpr Vector<2, T> operator-(T s, Vector<2, T> const& v)
	{
		return Vector<2, T>(s - v.x, s - v.y);
	}
	template<typename T> constexpr Vector<2, T> operator-(Vector<1, T> const& s, Vector<2, T> const& v)
	{
		return Vector<2, T>(s.x - v.x, s.x - v.y);
	}
	template<typename T> constexpr Vector<2, T> operator-(Vector<2, T> const& v1, Vector<2, T> const& v2)
	{
		return Vector<2, T>(v1.x - v2.x, v1.y - v2.y);
	}
	#pragma endregion

	#pragma region COperators*
	template<typename T> constexpr Vector<2, T> operator*(Vector<2, T> const& v, T s)
	{
		return Vector<2, T>(v.x * s, v.y * s);
	}
	template<typename T> constexpr Vector<2, T> operator*(Vector<2, T> const& v, Vector<1, T> const& s)
	{
		return Vector<2, T>(v.x * s.x, v.y * s.x);
	}
	template<typename T> constexpr Vector<2, T> operator*(T s, Vector<2, T> const& v)
	{
		return Vector<2, T>(s * v.x, s * v.y);
	}
	template<typename T> constexpr Vector<2, T> operator*(Vector<1, T> const& s, Vector<2, T> const& v)
	{
		return Vector<2, T>(s.x * v.x, s.x * v.y);
	}
	template<typename T> constexpr Vector<2, T> operator*(Vector<2, T> const& v1, Vector<2, T> const& v2)
	{
		return Vector<2, T>(v1.x * v2.x, v1.y * v2.y);
	}
	#pragma endregion

	#pragma region COperators/
	template<typename T> constexpr Vector<2, T> operator/(Vector<2, T> const& v, T s)
	{
		return Vector<2, T>(v.x / s, v.y / s);
	}
	template<typename T> constexpr Vector<2, T> operator/(Vector<2, T> const& v, Vector<1, T> const& s)
	{
		return Vector<2, T>(v.x / s.x, v.y / s.x);
	}
	template<typename T> constexpr Vector<2, T> operator/(T s, Vector<2, T> const& v)
	{
		return Vector<2, T>(s / v.x, s / v.y);
	}
	template<typename T> constexpr Vector<2, T> operator/(Vector<1, T> const& s, Vector<2, T> const& v)
	{
		return Vector<2, T>(s.x / v.x, s.x / v.y);
	}
	template<typename T> constexpr Vector<2, T> operator/(Vector<2, T> const& v1, Vector<2, T> const& v2)
	{
		return Vector<2, T>(v1.x / v2.x, v1.y / v2.y);
	}
	#pragma endregion

	#pragma region COperators%
	template<typename T> constexpr Vector<2, T> operator%(Vector<2, T> const& v, T s)
	{
		return Vector<2, T>(v.x % s, v.y % s);
	}
	template<typename T> constexpr Vector<2, T> operator%(Vector<2, T> const& v, Vector<1, T> const& s)
	{
		return Vector<2, T>(v.x % s.x, v.y % s.x);
	}
	template<typename T> constexpr Vector<2, T> operator%(T s, Vector<2, T> const& v)
	{
		return Vector<2, T>(s % v.x, s % v.y);
	}
	template<typename T> constexpr Vector<2, T> operator%(Vector<1, T> const& s, Vector<2, T> const& v)
	{
		return Vector<2, T>(s.x % v.x, s.x % v.y);
	}
	template<typename T> constexpr Vector<2, T> operator%(Vector<2, T> const& v1, Vector<2, T> const& v2)
	{
		return Vector<2, T>(v1.x % v2.x, v1.y % v2.y);
	}
	#pragma endregion

	#pragma region COperators&
	template<typename T> constexpr Vector<2, T> operator&(Vector<2, T> const& v, T s)
	{
		return Vector<2, T>(v.x & s, v.y & s);
	}
	template<typename T> constexpr Vector<2, T> operator&(Vector<2, T> const& v, Vector<1, T> const& s)
	{
		return Vector<2, T>(v.x & s.x, v.y & s.x);
	}
	template<typename T> constexpr Vector<2, T> operator&(T s, Vector<2, T> const& v)
	{
		return Vector<2, T>(s & v.x, s & v.y);
	}
	template<typename T> constexpr Vector<2, T> operator&(Vector<1, T> const& s, Vector<2, T> const& v)
	{
		return Vector<2, T>(s.x & v.x, s.x & v.y);
	}
	template<typename T> constexpr Vector<2, T> operator&(Vector<2, T> const& v1, Vector<2, T> const& v2)
	{
		return Vector<2, T>(v1.x & v2.x, v1.y & v2.y);
	}
	#pragma endregion

	#pragma region COperators|
	template<typename T> constexpr Vector<2, T> operator|(Vector<2, T> const& v, T s)
	{
		return Vector<2, T>(v.x | s, v.y | s);
	}
	template<typename T> constexpr Vector<2, T> operator|(Vector<2, T> const& v, Vector<1, T> const& s)
	{
		return Vector<2, T>(v.x | s.x, v.y | s.x);
	}
	template<typename T> constexpr Vector<2, T> operator|(T s, Vector<2, T> const& v)
	{
		return Vector<2, T>(s | v.x, s | v.y);
	}
	template<typename T> constexpr Vector<2, T> operator|(Vector<1, T> const& s, Vector<2, T> const& v)
	{
		return Vector<2, T>(s.x | v.x, s.x | v.y);
	}
	template<typename T> constexpr Vector<2, T> operator|(Vector<2, T> const& v1, Vector<2, T> const& v2)
	{
		return Vector<2, T>(v1.x | v2.x, v1.y | v2.y);
	}
	#pragma endregion

	#pragma region COperators^
	template<typename T> constexpr Vector<2, T> operator^(Vector<2, T> const& v, T s)
	{
		return Vector<2, T>(v.x ^ s, v.y ^ s);
	}
	template<typename T> constexpr Vector<2, T> operator^(Vector<2, T> const& v, Vector<1, T> const& s)
	{
		return Vector<2, T>(v.x ^ s.x, v.y ^ s.x);
	}
	template<typename T> constexpr Vector<2, T> operator^(T s, Vector<2, T> const& v)
	{
		return Vector<2, T>(s ^ v.x, s ^ v.y);
	}
	template<typename T> constexpr Vector<2, T> operator^(Vector<1, T> const& s, Vector<2, T> const& v)
	{
		return Vector<2, T>(s.x ^ v.x, s.x ^ v.y);
	}
	template<typename T> constexpr Vector<2, T> operator^(Vector<2, T> const& v1, Vector<2, T> const& v2)
	{
		return Vector<2, T>(v1.x ^ v2.x, v1.y ^ v2.y);
	}
	#pragma endregion

	#pragma region COperators<<
	template<typename T> constexpr Vector<2, T> operator<<(Vector<2, T> const& v, T s)
	{
		return Vector<2, T>(v.x << s, v.y << s);
	}
	template<typename T> constexpr Vector<2, T> operator<<(Vector<2, T> const& v, Vector<1, T> const& s)
	{
		return Vector<2, T>(v.x << s.x, v.y << s.x);
	}
	template<typename T> constexpr Vector<2, T> operator<<(T s, Vector<2, T> const& v)
	{
		return Vector<2, T>(s << v.x, s << v.y);
	}
	template<typename T> constexpr Vector<2, T> operator<<(Vector<1, T> const& s, Vector<2, T> const& v)
	{
		return Vector<2, T>(s.x << v.x, s.x << v.y);
	}
	template<typename T> constexpr Vector<2, T> operator<<(Vector<2, T> const& v1, Vector<2, T> const& v2)
	{
		return Vector<2, T>(v1.x << v2.x, v1.y << v2.y);
	}
	#pragma endregion

	#pragma region COperators>>
	template<typename T> constexpr Vector<2, T> operator>>(Vector<2, T> const& v, T s)
	{
		return Vector<2, T>(v.x >> s, v.y >> s);
	}
	template<typename T> constexpr Vector<2, T> operator>>(Vector<2, T> const& v, Vector<1, T> const& s)
	{
		return Vector<2, T>(v.x >> s.x, v.y >> s.x);
	}
	template<typename T> constexpr Vector<2, T> operator>>(T s, Vector<2, T> const& v)
	{
		return Vector<2, T>(s >> v.x, s >> v.y);
	}
	template<typename T> constexpr Vector<2, T> operator>>(Vector<1, T> const& s, Vector<2, T> const& v)
	{
		return Vector<2, T>(s.x >> v.x, s.x >> v.y);
	}
	template<typename T> constexpr Vector<2, T> operator>>(Vector<2, T> const& v1, Vector<2, T> const& v2)
	{
		return Vector<2, T>(v1.x >> v2.x, v1.y >> v2.y);
	}
	#pragma endregion

	#pragma region COperators~
	template<typename T> constexpr Vector<2, T> operator~(Vector<2, T> const& v)
	{
		return Vector<2, T>(~v.x, ~v.y);
	}
	#pragma endregion

	///////////////////////
	// BOOLEAN OPERATORS //
	///////////////////////

	#pragma region BOperators
	template<typename T> constexpr bool operator==(Vector<2, T> const& v1, Vector<2, T> const& v2)
	{
		return (v1.x == v2.x) && (v1.y == v2.y);
	}
	template<typename T> constexpr bool operator!=(Vector<2, T> const& v1, Vector<2, T> const& v2)
	{
		return (v1.x != v2.x) || (v1.y != v2.y);
	}
	template<typename T> constexpr Vector<2, bool> operator&&(Vector<2, T> const& v1, Vector<2, T> const& v2)
	{
		return Vector<2, bool>(v1.x && v2.x, v1.y && v2.y);
	}
	template<typename T> constexpr Vector<2, bool> operator||(Vector<2, T> const& v1, Vector<2, T> const& v2)
	{
		return Vector<2, bool>(v1.x || v2.x, v1.y || v2.y);
	}
	#pragma endregion

	//////////////////////
	// TYPE DEFINITIONS //
	//////////////////////

	typedef Vector< 2, float        >   Vec2;
	typedef Vector< 2, float        >  fVec2;
	typedef Vector< 2, double       >  dVec2;
	typedef Vector< 2, int          >  iVec2;
	typedef Vector< 2, unsigned int > uiVec2;
	typedef Vector< 2, bool         >  bVec2;
}
