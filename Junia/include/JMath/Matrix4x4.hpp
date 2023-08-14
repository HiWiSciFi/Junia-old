#pragma once

#include "Types.hpp"
#include "Vector3.hpp"

#include <cmath>
#include <cstdint>

namespace JMath {

// -----------------------------------------------------------------------------
// -------------------------------- Declarations -------------------------------
// -----------------------------------------------------------------------------

// ------------------------------ Type Definitions -----------------------------

using Mat4 = Matrix<4, 4, float>;

#ifdef _MSC_VER
#pragma pack(push, 1)
#endif

template<typename T>
struct Matrix<4, 4, T> {

// ------------------------------------ Data -----------------------------------

private:
	T data[4][4];

// -------------------------------- Constructors -------------------------------

public:
	inline Matrix<4, 4, T>();
	inline Matrix<4, 4, T>(T n00, T n01, T n02, T n03, T n10, T n11, T n12, T n13, T n20, T n21, T n22, T n23, T n30, T n31, T n32, T n33);
	inline Matrix<4, 4, T>(const Vector<4, T>& vec1, const Vector<4, T>& vec2, const Vector<4, T>& vec3, const Vector<4, T>& vec4);

// ----------------------------------- Access ----------------------------------

	inline T& operator()(int i, int j);
	inline const T& operator()(int i, int j) const;
	inline Vector<4, T>& operator[](int j);
	inline const Vector<4, T>& operator[](int j) const;

// --------------------------------- Operators ---------------------------------


// --------------------------------- Functions ---------------------------------

