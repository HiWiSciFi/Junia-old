#pragma once

#include "Types.hpp"
#include "Mathf.hpp"

namespace JMath
{
	template<typename T>
	struct Matrix<2, 3, T>
	{
		typedef Vector<2, T> row_t;
		typedef Vector<3, T> col_t;

	private:

		//////////
		// DATA //
		//////////

		col_t value[2];
		static constexpr unsigned char length() { return 2; }

	public:

		////////////
		// ACCESS //
		////////////

		#pragma region AccessFuncs
		col_t& operator[](unsigned char i)
		{
			return this->value[i];
		}
		constexpr col_t const& operator[](unsigned char i) const
		{
			return this->value[i];
		}
		#pragma endregion

		//////////////////
		// CONSTRUCTORS //
		//////////////////

		#pragma region ConstructorsBase
		constexpr Matrix() = default;

		constexpr Matrix(Matrix<2, 3, T> const& m) :
			value{
			col_t(m[0]),
			col_t(m[1]) }
		{
		}

		explicit constexpr Matrix(T s) :
			value{
			col_t(s, 0, 0),
			col_t(0, s, 0) }
		{
		}

		constexpr Matrix(
			T const& x1, T const& y1, T const& z1,
			T const& x2, T const& y2, T const& z2) :
			value{
				col_t(x1, y1, z1),
				col_t(x2, y2, z2) }
		{
		}

		constexpr Matrix(
			col_t const& v1,
			col_t const& v2) :
			value{
				col_t(v1),
				col_t(v2) }
		{
		}
		#pragma endregion

		#pragma region ConstructorsVectors
		template<
			typename X1, typename Y1, typename Z1,
			typename X2, typename Y2, typename Z2>
		constexpr Matrix(
			X1 const& x1, Y1 const& y1, Z1 const& z1,
			X2 const& x2, Y2 const& y2, Z2 const& z2) :
			value{
				col_t(static_cast<T>(x1), static_cast<T>(y1), static_cast<T>(z1)),
				col_t(static_cast<T>(x2), static_cast<T>(y2), static_cast<T>(z2)) }
		{
		}

		template<typename A, typename B>
		constexpr Matrix(
			Vector<3, A> const& v1,
			Vector<3, B> const& v2) :
			value{ col_t(v1), col_t(v2) }
		{
		}
		#pragma endregion

		#pragma region ConstructorsSize
		template<typename U> explicit constexpr Matrix(Matrix<2, 3, U> const& m) :
			value{ col_t(m[0]), col_t(m[1]) }
		{
		}

		explicit constexpr Matrix(Matrix<2, 2, T> const& m) : value{ col_t(m[0], 0), col_t(m[1], 0) } { }
		explicit constexpr Matrix(Matrix<3, 3, T> const& m) : value{ col_t(m[0]), col_t(m[1]) } { }
		explicit constexpr Matrix(Matrix<4, 4, T> const& m) : value{ col_t(m[0]), col_t(m[1]) } { }
		explicit constexpr Matrix(Matrix<2, 4, T> const& m) : value{ col_t(m[0]), col_t(m[1]) } { }
		explicit constexpr Matrix(Matrix<3, 2, T> const& m) : value{ col_t(m[0], 0), col_t(m[1], 0) } { }
		explicit constexpr Matrix(Matrix<3, 4, T> const& m) : value{ col_t(m[0]), col_t(m[1]) } { }
		explicit constexpr Matrix(Matrix<4, 2, T> const& m) : value{ col_t(m[0], 0), col_t(m[1], 0) } { }
		explicit constexpr Matrix(Matrix<4, 3, T> const& m) : value{ col_t(m[0]), col_t(m[1]) } { }
		#pragma endregion

		//////////////////////////
		// ASSIGNMENT OPERATORS //
		//////////////////////////

		#pragma region AOperators=
		template<typename U> Matrix<2, 3, T>& operator=(Matrix<2, 3, U> const& m)
		{
			this->value[0] = m[0];
			this->value[1] = m[1];
			return *this;
		}
		#pragma endregion

		#pragma region AOperators+=
		template<typename U> Matrix<2, 3, T>& operator+=(U s)
		{
			this->value[0] += s;
			this->value[1] += s;
			return *this;
		}
		template<typename U> Matrix<2, 3, T>& operator+=(Matrix<2, 3, U> const& m)
		{
			this->value[0] += m[0];
			this->value[1] += m[1];
			return *this;
		}
		#pragma endregion

