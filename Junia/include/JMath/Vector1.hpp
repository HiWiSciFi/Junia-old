#pragma once

#include "Types.hpp"

namespace JMath
{
	template<typename T>
	struct Vector<1, T>
	{
		//////////
		// DATA //
		//////////

		union { T x, r; };

		////////////
		// ACCESS //
		////////////

		#pragma region AccessFuncs
		static constexpr unsigned char length() { return 1; }

		constexpr T& operator[](unsigned char i)
		{
			switch (i)
			{
			default:
			case 0:
				return x;
			}
		}

		constexpr T const& operator[](unsigned char i) const
		{
			switch (i)
			{
			default:
			case 0:
				return x;
			}
		}
		#pragma endregion

		//////////////////
		// CONSTRUCTORS //
		//////////////////

		#pragma region ConstructorsBase
		constexpr Vector() = default;
		constexpr Vector(Vector const& v) = default;

		constexpr explicit Vector(T s) : x(s) { }
		#pragma endregion

		#pragma region ConstructorsSize
		template<typename U> constexpr explicit Vector(Vector<1, U> const& v) :
			x(static_cast<T>(v.x))
		{
		}
		template<typename U> constexpr explicit Vector(Vector<2, U> const& v) :
			x(static_cast<T>(v.x))
		{
		}
		template<typename U> constexpr explicit Vector(Vector<3, U> const& v) :
			x(static_cast<T>(v.x))
		{
		}
		template<typename U> constexpr explicit Vector(Vector<4, U> const& v) :
			x(static_cast<T>(v.x))
		{
		}
		#pragma endregion

		//////////////////////////
		// ASSIGNMENT OPERATORS //
		//////////////////////////

		#pragma region AOperators=
		constexpr Vector<1, T>& operator=(Vector<1, T> const& v) = default;
		template<typename U> constexpr Vector<1, T>& operator=(Vector<1, U> const& v)
		{
			this->x = static_cast<T>(v.x);
			return *this;
		}
		#pragma endregion

		#pragma region AOperators+=
		template<typename U> constexpr Vector<1, T>& operator+=(U s)
		{
			this->x += static_cast<T>(s);
			return *this;
		}
		template<typename U> constexpr Vector<1, T>& operator+=(Vector<1, U> const& v)
		{
			this->x += static_cast<T>(v.x);
			return *this;
		}
		#pragma endregion

		#pragma region AOperators-=
		template<typename U> constexpr Vector<1, T>& operator-=(U s)
		{
			this->x -= static_cast<T>(s);
			return *this;
		}
		template<typename U> constexpr Vector<1, T>& operator-=(Vector<1, U> const& v)
		{
			this->x -= static_cast<T>(v.x);
			return *this;
		}
		#pragma endregion

		#pragma region AOperators*=
		template<typename U> constexpr Vector<1, T>& operator*=(U s)
		{
			this->x *= static_cast<T>(s);
			return *this;
		}
		template<typename U> constexpr Vector<1, T>& operator*=(Vector<1, U> const& v)
		{
			this->x *= static_cast<T>(v.x);
			return *this;
		}
		#pragma endregion

		#pragma region AOperators/=
		template<typename U> constexpr Vector<1, T>& operator/=(U s)
		{
			this->x /= static_cast<T>(s);
			return *this;
		}
		template<typename U> constexpr Vector<1, T>& operator/=(Vector<1, U> const& v)
		{
			this->x /= static_cast<T>(v.x);
			return *this;
		}
		#pragma endregion

		#pragma region AOperators%=
		template<typename U> constexpr Vector<1, T>& operator%=(U s)
		{
			this->x %= static_cast<T>(s);
			return *this;
		}
		template<typename U> constexpr Vector<1, T>& operator%=(Vector<1, U> v)
		{
			this->x %= static_cast<T>(v.x);
			return *this;
		}
		#pragma endregion

		#pragma region AOperators&=
		template<typename U> constexpr Vector<1, T>& operator&=(U s)
		{
			this->x &= static_cast<T>(s);
			return *this;
		}
		template<typename U> constexpr Vector<1, T>& operator&=(Vector<1, U> v)
		{
			this->x &= static_cast<T>(v.x);
			return *this;
		}
		#pragma endregion

		#pragma region AOperators|=
		template<typename U> constexpr Vector<1, T>& operator|=(U s)
		{
			this->x |= static_cast<T>(s);
			return *this;
		}
		template<typename U> constexpr Vector<1, T>& operator|=(Vector<1, U> v)
		{
			this->x |= static_cast<T>(v.x);
			return *this;
		}
		#pragma endregion

