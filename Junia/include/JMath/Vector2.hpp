#pragma once

#include "Types.hpp"

#include <cmath>
#include <cstdint>

namespace JMath {

// -----------------------------------------------------------------------------
// -------------------------------- Declarations -------------------------------
// -----------------------------------------------------------------------------

// ------------------------------ Type Definitions -----------------------------

using Vec2   = Vector< 2,    float >;
using Vec2f  = Vector< 2,    float >;
using Vec2d  = Vector< 2,   double >;
using Vec2i  = Vector< 2,  int32_t >;
using Vec2ui = Vector< 2, uint32_t >;

template<typename T>
struct Vector<2, T> {
public:

// ------------------------------------ Data -----------------------------------

	union { T x, r; };
	union { T y, g; };

// -------------------------------- Constructors -------------------------------

	inline Vector();
	inline Vector(T x, T y);

	template<typename U>
	inline explicit Vector<2, T>(const Vector<2, U>& other);

// ----------------------------------- Access ----------------------------------

	inline T& operator[](int index);
	inline const T& operator[](int index) const;

// --------------------------------- Operators ---------------------------------

	inline Vector<2, T>& operator*=(T scalar);
	inline Vector<2, T>& operator/=(T scalar);
	inline Vector<2, T>& operator+=(const Vector<2, T>& other);
	inline Vector<2, T>& operator-=(const Vector<2, T>& other);

};

// ----------------------------- External Operators ----------------------------

template<typename T>
inline Vector<2, T> operator*(const Vector<2, T>& vector, T scalar);

template<typename T>
inline Vector<2, T> operator/(const Vector<2, T>& vector, T scalar);

template<typename T>
inline Vector<2, T> operator-(const Vector<2, T>& vector);

template<typename T>
inline Vector<2, T> operator+(const Vector<2, T>& first, const Vector<2, T>& second);

template<typename T>
inline Vector<2, T> operator-(const Vector<2, T>& first, const Vector<2, T>& second);

// ----------------------------- External Functions ----------------------------

template<typename T>
inline float Magnitude(const Vector<2, T>& vector);

template<typename T>
inline Vector<2, T> Normalize(const Vector<2, T>& vector);

template<typename T>
inline T Dot(const Vector<2, T>& first, const Vector<2, T>& second);

template<typename T>
inline Vector<2, T> Project(const Vector<2, T>& first, const Vector<2, T>& second);

template<typename T>
inline Vector<2, T> Reject(const Vector<2, T>& first, const Vector<2, T>& second);

// -----------------------------------------------------------------------------
// ------------------------------ Implementations ------------------------------
// -----------------------------------------------------------------------------

// -------------------------------- Constructors -------------------------------

template<typename T>
inline Vector<2, T>::Vector() = default;

template<typename T>
inline Vector<2, T>::Vector(T x, T y)
	: x(x), y(y) { }

template<typename T>
template<typename U>
inline Vector<2, T>::Vector(const Vector<2, U>& other)
	: x(static_cast<T>(other.x)),
	y(static_cast<T>(other.y)) { }

// ----------------------------------- Access ----------------------------------

template<typename T>
inline T& Vector<2, T>::operator[](int index) {
	return ((&x)[index]);
}

template<typename T>
inline const T& Vector<2, T>::operator[](int index) const {
	return ((&x)[index]);
}

// --------------------------------- Operators ---------------------------------

template<typename T>
inline Vector<2, T>& Vector<2, T>::operator*=(T scalar) {
	x *= scalar;
	y *= scalar;
	return *this;
}

template<typename T>
inline Vector<2, T>& Vector<2, T>::operator/=(T scalar) {
	scalar = 1.0f / scalar;
	x *= scalar;
	y *= scalar;
	return *this;
}

template<typename T>
inline Vector<2, T>& Vector<2, T>::operator+=(const Vector<2, T>& other) {
	x += other.x;
	y += other.y;
	return *this;
}

template<typename T>
inline Vector<2, T>& Vector<2, T>::operator-=(const Vector<2, T>& other) {
	x -= other.x;
	y -= other.y;
	return *this;
}

// ----------------------------- External Operators ----------------------------

template<typename T>
inline Vector<2, T> operator*(const Vector<2, T>& vector, T scalar) {
	return Vector<2, T>(
		vector.x * scalar,
		vector.y * scalar);
}

template<typename T>
inline Vector<2, T> operator/(const Vector<2, T>& vector, T scalar) {
	scalar = 1.0f / scalar;
	return Vector<2, T>(
		vector.x * scalar,
		vector.y * scalar);
}

template<typename T>
inline Vector<2, T> operator-(const Vector<2, T>& vector) {
	return Vector<2, T>(-vector.x, -vector.y);
}

template<typename T>
inline Vector<2, T> operator+(const Vector<2, T>& first,
	const Vector<2, T>& second) {
	return Vector<2, T>(
		first.x + second.x,
		first.y + second.y);
}

template<typename T>
inline Vector<2, T> operator-(const Vector<2, T>& first,
	const Vector<2, T>& second) {
	return Vector<2, T>(
		first.x - second.x,
		first.y - second.y);
}

// ----------------------------- External Functions ----------------------------

template<typename T>
inline float Magnitude(const Vector<2, T>& vector) {
	return std::sqrt(
		(vector.x * vector.x) +
		(vector.y * vector.y));
}

template<typename T>
inline Vector<2, T> Normalize(const Vector<2, T>& vector) {
	return vector / Magnitude(vector);
}

template<typename T>
inline T Dot(const Vector<2, T>& first, const Vector<2, T>& second) {
	return (first.x * second.x) + (first.y * second.y);
}

template<typename T>
inline Vector<2, T> Project(const Vector<2, T>& first,
	const Vector<2, T>& second) {
	return second * (Dot(first, second) / Dot(second, second));
}

template<typename T>
inline Vector<2, T> Reject(const Vector<2, T>& first,
	const Vector<2, T>& second) {
	return first - (second * (Dot(first, second) / Dot(second, second)));
}

} // namespace JMath
