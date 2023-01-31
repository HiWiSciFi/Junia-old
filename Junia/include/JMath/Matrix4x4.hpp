#pragma once

#include <JMath/Types.hpp>
#include <JMath/Mathf.hpp>

namespace JMath
{
	template<typename T>
	struct Matrix<4, 4, T>
	{
		typedef Vector<4, T> row_t;
		typedef Vector<4, T> col_t;

	private:

		//////////
		// DATA //
		//////////

		col_t value[4];
		static constexpr unsigned char length() { return 4; }

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

		constexpr Matrix(Matrix<4, 4, T> const& m) :
			value{
			col_t(m[0]),
			col_t(m[1]),
			col_t(m[2]),
			col_t(m[3]) }
		{
		}

		explicit constexpr Matrix(T s) :
			value{
			col_t(s, 0, 0, 0),
			col_t(0, s, 0, 0),
			col_t(0, 0, s, 0),
			col_t(0, 0, 0, s) }
		{
		}

		constexpr Matrix(
			T const& x1, T const& y1, T const& z1, T const& w1,
			T const& x2, T const& y2, T const& z2, T const& w2,
			T const& x3, T const& y3, T const& z3, T const& w3,
			T const& x4, T const& y4, T const& z4, T const& w4) :
			value{
				col_t(x1, y1, z1, w1),
				col_t(x2, y2, z2, w2),
				col_t(x3, y3, z3, w3),
				col_t(x4, y4, z4, w4) }
		{
		}

		constexpr Matrix(
			col_t const& v1,
			col_t const& v2,
			col_t const& v3,
			col_t const& v4) :
			value{
				col_t(v1),
				col_t(v2),
				col_t(v3),
				col_t(v4) }
		{
		}
		#pragma endregion

		#pragma region ConstructorsVectors
		template<
			typename X1, typename Y1, typename Z1, typename W1,
			typename X2, typename Y2, typename Z2, typename W2,
			typename X3, typename Y3, typename Z3, typename W3,
			typename X4, typename Y4, typename Z4, typename W4>
		constexpr Matrix(
			X1 const& x1, Y1 const& y1, Z1 const& z1, W1 const& w1,
			X2 const& x2, Y2 const& y2, Z2 const& z2, W2 const& w2,
			X3 const& x3, Y3 const& y3, Z3 const& z3, W3 const& w3,
			X4 const& x4, Y4 const& y4, Z4 const& z4, W4 const& w4) :
			value{
				col_t(static_cast<T>(x1), static_cast<T>(y1), static_cast<T>(z1), static_cast<T>(w1)),
				col_t(static_cast<T>(x2), static_cast<T>(y2), static_cast<T>(z2), static_cast<T>(w2)),
				col_t(static_cast<T>(x3), static_cast<T>(y3), static_cast<T>(z3), static_cast<T>(w3)),
				col_t(static_cast<T>(x4), static_cast<T>(y4), static_cast<T>(z4), static_cast<T>(w4)) }
		{
		}

		template<typename A, typename B, typename C, typename D>
		constexpr Matrix(
			Vector<4, A> const& v1,
			Vector<4, B> const& v2,
			Vector<4, C> const& v3,
			Vector<4, D> const& v4) :
			value{ col_t(v1), col_t(v2), col_t(v3), col_t(v4) }
		{
		}
		#pragma endregion

		#pragma region ConstructorsSize
		template<typename U> explicit constexpr Matrix(Matrix<4, 4, U> const& m) :
			value{ col_t(m[0]), col_t(m[1]), col_t(m[2]), col_t(m[3]) }
		{
		}