		#pragma region AOperators^=
		template<typename U> constexpr Vector<1, T>& operator^=(U s)
		{
			this->x ^= static_cast<T>(s);
			return *this;
		}
		template<typename U> constexpr Vector<1, T>& operator^=(Vector<1, U> v)
		{
			this->x ^= static_cast<T>(v.x);
			return *this;
		}
		#pragma endregion

		#pragma region AOperators<<=
		template<typename U> constexpr Vector<1, T>& operator<<=(U s)
		{
			this->x <<= static_cast<T>(s);
			return *this;
		}
		template<typename U> constexpr Vector<1, T>& operator<<=(Vector<1, U> v)
		{
			this->x <<= static_cast<T>(v.x);
			return *this;
		}
		#pragma endregion

		#pragma region AOperators>>=
		template<typename U> constexpr Vector<1, T>& operator>>=(U s)
		{
			this->x >>= static_cast<T>(s);
			return *this;
		}
		template<typename U> constexpr Vector<1, T>& operator>>=(Vector<1, U> v)
		{
			this->x >>= static_cast<T>(v.x);
			return *this;
		}
		#pragma endregion

		/////////////////////////
		// INCREMENT OPERATORS //
		/////////////////////////

		#pragma region IOperators
		constexpr Vector<1, T>& operator++()
		{
			++this->x;
			return *this;
		}
		constexpr Vector<1, T>& operator--()
		{
			--this->x;
			return *this;
		}
		constexpr Vector<1, T> operator++(int)
		{
			Vector<1, T> result(*this);
			++(*this);
			return result;
		}
		constexpr Vector<1, T> operator--(int)
		{
			Vector<1, T> result(*this);
			--(*this);
			return result;
		}
		#pragma endregion
	};

	////////////////////
	// CALC OPERATORS //
	////////////////////

	#pragma region COperators+
	template<typename T> constexpr Vector<1, T> operator+(Vector<1, T> const& v)
	{
		return v;
	}
	template<typename T> constexpr Vector<1, T> operator+(Vector<1, T> const& v, T s)
	{
		return Vector<1, T>(v.x + s);
	}
	template<typename T> constexpr Vector<1, T> operator+(T s, Vector<1, T> const& v)
	{
		return Vector<1, T>(s + v.x);
	}
	template<typename T> constexpr Vector<1, T> operator+(Vector<1, T> const& v1, Vector<1, T> const& v2)
	{
		return Vector<1, T>(v1.x + v2.x);
	}
	#pragma endregion

	#pragma region COperators-
	template<typename T> constexpr Vector<1, T> operator-(Vector<1, T> const& v)
	{
		return Vector<1, T>(-v.x);
	}
	template<typename T> constexpr Vector<1, T> operator-(Vector<1, T> const& v, T s)
	{
		return Vector<1, T>(v.x - s);
	}
	template<typename T> constexpr Vector<1, T> operator-(T s, Vector<1, T> const& v)
	{
		return Vector<1, T>(s - v.x);
	}
	template<typename T> constexpr Vector<1, T> operator-(Vector<1, T> const& v1, Vector<1, T> const& v2)
	{
		return Vector<1, T>(v1.x - v2.x);
	}
	#pragma endregion

	#pragma region COperators*
	template<typename T> constexpr Vector<1, T> operator*(Vector<1, T> const& v, T s)
	{
		return Vector<1, T>(v.x * s);
	}
	template<typename T> constexpr Vector<1, T> operator*(T s, Vector<1, T> const& v)
	{
		return Vector<1, T>(s * v.x);
	}
	template<typename T> constexpr Vector<1, T> operator*(Vector<1, T> const& v1, Vector<1, T> const& v2)
	{
		return Vector<1, T>(v1.x * v2.x);
	}
	#pragma endregion

	#pragma region COperators/
	template<typename T> constexpr Vector<1, T> operator/(Vector<1, T> const& v, T s)
	{
		return Vector<1, T>(v.x / s);
	}
	template<typename T> constexpr Vector<1, T> operator/(T s, Vector<1, T> const& v)
	{
		return Vector<1, T>(s / v.x);
	}
	template<typename T> constexpr Vector<1, T> operator/(Vector<1, T> const& v1, Vector<1, T> const& v2)
	{
		return Vector<1, T>(v1.x / v2.x);
	}
	#pragma endregion

	#pragma region COperators%
	template<typename T> constexpr Vector<1, T> operator%(Vector<1, T> const& v, T s)
	{
		return Vector<1, T>(v.x % s);
	}
	template<typename T> constexpr Vector<1, T> operator%(T s, Vector<1, T> const& v)
	{
		return Vector<1, T>(s % v.x);
	}
	template<typename T> constexpr Vector<1, T> operator%(Vector<1, T> const& v1, Vector<1, T> const& v2)
	{
		return Vector<1, T>(v1.x % v2.x);
	}
	#pragma endregion

