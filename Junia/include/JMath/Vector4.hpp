#pragma once

#include "Types.hpp"

#include <cmath>
#include <cstdint>

namespace JMath {

// -----------------------------------------------------------------------------
// -------------------------------- Declarations -------------------------------
// -----------------------------------------------------------------------------

// ------------------------------ Type Definitions -----------------------------

using Vec4   = Vector< 4,    float >;
using Vec4f  = Vector< 4,    float >;
using Vec4d  = Vector< 4,   double >;
using Vec4i  = Vector< 4,  int32_t >;
using Vec4ui = Vector< 4, uint32_t >;

#ifdef _MSC_VER
#pragma pack(push, 1)
#endif

template<typename T>
struct Vector<4, T> {
public:

// ------------------------------------ Data -----------------------------------

	union { T x, r; };
	union { T y, g; };
	union { T z, b; };
	union { T w, a; };

// -------------------------------- Constructors -------------------------------

	inline Vector();
	inline Vector(T x, T y, T z, T w);

	template<typename U>
	inline explicit Vector<4, T>(const Vector<4, U>& other);

// ----------------------------------- Access ----------------------------------

	inline T& operator[](int index);
	inline const T& operator[](int index) const;

// --------------------------------- Operators ---------------------------------

	inline Vector<4, T>& operator*=(T scalar);
	inline Vector<4, T>& operator/=(T scalar);
	inline Vector<4, T>& operator+=(const Vector<4, T>& other);
	inline Vector<4, T>& operator-=(const Vector<4, T>& other);

}
#if defined(__GNUC__) || defined(__clang__)
__attribute__((__packed__))
#endif
;

#ifdef _MSC_VER
#pragma pack(pop)
#endif

// ----------------------------- External Operators ----------------------------

template<typename T>
inline Vector<4, T> operator*(const Vector<4, T>& vector, T scalar);

template<typename T>
inline Vector<4, T> operator/(const Vector<4, T>& vector, T scalar);

template<typename T>
inline Vector<4, T> operator-(const Vector<4, T>& vector);

template<typename T>
inline Vector<4, T> operator+(const Vector<4, T>& first, const Vector<4, T>& second);

template<typename T>
inline Vector<4, T> operator-(const Vector<4, T>& first, const Vector<4, T>& second);

// ----------------------------- External Functions ----------------------------

template<typename T>
inline float Magnitude(const Vector<4, T>& vector);

template<typename T>
inline Vector<4, T> Normalize(const Vector<4, T>& vector);

template<typename T>
inline T Dot(const Vector<4, T>& first, const Vector<4, T>& second);

// -----------------------------------------------------------------------------
// ------------------------------ Implementations ------------------------------
// -----------------------------------------------------------------------------

// -------------------------------- Constructors -------------------------------

template<typename T>
inline Vector<4, T>::Vector() {
	x = static_cast<T>(0);
	y = static_cast<T>(0);
	z = static_cast<T>(0);
	w = static_cast<T>(0);
}

template<typename T>
inline Vector<4, T>::Vector(T x, T y, T z, T w)
	: x(x), y(y), z(z), w(w) { }

template<typename T>
template<typename U>
inline Vector<4, T>::Vector(const Vector<4, U>& other)
	: x(static_cast<T>(other.x)),
	y(static_cast<T>(other.y)),
	z(static_cast<T>(other.z)),
	w(static_cast<T>(other.w)) { }

// ----------------------------------- Access ----------------------------------

template<typename T>
inline T& Vector<4, T>::operator[](int index) {
	return ((&x)[index]);
}

template<typename T>
inline const T& Vector<4, T>::operator[](int index) const {
	return ((&x)[index]);
}

// --------------------------------- Operators ---------------------------------

template<typename T>
inline Vector<4, T>& Vector<4, T>::operator*=(T scalar) {
	x *= scalar;
	y *= scalar;
	z *= scalar;
	w *= scalar;
	return *this;
}

template<typename T>
inline Vector<4, T>& Vector<4, T>::operator/=(T scalar) {
	scalar = 1.0f / scalar;
	x *= scalar;
	y *= scalar;
	z *= scalar;
	w *= scalar;
	return *this;
}

template<typename T>
inline Vector<4, T>& Vector<4, T>::operator+=(const Vector<4, T>& other) {
	x += other.x;
	y += other.y;
	z += other.z;
	w += other.w;
	return *this;
}

template<typename T>
inline Vector<4, T>& Vector<4, T>::operator-=(const Vector<4, T>& other) {
	x -= other.x;
	y -= other.y;
	z -= other.z;
	w -= other.w;
	return *this;
}

// ----------------------------- External Operators ----------------------------

template<typename T>
inline Vector<4, T> operator*(const Vector<4, T>& vector, T scalar) {
	return Vector<4, T>(
		vector.x * scalar,
		vector.y * scalar,
		vector.z * scalar,
		vector.w * scalar);
}

template<typename T>
inline Vector<4, T> operator/(const Vector<4, T>& vector, T scalar) {
	scalar = 1.0f / scalar;
	return Vector<4, T>(
		vector.x * scalar,
		vector.y * scalar,
		vector.z * scalar,
		vector.w * scalar);
}

template<typename T>
inline Vector<4, T> operator-(const Vector<4, T>& vector) {
	return Vector<4, T>(-vector.x, -vector.y, -vector.z, -vector.w);
}

template<typename T>
inline Vector<4, T> operator+(const Vector<4, T>& first,
	const Vector<4, T>& second) {
	return Vector<4, T>(
		first.x + second.x,
		first.y + second.y,
		first.z + second.z,
		first.w + second.w);
}

template<typename T>
inline Vector<4, T> operator-(const Vector<4, T>& first,
	const Vector<4, T>& second) {
	return Vector<4, T>(
		first.x - second.x,
		first.y - second.y,
		first.z - second.z,
		first.w - second.w);
}

// ----------------------------- External Functions ----------------------------

template<typename T>
inline float Magnitude(const Vector<4, T>& vector) {
	return std::sqrt(
		(vector.x * vector.x) +
		(vector.y * vector.y) +
		(vector.z * vector.z) +
		(vector.w * vector.w));
}

template<typename T>
inline Vector<4, T> Normalize(const Vector<4, T>& vector) {
	return vector / Magnitude(vector);
}

template<typename T>
inline T Dot(const Vector<4, T>& first, const Vector<4, T>& second) {
	return (first.x * second.x) + (first.y * second.y) + (first.z * second.z) + (first.w * second.w);
}

} // namespace JMath