		explicit constexpr Matrix(Matrix<2, 2, T> const& m) : value{ col_t(m[0], 0, 0), col_t(m[1], 0, 0), col_t(0, 0, 1, 0), col_t(0, 0, 0, 1) } { }
		explicit constexpr Matrix(Matrix<3, 3, T> const& m) : value{ col_t(m[0], 0), col_t(m[1], 0), col_t(m[2], 0), col_t(0, 0, 0, 1) } { }
		explicit constexpr Matrix(Matrix<2, 3, T> const& m) : value{ col_t(m[0], 0), col_t(m[1], 0), col_t(0, 0, 1, 0), col_t(0, 0, 0, 1) } { }
		explicit constexpr Matrix(Matrix<3, 2, T> const& m) : value{ col_t(m[0], 0, 0), col_t(m[1], 0, 0), col_t(m[2], 1, 0), col_t(0, 0, 0, 1) } { }
		explicit constexpr Matrix(Matrix<2, 4, T> const& m) : value{ col_t(m[0]), col_t(m[1]), col_t(0, 0, 1, 0), col_t(0, 0, 0, 1) } { }
		explicit constexpr Matrix(Matrix<4, 2, T> const& m) : value{ col_t(m[0], 0, 0), col_t(m[1], 0, 0), col_t(0, 0, 1, 0), col_t(0, 0, 0, 1) } { }
		explicit constexpr Matrix(Matrix<3, 4, T> const& m) : value{ col_t(m[0]), col_t(m[1]), col_t(m[2]), col_t(0, 0, 0, 1) } { }
		explicit constexpr Matrix(Matrix<4, 3, T> const& m) : value{ col_t(m[0], 0), col_t(m[1], 0), col_t(m[2], 0), col_t(m[3], 1) } { }
		#pragma endregion

		//////////////////////////
		// ASSIGNMENT OPERATORS //
		//////////////////////////

		#pragma region AOperators=
		template<typename U> Matrix<4, 4, T>& operator=(Matrix<4, 4, U> const& m)
		{
			this->value[0] = m[0];
			this->value[1] = m[1];
			this->value[2] = m[2];
			this->value[3] = m[3];
			return *this;
		}
		#pragma endregion

		#pragma region AOperators+=
		template<typename U> Matrix<4, 4, T>& operator+=(U s)
		{
			this->value[0] += s;
			this->value[1] += s;
			this->value[2] += s;
			this->value[3] += s;
			return *this;
		}
		template<typename U> Matrix<4, 4, T>& operator+=(Matrix<4, 4, U> const& m)
		{
			this->value[0] += m[0];
			this->value[1] += m[1];
			this->value[2] += m[2];
			this->value[3] += m[3];
			return *this;
		}
		#pragma endregion

		#pragma region AOperators-=
		template<typename U> Matrix<4, 4, T>& operator-=(U s)
		{
			this->value[0] -= s;
			this->value[1] -= s;
			this->value[2] -= s;
			this->value[3] -= s;
			return *this;
		}
		template<typename U> Matrix<4, 4, T>& operator-=(Matrix<4, 4, U> const& m)
		{
			this->value[0] -= m[0];
			this->value[1] -= m[1];
			this->value[2] -= m[2];
			this->value[3] -= m[3];
			return *this;
		}
		#pragma endregion

		#pragma region AOperators*=
		template<typename U> Matrix<4, 4, T>& operator*=(U s)
		{
			this->value[0] *= s;
			this->value[1] *= s;
			this->value[2] *= s;
			this->value[3] *= s;
			return *this;
		}
		template<typename U> Matrix<4, 4, T>& operator*=(Matrix<4, 4, U> const& m)
		{
			return (*this = *this * m);
		}
		#pragma endregion

		#pragma region AOperators/=
		template<typename U> Matrix<4, 4, T>& operator/=(U s)
		{
			this->value[0] /= s;
			this->value[1] /= s;
			this->value[2] /= s;
			this->value[4] /= s;
			return *this;
		}
		template<typename U> Matrix<4, 4, T>& operator/=(Matrix<4, 4, U> const& m)
		{
			return *this *= inverse(m);
		}
		#pragma endregion

		/////////////////////////
		// INCREMENT OPERATORS //
		/////////////////////////