	#pragma region COperators&
	template<typename T> constexpr Vector<1, T> operator&(Vector<1, T> const& v, T s)
	{
		return Vector<1, T>(v.x & s);
	}
	template<typename T> constexpr Vector<1, T> operator&(T s, Vector<1, T> const& v)
	{
		return Vector<1, T>(s & v.x);
	}
	template<typename T> constexpr Vector<1, T> operator&(Vector<1, T> const& v1, Vector<1, T> const& v2)
	{
		return Vector<1, T>(v1.x & v2.x);
	}
	#pragma endregion

	#pragma region COperators|
	template<typename T> constexpr Vector<1, T> operator|(Vector<1, T> const& v, T s)
	{
		return Vector<1, T>(v.x | s);
	}
	template<typename T> constexpr Vector<1, T> operator|(T s, Vector<1, T> const& v)
	{
		return Vector<1, T>(s | v.x);
	}
	template<typename T> constexpr Vector<1, T> operator|(Vector<1, T> const& v1, Vector<1, T> const& v2)
	{
		return Vector<1, T>(v1.x | v2.x);
	}
	#pragma endregion

	#pragma region COperators^
	template<typename T> constexpr Vector<1, T> operator^(Vector<1, T> const& v, T s)
	{
		return Vector<1, T>(v.x ^ s);
	}
	template<typename T> constexpr Vector<1, T> operator^(T s, Vector<1, T> const& v)
	{
		return Vector<1, T>(s ^ v.x);
	}
	template<typename T> constexpr Vector<1, T> operator^(Vector<1, T> const& v1, Vector<1, T> const& v2)
	{
		return Vector<1, T>(v1.x ^ v2.x);
	}
	#pragma endregion

	#pragma region COperators<<
	template<typename T> constexpr Vector<1, T> operator<<(Vector<1, T> const& v, T s)
	{
		return Vector<1, T>(v.x << s);
	}
	template<typename T> constexpr Vector<1, T> operator<<(T s, Vector<1, T> const& v)
	{
		return Vector<1, T>(s << v.x);
	}
	template<typename T> constexpr Vector<1, T> operator<<(Vector<1, T> const& v1, Vector<1, T> const& v2)
	{
		return Vector<1, T>(v1.x << v2.x);
	}
	#pragma endregion

	#pragma region COperators>>
	template<typename T> constexpr Vector<1, T> operator>>(Vector<1, T> const& v, T s)
	{
		return Vector<1, T>(v.x >> s);
	}
	template<typename T> constexpr Vector<1, T> operator>>(T s, Vector<1, T> const& v)
	{
		return Vector<1, T>(s >> v.x);
	}
	template<typename T> constexpr Vector<1, T> operator>>(Vector<1, T> const& v1, Vector<1, T> const& v2)
	{
		return Vector<1, T>(v1.x >> v2.x);
	}
	#pragma endregion

	#pragma region COperators~
	template<typename T> constexpr Vector<1, T> operator~(Vector<1, T> const& v)
	{
		return Vector<1, T>(~v.x);
	}
	#pragma endregion

	///////////////////////
	// BOOLEAN OPERATORS //
	///////////////////////

	#pragma region BOperators
	template<typename T> constexpr bool operator==(Vector<1, T> const& v1, Vector<1, T> const& v2)
	{
		return v1.x == v2.x;
	}
	template<typename T> constexpr bool operator!=(Vector<1, T> const& v1, Vector<1, T> const& v2)
	{
		return v1.x != v2.x;
	}
	template<typename T> constexpr Vector<1, bool> operator&&(Vector<1, T> const& v1, Vector<1, T> const& v2)
	{
		return Vector<1, bool>(v1.x && v2.x);
	}
	template<typename T> constexpr Vector<1, bool> operator||(Vector<1, T> const& v1, Vector<1, T> const& v2)
	{
		return Vector<1, bool>(v1.x || v2.x);
	}
	#pragma endregion

	//////////////////////
	// TYPE DEFINITIONS //
	//////////////////////

	typedef Vector< 1, float        >     Vec1;
	typedef Vector< 1, float        >    fVec1;
	typedef Vector< 1, double       >    dVec1;
	typedef Vector< 1, int          >    iVec1;
	typedef Vector< 1, unsigned int >   uiVec1;
	typedef Vector< 1, bool         >    bVec1;

	typedef Vector< 1, float        >   Scalar;
	typedef Vector< 1, float        >  fScalar;
	typedef Vector< 1, double       >  dScalar;
	typedef Vector< 1, int          >  iScalar;
	typedef Vector< 1, unsigned int > uiScalar;
	typedef Vector< 1, bool         >  bScalar;
}
