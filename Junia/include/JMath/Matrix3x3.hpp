#pragma once

#include <cmath>

#include "Types.hpp"
#include "Vector3.hpp"

namespace JMath {

// -----------------------------------------------------------------------------
// -------------------------------- Declarations -------------------------------
// -----------------------------------------------------------------------------

// ------------------------------ Type Definitions -----------------------------

using Mat3 = Matrix<3, 3, float>;

#ifdef _MSC_VER
#pragma pack(push, 1)
#endif

template<typename T>
struct Matrix<3, 3, T> {

// ------------------------------------ Data -----------------------------------

private:
	T data[3][3];

// -------------------------------- Constructors -------------------------------

public:
	inline Matrix<3, 3, T>();
	inline Matrix<3, 3, T>(T n00, T n01, T n02, T n10, T n11, T n12, T n20, T n21, T n22);
	inline Matrix<3, 3, T>(const Vector<3, T>& vec1, const Vector<3, T>& vec2, const Vector<3, T>& vec3);

// ----------------------------------- Access ----------------------------------

	inline T& operator()(int i, int j);
	inline const T& operator()(int i, int j) const;
	inline Vector<3, T>& operator[](int j);
	inline const Vector<3, T>& operator[](int j) const;

// --------------------------------- Operators ---------------------------------


// --------------------------------- Functions ---------------------------------

	inline float Determinant() const;
	inline Matrix<3, 3, T> Inverse() const;

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
inline Matrix<3, 3, T> operator*(const Matrix<3, 3, T>& mat1, const Matrix<3, 3, T>& mat2);

template<typename T>
inline Vector<3, T> operator*(const Matrix<3, 3, T>& mat, const Vector<3, T>& vec);

// -----------------------------------------------------------------------------
// ------------------------------ Implementations ------------------------------
// -----------------------------------------------------------------------------

// -------------------------------- Constructors -------------------------------

template<typename T>
inline Matrix<3, 3, T>::Matrix() = default;

template<typename T>
inline Matrix<3, 3, T>::Matrix(T n00, T n01, T n02, T n10, T n11, T n12, T n20,
	T n21, T n22) {
	data[0][0] = n00; data[0][1] = n10; data[0][2] = n20;
	data[1][0] = n01; data[1][1] = n11; data[1][2] = n21;
	data[2][0] = n02; data[2][1] = n12; data[2][2] = n22;
}

template<typename T>
inline Matrix<3, 3, T>::Matrix(const Vector<3, T>& vec1,
	const Vector<3, T>& vec2, const Vector<3, T>& vec3) {
	data[0][0] = vec1.x; data[0][1] = vec1.y; data[0][2] = vec1.z;
	data[1][0] = vec2.x; data[1][1] = vec2.y; data[1][2] = vec2.z;
	data[2][0] = vec3.x; data[2][1] = vec3.y; data[2][2] = vec3.z;
}

// ----------------------------------- Access ----------------------------------

template<typename T>
inline T& Matrix<3, 3, T>::operator()(int i, int j) {
	return data[j][i];
}

template<typename T>
inline const T& Matrix<3, 3, T>::operator()(int i, int j) const {
	return data[j][i];
}

template<typename T>
inline Vector<3, T>& Matrix<3, 3, T>::operator[](int j) {
	return *reinterpret_cast<Vector<3, T>*>(data[j]);
}

template<typename T>
inline const Vector<3, T>& Matrix<3, 3, T>::operator[](int j) const {
	return *reinterpret_cast<const Vector<3, T>*>(data[j]);
}

// --------------------------------- Operators ---------------------------------


// --------------------------------- Functions ---------------------------------

template<typename T>
inline float JMath::Matrix<3, 3, T>::Determinant() const {
	return data[0, 0] * (data[1, 1] * data[2, 2] - data[2, 1] * data[1, 2]) +
	       data[1, 0] * (data[2, 1] * data[0, 2] - data[0, 1] * data[2, 2]) +
	       data[2, 0] * (data[0, 1] * data[1, 2] - data[1, 1] * data[0, 2]);
}

template<typename T>
inline Matrix<3, 3, T> JMath::Matrix<3, 3, T>::Inverse() const {
	const Vector<3, T>& a = this->operator[](0);
	const Vector<3, T>& b = this->operator[](1);
	const Vector<3, T>& c = this->operator[](2);

	Vector<3, T> r0 = Dot(b, c);
	Vector<3, T> r1 = Dot(c, a);
	Vector<3, T> r2 = Dot(a, b);

	float invDet = 1.0f / Dot(r2, c);

	return Matrix<3, 3, T>(r0.x * invDet, r0.y * invDet, r0.z * invDet,
	                       r1.x * invDet, r1.y * invDet, r1.z * invDet,
	                       r2.x * invDet, r2.y * invDet, r2.z * invDet);
}

// ----------------------------- External Operators ----------------------------

template<typename T>
inline Matrix<3, 3, T> operator*(const Matrix<3, 3, T>& mat1,
	const Matrix<3, 3, T>& mat2) {
	return Matrix<3, 3, T>(
	mat1(0, 0) * mat2(0, 0) + mat1(0, 1) * mat2(1, 0) + mat1(0, 2) * mat2(2, 0),
	mat1(0, 0) * mat2(0, 1) + mat1(0, 1) * mat2(1, 1) + mat1(0, 2) * mat2(2, 1),
	mat1(0, 0) * mat2(0, 2) + mat1(0, 1) * mat2(1, 2) + mat1(0, 2) * mat2(2, 2),
	mat1(1, 0) * mat2(0, 0) + mat1(1, 1) * mat2(1, 0) + mat1(1, 2) * mat2(2, 0),
	mat1(1, 0) * mat2(0, 1) + mat1(1, 1) * mat2(1, 1) + mat1(1, 2) * mat2(2, 1),
	mat1(1, 0) * mat2(0, 2) + mat1(1, 1) * mat2(1, 2) + mat1(1, 2) * mat2(2, 2),
	mat1(2, 0) * mat2(0, 0) + mat1(2, 1) * mat2(1, 0) + mat1(2, 2) * mat2(2, 0),
	mat1(2, 0) * mat2(0, 1) + mat1(2, 1) * mat2(1, 1) + mat1(2, 2) * mat2(2, 1),
	mat1(2, 0) * mat2(0, 2) + mat1(2, 1) * mat2(1, 2) + mat1(2, 2) * mat2(2, 2)
	);
}

template<typename T>
inline Vector<3, T> operator*(const Matrix<3, 3, T>& mat,
	const Vector<3, T>& vec) {
	return Vector<3, T>(
		mat(0, 0) * vec.x + mat(0, 1) * vec.y + mat(0, 2) * vec.z,
		mat(1, 0) * vec.x + mat(1, 1) * vec.y + mat(1, 2) * vec.z,
		mat(2, 0) * vec.x + mat(2, 1) * vec.y + mat(2, 2) * vec.z);
}

} // namespace JMath