		#pragma region IOperators
		Matrix<4, 4, T>& operator++()
		{
			++this->value[0];
			++this->value[1];
			++this->value[2];
			++this->value[3];
			return *this;
		}
		Matrix<4, 4, T>& operator--()
		{
			--this->value[0];
			--this->value[1];
			--this->value[2];
			--this->value[3];
			return *this;
		}
		Matrix<4, 4, T> operator++(int)
		{
			Matrix<4, 4, T> r(*this);
			++* this;
			return r;
		}
		Matrix<4, 4, T> operator--(int)
		{
			Matrix<4, 4, T> r(*this);
			--* this;
			return r;
		}
		#pragma endregion
	};

	////////////////////
	// CALC OPERATORS //
	////////////////////

	#pragma region COperators+
	template<typename T> Matrix<4, 4, T> operator+(Matrix<4, 4, T> const& m)
	{
		return m;
	}
	template<typename T> Matrix<4, 4, T> operator+(Matrix<4, 4, T> const& m, T s)
	{
		return Matrix<4, 4, T>(m[0] + s, m[1] + s, m[2] + s, m[3] + s);
	}
	template<typename T> Matrix<4, 4, T> operator+(T s, Matrix<4, 4, T> const& m)
	{
		return Matrix<4, 4, T>(s + m[0], s + m[1], s + m[2], s + m[3]);
	}
	template<typename T> Matrix<4, 4, T> operator+(Matrix<4, 4, T> const& m1, Matrix<4, 4, T> const& m2)
	{
		return Matrix<4, 4, T>(m1[0] + m2[0], m1[1] + m2[1], m1[2] + m2[2], m1[3] + m2[3]);
	}
	#pragma endregion

	#pragma region COperators-
	template<typename T> Matrix<4, 4, T> operator-(Matrix<4, 4, T> const& m)
	{
		return Matrix<4, 4, T>(-m[0], -m[1], -m[2], -m[3]);
	}
	template<typename T> Matrix<4, 4, T> operator-(Matrix<4, 4, T> const& m, T s)
	{
		return Matrix<4, 4, T>(m[0] - s, m[1] - s, m[2] - s, m[3] - s);
	}
	template<typename T> Matrix<4, 4, T> operator-(T s, Matrix<4, 4, T> const& m)
	{
		return Matrix<4, 4, T>(s - m[0], s - m[1], s - m[2], s - m[3]);
	}
	template<typename T> Matrix<4, 4, T> operator-(Matrix<4, 4, T> const& m1, Matrix<4, 4, T> const& m2)
	{
		return Matrix<4, 4, T>(m1[0] - m2[0], m1[1] - m2[1], m1[2] - m2[2], m1[3] - m2[3]);
	}
	#pragma endregion

