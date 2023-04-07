#pragma once

#include "Types.hpp"

#include <cmath>
#include <cstdint>

namespace JMath {

// -----------------------------------------------------------------------------
// -------------------------------- Declarations -------------------------------
// -----------------------------------------------------------------------------

// ------------------------------ Type Definitions -----------------------------

using Vec3   = Vector< 3,    float >;
using Vec3f  = Vector< 3,    float >;
using Vec3d  = Vector< 3,   double >;
using Vec3i  = Vector< 3,  int32_t >;
using Vec3ui = Vector< 3, uint32_t >;

template<typename T>
struct Vector<3, T> {
public:

// ------------------------------------ Data -----------------------------------

	union { T x, r; };
	union { T y, g; };
	union { T z, b; };

// -------------------------------- Constructors -------------------------------

	inline Vector();
	inline Vector(T x, T y, T z);

	template<typename U>
	inline explicit Vector<3, T>(const Vector<3, U>& other);

// ----------------------------------- Access ----------------------------------

	inline T& operator[](int index);
	inline const T& operator[](int index) const;

// --------------------------------- Operators ---------------------------------

	inline Vector<3, T>& operator*=(T scalar);
	inline Vector<3, T>& operator/=(T scalar);
	inline Vector<3, T>& operator+=(const Vector<3, T>& other);
	inline Vector<3, T>& operator-=(const Vector<3, T>& other);

};

// ----------------------------- External Operators ----------------------------

template<typename T>
inline Vector<3, T> operator*(const Vector<3, T>& vector, T scalar);

template<typename T>
inline Vector<3, T> operator/(const Vector<3, T>& vector, T scalar);

template<typename T>
inline Vector<3, T> operator-(const Vector<3, T>& vector);

template<typename T>
inline Vector<3, T> operator+(const Vector<3, T>& first, const Vector<3, T>& second);

template<typename T>
inline Vector<3, T> operator-(const Vector<3, T>& first, const Vector<3, T>& second);

// ----------------------------- External Functions ----------------------------

template<typename T>
inline float Magnitude(const Vector<3, T>& vector);

template<typename T>
inline Vector<3, T> Normalize(const Vector<3, T>& vector);

template<typename T>
inline T Dot(const Vector<3, T>& first, const Vector<3, T>& second);

template<typename T>
inline Vector<3, T> Cross(const Vector<3, T>& first, const Vector<3, T>& second);

template<typename T>
inline Vector<3, T> Project(const Vector<3, T>& first, const Vector<3, T>& second);

template<typename T>
inline Vector<3, T> Reject(const Vector<3, T>& first, const Vector<3, T>& second);

// -----------------------------------------------------------------------------
// ------------------------------ Implementations ------------------------------
// -----------------------------------------------------------------------------

// -------------------------------- Constructors -------------------------------

template<typename T>
inline Vector<3, T>::Vector() = default;

template<typename T>
inline Vector<3, T>::Vector(T x, T y, T z)
	: x(x), y(y), z(z) { }

template<typename T>
template<typename U>
inline Vector<3, T>::Vector(const Vector<3, U>& other)
	: x(static_cast<T>(other.x)),
	y(static_cast<T>(other.y)),
	z(static_cast<T>(other.z)) { }

// ----------------------------------- Access ----------------------------------

template<typename T>
inline T& Vector<3, T>::operator[](int index) {
	return ((&x)[index]);
}

template<typename T>
inline const T& Vector<3, T>::operator[](int index) const {
	return ((&x)[index]);
}

// --------------------------------- Operators ---------------------------------

template<typename T>
inline Vector<3, T>& Vector<3, T>::operator*=(T scalar) {
	x *= scalar;
	y *= scalar;
	z *= scalar;
	return *this;
}

template<typename T>
inline Vector<3, T>& Vector<3, T>::operator/=(T scalar) {
	scalar = 1.0f / scalar;
	x *= scalar;
	y *= scalar;
	z *= scalar;
	return *this;
}

template<typename T>
inline Vector<3, T>& Vector<3, T>::operator+=(const Vector<3, T>& other) {
	x += other.x;
	y += other.y;
	z += other.z;
	return *this;
}

template<typename T>
inline Vector<3, T>& Vector<3, T>::operator-=(const Vector<3, T>& other) {
	x -= other.x;
	y -= other.y;
	z -= other.z;
	return *this;
}

// ----------------------------- External Operators ----------------------------

template<typename T>
inline Vector<3, T> operator*(const Vector<3, T>& vector, T scalar) {
	return Vector<3, T>(
		vector.x * scalar,
		vector.y * scalar,
		vector.z * scalar);
}

template<typename T>
inline Vector<3, T> operator/(const Vector<3, T>& vector, T scalar) {
	scalar = 1.0f / scalar;
	return Vector<3, T>(
		vector.x * scalar,
		vector.y * scalar,
		vector.z * scalar);
}

template<typename T>
inline Vector<3, T> operator-(const Vector<3, T>& vector) {
	return Vector<3, T>(-vector.x, -vector.y, -vector.z);
}

template<typename T>
inline Vector<3, T> operator+(const Vector<3, T>& first,
	const Vector<3, T>& second) {
	return Vector<3, T>(
		first.x + second.x,
		first.y + second.y,
		first.z + second.z);
}

template<typename T>
inline Vector<3, T> operator-(const Vector<3, T>& first,
	const Vector<3, T>& second) {
	return Vector<3, T>(
		first.x - second.x,
		first.y - second.y,
		first.z - second.z);
}

// ----------------------------- External Functions ----------------------------

template<typename T>
inline float Magnitude(const Vector<3, T>& vector) {
	return std::sqrt(
		(vector.x * vector.x) +
		(vector.y * vector.y) +
		(vector.z * vector.z));
}

template<typename T>
inline Vector<3, T> Normalize(const Vector<3, T>& vector) {
	return vector / Magnitude(vector);
}

template<typename T>
inline T Dot(const Vector<3, T>& first, const Vector<3, T>& second) {
	return (first.x * second.x) + (first.y * second.y) + (first.z * second.z);
}

template<typename T>
inline Vector<3, T> Cross(const Vector<3, T>& first,
	const Vector<3, T>& second) {
	return Vector<3, T>(
		(first.y * second.z) - (first.z * second.y),
		(first.z * second.x) - (first.x * second.z),
		(first.x * second.y) - (first.y * second.x));
}

template<typename T>
inline Vector<3, T> Project(const Vector<3, T>& first,
	const Vector<3, T>& second) {
	return second * (Dot(first, second) / Dot(second, second));
}

template<typename T>
inline Vector<3, T> Reject(const Vector<3, T>& first,
	const Vector<3, T>& second) {
	return first - (second * (Dot(first, second) / Dot(second, second)));
}

} // namespace JMath