		#pragma region AOperators-=
		template<typename U> Matrix<2, 3, T>& operator-=(U s)
		{
			this->value[0] -= s;
			this->value[1] -= s;
			return *this;
		}
		template<typename U> Matrix<2, 3, T>& operator-=(Matrix<2, 3, U> const& m)
		{
			this->value[0] -= m[0];
			this->value[1] -= m[1];
			return *this;
		}
		#pragma endregion

		#pragma region AOperators*=
		template<typename U> Matrix<2, 3, T>& operator*=(U s)
		{
			this->value[0] *= s;
			this->value[1] *= s;
			return *this;
		}
		#pragma endregion

		#pragma region AOperators/=
		template<typename U> Matrix<2, 3, T>& operator/=(U s)
		{
			this->value[0] /= s;
			this->value[1] /= s;
			return *this;
		}
		#pragma endregion

		/////////////////////////
		// INCREMENT OPERATORS //
		/////////////////////////

		#pragma region IOperators
		Matrix<2, 3, T>& operator++()
		{
			++this->value[0];
			++this->value[1];
			return *this;
		}
		Matrix<2, 3, T>& operator--()
		{
			--this->value[0];
			--this->value[1];
			return *this;
		}
		Matrix<2, 3, T> operator++(int)
		{
			Matrix<2, 3, T> r(*this);
			++* this;
			return r;
		}
		Matrix<2, 3, T> operator--(int)
		{
			Matrix<2, 3, T> r(*this);
			--* this;
			return r;
		}
		#pragma endregion
	};

	////////////////////
	// CALC OPERATORS //
	////////////////////

	#pragma region COperators+
	template<typename T> Matrix<2, 3, T> operator+(Matrix<2, 3, T> const& m)
	{
		return m;
	}
	template<typename T> Matrix<2, 3, T> operator+(Matrix<2, 3, T> const& m, T s)
	{
		return Matrix<2, 3, T>(m[0] + s, m[1] + s);
	}
	template<typename T> Matrix<2, 3, T> operator+(T s, Matrix<2, 3, T> const& m)
	{
		return Matrix<2, 3, T>(s + m[0], s + m[1]);
	}
	template<typename T> Matrix<2, 3, T> operator+(Matrix<2, 3, T> const& m1, Matrix<2, 3, T> const& m2)
	{
		return Matrix<2, 3, T>(m1[0] + m2[0], m1[1] + m2[1]);
	}
	#pragma endregion

	#pragma region COperators-
	template<typename T> Matrix<2, 3, T> operator-(Matrix<2, 3, T> const& m)
	{
		return Matrix<2, 3, T>(-m[0], -m[1]);
	}
	template<typename T> Matrix<2, 3, T> operator-(Matrix<2, 3, T> const& m, T s)
	{
		return Matrix<2, 3, T>(m[0] - s, m[1] - s);
	}
	template<typename T> Matrix<2, 3, T> operator-(T s, Matrix<2, 3, T> const& m)
	{
		return Matrix<2, 3, T>(s - m[0], s - m[1]);
	}
	template<typename T> Matrix<2, 3, T> operator-(Matrix<2, 3, T> const& m1, Matrix<2, 3, T> const& m2)
	{
		return Matrix<2, 3, T>(m1[0] - m2[0], m1[1] - m2[1]);
	}
	#pragma endregion