	#pragma region COperators*
	template<typename T> Matrix<4, 4, T> operator*(Matrix<4, 4, T> const& m, T s)
	{
		return Matrix<4, 4, T>(m[0] * s, m[1] * s, m[2] * s, m[3] * s);
	}
	template<typename T> Matrix<4, 4, T> operator*(T s, Matrix<4, 4, T> const& m)
	{
		return Matrix<4, 4, T>(s * m[0], s * m[1], s * m[2], s * m[3]);
	}
	template<typename T> typename Matrix<4, 4, T>::col_t operator*(Matrix<4, 4, T> const& m, typename Matrix<4, 4, T>::row_t const& v)
	{
		return typename Matrix<4, 4, T>::col_t(
			m[0][0] * v.x + m[1][0] * v.y + m[2][0] * v.z + m[3][0] * v.w,
			m[0][1] * v.x + m[1][1] * v.y + m[2][1] * v.z + m[3][1] * v.w,
			m[0][2] * v.x + m[1][2] * v.y + m[2][2] * v.z + m[3][2] * v.w,
			m[0][3] * v.x + m[1][3] * v.y + m[2][3] * v.z + m[3][3] * v.w);
	}
	template<typename T> typename Matrix<4, 4, T>::row_t operator*(typename Matrix<4, 4, T>::col_t const& v, Matrix<4, 4, T> const& m)
	{
		return typename Matrix<4, 4, T>::row_t(
			m[0][0] * v.x + m[0][1] * v.y + m[0][2] * v.z + m[0][3] * v.w,
			m[1][0] * v.x + m[1][1] * v.y + m[1][2] * v.z + m[1][3] * v.w,
			m[2][0] * v.x + m[2][1] * v.y + m[2][2] * v.z + m[2][3] * v.w,
			m[3][0] * v.x + m[3][1] * v.y + m[3][2] * v.z + m[3][3] * v.w);
	}
	template<typename T> Matrix<2, 4, T> operator*(Matrix<4, 4, T> const& m1, Matrix<2, 4, T> const& m2)
	{
		return Matrix<2, 4, T>(
			m1[0][0] * m2[0][0] + m1[1][0] * m2[0][1] + m1[2][0] * m2[0][2] + m1[3][0] * m2[0][3],
			m1[0][1] * m2[0][0] + m1[1][1] * m2[0][1] + m1[2][1] * m2[0][2] + m1[3][1] * m2[0][3],
			m1[0][2] * m2[0][0] + m1[1][2] * m2[0][1] + m1[2][2] * m2[0][2] + m1[3][2] * m2[0][3],
			m1[0][3] * m2[0][0] + m1[1][3] * m2[0][1] + m1[2][3] * m2[0][2] + m1[3][3] * m2[0][3],
			m1[0][0] * m2[1][0] + m1[1][0] * m2[1][1] + m1[2][0] * m2[1][2] + m1[3][0] * m2[1][3],
			m1[0][1] * m2[1][0] + m1[1][1] * m2[1][1] + m1[2][1] * m2[1][2] + m1[3][1] * m2[1][3],
			m1[0][2] * m2[1][0] + m1[1][2] * m2[1][1] + m1[2][2] * m2[1][2] + m1[3][2] * m2[1][3],
			m1[0][3] * m2[1][0] + m1[1][3] * m2[1][1] + m1[2][3] * m2[1][2] + m1[3][3] * m2[1][3]);
	}
	template<typename T> Matrix<3, 4, T> operator*(Matrix<4, 4, T> const& m1, Matrix<3, 4, T> const& m2)
	{
		return Matrix<3, 4, T>(
			m1[0][0] * m2[0][0] + m1[1][0] * m2[0][1] + m1[2][0] * m2[0][2] + m1[3][0] * m2[0][3],
			m1[0][1] * m2[0][0] + m1[1][1] * m2[0][1] + m1[2][1] * m2[0][2] + m1[3][1] * m2[0][3],
			m1[0][2] * m2[0][0] + m1[1][2] * m2[0][1] + m1[2][2] * m2[0][2] + m1[3][2] * m2[0][3],
			m1[0][3] * m2[0][0] + m1[1][3] * m2[0][1] + m1[2][3] * m2[0][2] + m1[3][3] * m2[0][3],
			m1[0][0] * m2[1][0] + m1[1][0] * m2[1][1] + m1[2][0] * m2[1][2] + m1[3][0] * m2[1][3],
			m1[0][1] * m2[1][0] + m1[1][1] * m2[1][1] + m1[2][1] * m2[1][2] + m1[3][1] * m2[1][3],
			m1[0][2] * m2[1][0] + m1[1][2] * m2[1][1] + m1[2][2] * m2[1][2] + m1[3][2] * m2[1][3],
			m1[0][3] * m2[1][0] + m1[1][3] * m2[1][1] + m1[2][3] * m2[1][2] + m1[3][3] * m2[1][3],
			m1[0][0] * m2[2][0] + m1[1][0] * m2[2][1] + m1[2][0] * m2[2][2] + m1[3][0] * m2[2][3],
			m1[0][1] * m2[2][0] + m1[1][1] * m2[2][1] + m1[2][1] * m2[2][2] + m1[3][1] * m2[2][3],
			m1[0][2] * m2[2][0] + m1[1][2] * m2[2][1] + m1[2][2] * m2[2][2] + m1[3][2] * m2[2][3],
			m1[0][3] * m2[2][0] + m1[1][3] * m2[2][1] + m1[2][3] * m2[2][2] + m1[3][3] * m2[2][3]);
	}
	template<typename T> Matrix<4, 4, T> operator*(Matrix<4, 4, T> const& m1, Matrix<4, 4, T> const& m2)
	{
		return Matrix<4, 4, T>(
			m1[0] * m2[0][0] + m1[1] * m2[0][1] + m1[2] * m2[0][2] + m1[3] * m2[3],
			m1[0] * m2[1][0] + m1[1] * m2[1][1] + m1[2] * m2[1][2] + m1[3] * m2[3],
			m1[0] * m2[2][0] + m1[1] * m2[2][1] + m1[2] * m2[2][2] + m1[3] * m2[3],
			m1[0] * m2[3][0] + m1[1] * m2[3][1] + m1[2] * m2[3][2] + m1[3] * m2[3]);
	}
	#pragma endregion

