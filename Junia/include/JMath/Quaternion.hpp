#pragma once

namespace JMath {

template<typename T>
struct Quat {
private:

	//////////
	// DATA //
	//////////

	static constexpr unsigned char length() { return 4; }

public:

	T x, y, z, w;

	////////////
	// ACCESS //
	////////////

	#pragma region AccessFuncs
	constexpr T& operator[](unsigned char i) {
		switch (i) {
		default:
		case 0: return x;
		case 1: return y;
		case 2: return z;
		case 3: return w;
		}
	}

	constexpr T const& operator[](unsigned char i) const {
		switch (i) {
		default:
		case 0: return x;
		case 1: return y;
		case 2: return z;
		case 3: return w;
		}
	}
	#pragma endregion

	//////////////////
	// CONSTRUCTORS //
	//////////////////

	#pragma region ConstructorsBase
	constexpr Quat() = default;
	constexpr Quat(Quat<T> const& q) : x(q.x), y(q.y), z(q.z), w(q.w) { }

	constexpr Quat(T s, Vector<3, T> const& v) : x(v.x), y(v.y), z(v.z), w(s) { }

	constexpr Quat(T _x, T _y, T _z, T _w) : x(_x), y(_y), z(_z), w(_w) { }

	template<typename U> constexpr explicit Quat(Quat<U> const& q) :
		x(static_cast<T>(q.x)),
		y(static_cast<T>(q.y)),
		z(static_cast<T>(q.z)),
		w(static_cast<T>(q.w)) { }
	#pragma endregion

	#pragma region ConstructorsAxis
	/**
	 * @brief Create a quaternion from two normalized axis
	 * @param u the first normalized axis
	 * @param v the second normalized axis
	*/
	Quat(Vector<3, T> const& u, Vector<3, T> const& v) {
		T norm_u_norm_v = sqrt(Dot(u, u) * Dot(v, v));
		T real_part = norm_u_norm_v + Dot(u, v);
		Vector<3, T> t;

		if (real_part < static_cast<T>(1.e-6f) * norm_u_norm_v) {
			// If u and v are exactly opposite, rotate 180 degrees
			// around an arbitrary orthogonal axis. Axis normalisation
			// can happen later, during quaternion normalization.
			real_part = static_cast<T>(0);
			t = Abs(u.x) > Abs(u.z) ?
				Vector<3, T>(-u.y, u.x, static_cast<T>(0))
				: Vector<3, T>(static_cast<T>(0), -u.z, u.y);
		} else {
			t = Cross(u, v);
		}

		*this = Normalize(Quat<T>(real_part, t.x, t.y, t.z));
	}
	#pragma endregion

	#pragma region ConstructorsEuler
	/// Build a quaternion from euler angles (pitch, yaw, roll), in radians.
	constexpr explicit Quat(Vector<3, T> const& eulerAngle) {
		Vector<3, T> c = cos(eulerAngle * T(0.5));
		Vector<3, T> s = sin(eulerAngle * T(0.5));

		this->x = s.x * c.y * c.z - c.x * s.y * s.z;
		this->y = c.x * s.y * c.z + s.x * c.y * s.z;
		this->z = c.x * c.y * s.z - s.x * s.y * c.z;
		this->w = c.x * c.y * c.z + s.x * s.y * s.z;
	}
	explicit Quat(Matrix<3, 3, T> const& q);
	explicit Quat(Matrix<4, 4, T> const& q);
	#pragma endregion

	//////////////////////////
	// ASSIGNMENT OPERATORS //
	//////////////////////////

	#pragma region AOperators=
	constexpr Quat<T>& operator=(Quat<T> const& q) = default;

	template<typename U> constexpr Quat<T>& operator=(Quat<U> const& q) {
		x = static_cast<T>(q.x);
		y = static_cast<T>(q.y);
		z = static_cast<T>(q.z);
		return *this;
	}
	#pragma endregion

	#pragma region AOperators+=
	template<typename U> constexpr Quat<T>& operator+=(Quat<U> const& q) {
		x += static_cast<T>(q.x);
		y += static_cast<T>(q.y);
		z += static_cast<T>(q.z);
		w += static_cast<T>(q.w);
	}
	#pragma endregion

	#pragma region AOperators-=
	template<typename U> constexpr Quat<T>& operator-=(Quat<U> const& q) {
		x -= static_cast<T>(q.x);
		y -= static_cast<T>(q.y);
		z -= static_cast<T>(q.z);
		w -= static_cast<T>(q.w);
	}
	#pragma endregion

	#pragma region AOperators*=
	template<typename U> constexpr Quat<T>& operator*=(Quat<U> const& r) {
		Quat<T> const p(*this);
		Quat<T> const q(r);
		w = p.w * q.w - p.x * q.x - p.y * q.y - p.z * q.z;
		x = p.w * q.x + p.x * q.w + p.y * q.z - p.z * q.y;
		y = p.w * q.y + p.y * q.w + p.z * q.x - p.x * q.z;
		z = p.w * q.z + p.z * q.w + p.x * q.y - p.y * q.x;
		return *this;
	}

	template<typename U> constexpr Quat<T>& operator*=(U s);
	#pragma endregion

	#pragma region AOperators/=
	template<typename U> constexpr Quat<T>& operator/=(U s);
	#pragma endregion
};

////////////////////
// CALC OPERATORS //
////////////////////

#pragma region COperators+
template<typename T> constexpr Quat<T> operator+(Quat<T> const& q);
template<typename T> constexpr Quat<T> operator+(Quat<T> const& q, Quat<T> const& p);
#pragma endregion

#pragma region COperators-
template<typename T> constexpr Quat<T> operator-(Quat<T> const& q);
template<typename T> constexpr Quat<T> operator-(Quat<T> const& q, Quat<T> const& p);
#pragma endregion

#pragma region COperators*
template<typename T> constexpr Quat<T> operator*(Quat<T> const& q, Quat<T> const& p);
template<typename T> constexpr Vector<3, T> operator*(Quat<T> const& q, Vector<3, T> const& v);
template<typename T> constexpr Vector<3, T> operator*(Vector<3, T> const& v, Quat<T> const& q);
template<typename T> constexpr Vector<4, T> operator*(Quat<T> const& q, Vector<4, T> const& v);
template<typename T> constexpr Vector<4, T> operator*(Vector<4, T> const& v, Quat<T> const& q);
template<typename T> constexpr Quat<T> operator*(Quat<T> const& q, T const& s);
template<typename T> constexpr Quat<T> operator*(T const& s, Quat<T> const& q);
#pragma endregion

#pragma region COperators/
template<typename T> constexpr Quat<T> operator/(Quat<T> const& q, T const& s);
#pragma endregion

///////////////////////
// BOOLEAN OPERATORS //
///////////////////////

#pragma region BOperators
template<typename T> constexpr bool operator==(Quat<T> const& q1, Quat<T> const& q2) {
	return q1.x == q2.x && q1.y == q2.y && q1.z == q2.z && q1.w == q2.w;
}

template<typename T> constexpr bool operator!=(Quat<T> const& q1, Quat<T> const& q2) {
	return !(q1 == q2);
}
#pragma endregion

//////////////////////
// TYPE DEFINITIONS //
//////////////////////

typedef Quat< float        >   Quaternion;
typedef Quat< float        >  fQuaternion;
typedef Quat< double       >  dQuaternion;
typedef Quat< int          >  iQuaternion;
typedef Quat< unsigned int > uiQuaternion;

} // namespace JMath