	inline float Determinant() const;
	inline Matrix<4, 4, T> Inverse() const;

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
inline Matrix<4, 4, T> operator*(const Matrix<4, 4, T>& mat1, const Matrix<4, 4, T>& mat2);

template<typename T>
inline Vector<4, T> operator*(const Matrix<4, 4, T>& mat, const Vector<4, T>& vec);

// -----------------------------------------------------------------------------
// ------------------------------ Implementations ------------------------------
// -----------------------------------------------------------------------------

// -------------------------------- Constructors -------------------------------

template<typename T>
inline Matrix<4, 4, T>::Matrix() = default;

template<typename T>
inline Matrix<4, 4, T>::Matrix(T n00, T n01, T n02, T n03, T n10, T n11, T n12, T n13, T n20, T n21, T n22, T n23, T n30, T n31, T n32, T n33) {
	data[0][0] = n00; data[0][1] = n10; data[0][2] = n20; data[0][3] = n30;
	data[1][0] = n01; data[1][1] = n11; data[1][2] = n21; data[1][3] = n31;
	data[2][0] = n02; data[2][1] = n12; data[2][2] = n22; data[2][3] = n32;
	data[3][0] = n03; data[3][1] = n13; data[3][2] = n23; data[3][3] = n33;
}

template<typename T>
inline Matrix<4, 4, T>::Matrix(const Vector<4, T>& vec1,
	const Vector<4, T>& vec2, const Vector<4, T>& vec3, const Vector<4, T>& vec4) {
	data[0][0] = vec1.x; data[0][1] = vec1.y; data[0][2] = vec1.z; data[0][3] = vec1.w;
	data[1][0] = vec2.x; data[1][1] = vec2.y; data[1][2] = vec2.z; data[1][3] = vec2.w;
	data[2][0] = vec3.x; data[2][1] = vec3.y; data[2][2] = vec3.z; data[2][3] = vec3.w;
	data[3][0] = vec4.x; data[3][1] = vec4.y; data[3][2] = vec4.z; data[3][3] = vec4.w;
}

// ----------------------------------- Access ----------------------------------

template<typename T>
inline T& Matrix<4, 4, T>::operator()(int i, int j) {
	return data[j][i];
}

template<typename T>
inline const T& Matrix<4, 4, T>::operator()(int i, int j) const {
	return data[j][i];
}

template<typename T>
inline Vector<4, T>& Matrix<4, 4, T>::operator[](int j) {
	return *reinterpret_cast<Vector<4, T>*>(data[j]);
}

template<typename T>
inline const Vector<4, T>& Matrix<4, 4, T>::operator[](int j) const {
	return *reinterpret_cast<const Vector<4, T>*>(data[j]);
}

// --------------------------------- Operators ---------------------------------


// --------------------------------- Functions ---------------------------------

// TODO: determinant

template<typename T>
inline Matrix<4, 4, T> JMath::Matrix<4, 4, T>::Inverse() const {
	const Vector<3, T>& a = reinterpret_cast<const Vector<3, T>&>(data[0]);
	const Vector<3, T>& b = reinterpret_cast<const Vector<3, T>&>(data[1]);
	const Vector<3, T>& c = reinterpret_cast<const Vector<3, T>&>(data[2]);
	const Vector<3, T>& d = reinterpret_cast<const Vector<3, T>&>(data[3]);

	const float& x = data[0, 3];
	const float& y = data[1, 3];
	const float& z = data[2, 3];
	const float& w = data[3, 3];

	Vector<3, T> s = Cross(a, b);
	Vector<3, T> t = Cross(c, d);
	Vector<3, T> u = a * y - b * x;
	Vector<3, T> v = c * w - d * z;

	float invDet = 1.0f / (Dot(s, v) + Dot(t, u));
	s *= invDet;
	t *= invDet;
	u *= invDet;
	v *= invDet;

	Vector<3, T> r0 = Cross(b, v) + t * y;
	Vector<3, T> r1 = Cross(v, a) - t * x;
	Vector<3, T> r2 = Cross(d, u) + s * w;
	Vector<3, T> r3 = Cross(u, c) - s * z;

	return Matrix<4, 4, T>(r0.x, r0.y, r0.z, -Dot(b, t),
	                       r1.x, r1.y, r1.z,  Dot(a, t),
	                       r2.x, r2.y, r2.z, -Dot(d, s),
	                       r3.x, r3.y, r3.z,  Dot(c, s));
}

// ----------------------------- External Operators ----------------------------

template<typename T>
inline Matrix<4, 4, T> operator*(const Matrix<4, 4, T>& mat1,
	const Matrix<4, 4, T>& mat2) {
	return Matrix<4, 4, T>(
		mat1(0, 0) * mat2(0, 0) + mat1(0, 1) * mat2(1, 0) + mat1(0, 2) * mat2(2, 0) + mat1(0, 3) * mat2(3, 0),
		mat1(0, 0) * mat2(0, 1) + mat1(0, 1) * mat2(1, 1) + mat1(0, 2) * mat2(2, 1) + mat1(0, 3) * mat2(3, 1),
		mat1(0, 0) * mat2(0, 2) + mat1(0, 1) * mat2(1, 2) + mat1(0, 2) * mat2(2, 2) + mat1(0, 3) * mat2(3, 2),
		mat1(0, 0) * mat2(0, 3) + mat1(0, 1) * mat2(1, 3) + mat1(0, 2) * mat2(2, 3) + mat1(0, 3) * mat2(3, 3),
		mat1(1, 0) * mat2(0, 0) + mat1(1, 1) * mat2(1, 0) + mat1(1, 2) * mat2(2, 0) + mat1(1, 3) * mat2(3, 0),
		mat1(1, 0) * mat2(0, 1) + mat1(1, 1) * mat2(1, 1) + mat1(1, 2) * mat2(2, 1) + mat1(1, 3) * mat2(3, 1),
		mat1(1, 0) * mat2(0, 2) + mat1(1, 1) * mat2(1, 2) + mat1(1, 2) * mat2(2, 2) + mat1(1, 3) * mat2(3, 2),
		mat1(1, 0) * mat2(0, 3) + mat1(1, 1) * mat2(1, 3) + mat1(1, 2) * mat2(2, 3) + mat1(1, 3) * mat2(3, 3),
		mat1(2, 0) * mat2(0, 0) + mat1(2, 1) * mat2(1, 0) + mat1(2, 2) * mat2(2, 0) + mat1(2, 3) * mat2(3, 0),
		mat1(2, 0) * mat2(0, 1) + mat1(2, 1) * mat2(1, 1) + mat1(2, 2) * mat2(2, 1) + mat1(2, 3) * mat2(3, 1),
		mat1(2, 0) * mat2(0, 2) + mat1(2, 1) * mat2(1, 2) + mat1(2, 2) * mat2(2, 2) + mat1(2, 3) * mat2(3, 2),
		mat1(2, 0) * mat2(0, 3) + mat1(2, 1) * mat2(1, 3) + mat1(2, 2) * mat2(2, 3) + mat1(2, 3) * mat2(3, 3)
	);
}

template<typename T>
inline Vector<4, T> operator*(const Matrix<4, 4, T>& mat,
	const Vector<4, T>& vec) {
	return Vector<4, T>(
		mat(0, 0) * vec.x + mat(0, 1) * vec.y + mat(0, 2) * vec.z + mat(0, 3) * vec.w,
		mat(1, 0) * vec.x + mat(1, 1) * vec.y + mat(1, 2) * vec.z + mat(1, 3) * vec.w,
		mat(2, 0) * vec.x + mat(2, 1) * vec.y + mat(2, 2) * vec.z + mat(2, 3) * vec.w,
		mat(3, 0) * vec.x + mat(3, 1) * vec.y + mat(3, 2) * vec.z + mat(3, 3) * vec.w);
}

} // namespace JMath