	#pragma region COperators/
	template<typename T> Matrix<4, 4, T> operator/(Matrix<4, 4, T> const& m, T s)
	{
		return Matrix<4, 4, T>(m[0] / s, m[1] / s, m[2] / s, m[3] / s);
	}
	template<typename T> Matrix<4, 4, T> operator/(T s, Matrix<4, 4, T> const& m)
	{
		return Matrix<4, 4, T>(s / m[0], s / m[1], s / m[2], s / m[3]);
	}
	template<typename T> typename Matrix<4, 4, T>::col_t operator/(Matrix<4, 4, T> const& m, typename Matrix<4, 4, T>::row_t const& v)
	{
		return inverse(m) * v;
	}
	template<typename T> typename Matrix<4, 4, T>::row_t operator/(typename Matrix<4, 4, T>::col_t const& v, Matrix<4, 4, T> const& m)
	{
		return v * inverse(m);
	}
	template<typename T> Matrix<4, 4, T> operator/(Matrix<4, 4, T> const& m1, Matrix<4, 4, T> const& m2)
	{
		Matrix<4, 4, T> r(m1);
		return r /= m2;
	}
	#pragma endregion

	///////////////////////
	// BOOLEAN OPERATORS //
	///////////////////////

	#pragma region BOperators
	template<typename T> bool operator==(Matrix<4, 4, T> const& m1, Matrix<4, 4, T> const& m2)
	{
		return (m1[0] == m2[0]) && (m1[1] == m2[1]) && (m1[2] == m2[2]) && (m1[3] == m2[3]);
	}
	template<typename T> bool operator!=(Matrix<4, 4, T> const& m1, Matrix<4, 4, T> const& m2)
	{
		return (m1[0] != m2[0]) || (m1[1] != m2[1]) || (m1[2] != m2[2]) || (m1[3] != m2[3]);
	}
	#pragma endregion

	//////////////////////
	// TYPE DEFINITIONS //
	//////////////////////

	typedef Matrix< 4, 4, float        >     Mat4;
	typedef Matrix< 4, 4, float        >    fMat4;
	typedef Matrix< 4, 4, double       >    dMat4;
	typedef Matrix< 4, 4, int          >    iMat4;
	typedef Matrix< 4, 4, unsigned int >   uiMat4;
	typedef Matrix< 4, 4, bool         >    bMat4;

	typedef Matrix< 4, 4, float        >   Mat4x4;
	typedef Matrix< 4, 4, float        >  fMat4x4;
	typedef Matrix< 4, 4, double       >  dMat4x4;
	typedef Matrix< 4, 4, int          >  iMat4x4;
	typedef Matrix< 4, 4, unsigned int > uiMat4x4;
	typedef Matrix< 4, 4, bool         >  bMat4x4;
}