	#pragma region COperators*
	template<typename T> Matrix<2, 3, T> operator*(Matrix<2, 3, T> const& m, T s)
	{
		return Matrix<2, 3, T>(m[0] * s, m[1] * s);
	}
	template<typename T> Matrix<2, 3, T> operator*(T s, Matrix<2, 3, T> const& m)
	{
		return Matrix<2, 3, T>(s * m[0], s * m[1]);
	}
	template<typename T> typename Matrix<2, 3, T>::col_t operator*(Matrix<2, 3, T> const& m, typename Matrix<2, 3, T>::row_t const& v)
	{
		return typename Matrix<2, 3, T>::col_t(
			m[0][0] * v.x + m[1][0] * v.y,
			m[0][1] * v.x + m[1][1] * v.y,
			m[0][2] * v.x + m[1][2] * v.y);
	}
	template<typename T> typename Matrix<2, 3, T>::row_t operator*(typename Matrix<2, 3, T>::col_t const& v, Matrix<2, 3, T> const& m)
	{
		return typename Matrix<2, 3, T>::row_t(
			v.x * m[0][0] + v.y * m[0][1] + v.z * m[0][2],
			v.x * m[1][0] + v.y * m[1][1] + v.z * m[1][2]);
	}
	template<typename T> Matrix<2, 3, T> operator*(Matrix<2, 3, T> const& m1, Matrix<2, 2, T> const& m2)
	{
		return Matrix<2, 3, T>(
			m1[0][0] * m2[0][0] + m1[1][0] * m2[0][1],
			m1[0][1] * m2[0][0] + m1[1][1] * m2[0][1],
			m1[0][2] * m2[0][0] + m1[1][2] * m2[0][1],
			m1[0][0] * m2[1][0] + m1[1][0] * m2[1][1],
			m1[0][1] * m2[1][0] + m1[1][1] * m2[1][1],
			m1[0][2] * m2[1][0] + m1[1][2] * m2[1][1]);
	}
	template<typename T> Matrix<3, 3, T> operator*(Matrix<2, 3, T> const& m1, Matrix<3, 2, T> const& m2)
	{
		return Matrix<3, 3, T>(
			m1[0][0] * m2[0][0] + m1[1][0] * m2[0][1],
			m1[0][1] * m2[0][0] + m1[1][1] * m2[0][1],
			m1[0][2] * m2[0][0] + m1[1][2] * m2[0][1],
			m1[0][0] * m2[1][0] + m1[1][0] * m2[1][1],
			m1[0][1] * m2[1][0] + m1[1][1] * m2[1][1],
			m1[0][2] * m2[1][0] + m1[1][2] * m2[1][1],
			m1[0][0] * m2[2][0] + m1[1][0] * m2[2][1],
			m1[0][1] * m2[2][0] + m1[1][1] * m2[2][1],
			m1[0][2] * m2[2][0] + m1[1][2] * m2[2][1]);
	}
	template<typename T> Matrix<4, 3, T> operator*(Matrix<2, 3, T> const& m1, Matrix<4, 2, T> const& m2)
	{
		return Matrix<4, 3, T>(
			m1[0][0] * m2[0][0] + m1[1][0] * m2[0][1],
			m1[0][1] * m2[0][0] + m1[1][1] * m2[0][1],
			m1[0][2] * m2[0][0] + m1[1][2] * m2[0][1],
			m1[0][0] * m2[1][0] + m1[1][0] * m2[1][1],
			m1[0][1] * m2[1][0] + m1[1][1] * m2[1][1],
			m1[0][2] * m2[1][0] + m1[1][2] * m2[1][1],
			m1[0][0] * m2[2][0] + m1[1][0] * m2[2][1],
			m1[0][1] * m2[2][0] + m1[1][1] * m2[2][1],
			m1[0][2] * m2[2][0] + m1[1][2] * m2[2][1],
			m1[0][0] * m2[3][0] + m1[1][0] * m2[3][1],
			m1[0][1] * m2[3][0] + m1[1][1] * m2[3][1],
			m1[0][2] * m2[3][0] + m1[1][2] * m2[3][1]);
	}
	#pragma endregion

	#pragma region COperators/
	template<typename T> Matrix<2, 3, T> operator/(Matrix<2, 3, T> const& m, T s)
	{
		return Matrix<2, 3, T>(m[0] / s, m[1] / s);
	}
	template<typename T> Matrix<2, 3, T> operator/(T s, Matrix<2, 3, T> const& m)
	{
		return Matrix<2, 3, T>(s / m[0], s / m[1]);
	}
	#pragma endregion

	///////////////////////
	// BOOLEAN OPERATORS //
	///////////////////////

	#pragma region BOperators
	template<typename T> bool operator==(Matrix<2, 3, T> const& m1, Matrix<2, 3, T> const& m2)
	{
		return (m1[0] == m2[0]) && (m1[1] == m2[1]);
	}
	template<typename T> bool operator!=(Matrix<2, 3, T> const& m1, Matrix<2, 3, T> const& m2)
	{
		return (m1[0] != m2[0]) || (m1[1] != m2[1]);
	}
	#pragma endregion

	//////////////////////
	// TYPE DEFINITIONS //
	//////////////////////

	typedef Matrix< 2, 3, float        >   Mat2x3;
	typedef Matrix< 2, 3, float        >  fMat2x3;
	typedef Matrix< 2, 3, double       >  dMat2x3;
	typedef Matrix< 2, 3, int          >  iMat2x3;
	typedef Matrix< 2, 3, unsigned int > uiMat2x3;
	typedef Matrix< 2, 3, bool         >  bMat2x3;
}
