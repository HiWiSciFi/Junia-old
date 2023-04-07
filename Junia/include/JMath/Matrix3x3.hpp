#pragma once

#include "Types.hpp"
#include "Vector3.hpp"

#include <cmath>
#include <cstdint>

// TODO(HiWiSciFi): Finish implementation. [07-Apr-23]

namespace JMath {

// -----------------------------------------------------------------------------
// -------------------------------- Declarations -------------------------------
// -----------------------------------------------------------------------------

// ------------------------------ Type Definitions -----------------------------

using Mat3 = Matrix<3, 3, float>;

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

};

// ----------------------------- External Operators ----------------------------

// ----------------------------- External Functions ----------------------------

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
	data[0][0] = vec1.x; data[0][1] = vec1.x; data[0][2] = vec1.x;
	data[1][0] = vec2.y; data[1][1] = vec2.y; data[1][2] = vec2.y;
	data[2][0] = vec3.z; data[2][1] = vec3.z; data[2][2] = vec3.z;
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
inline Vector<3, T>& JMath::Matrix<3, 3, T>::operator[](int j) {
	return *reinterpret_cast<Vector<3, T>*>(data[j]);
}

template<typename T>
inline const Vector<3, T>& JMath::Matrix<3, 3, T>::operator[](int j) const {
	return *reinterpret_cast<const Vector<3, T>*>(data[j]);
}

// --------------------------------- Operators ---------------------------------

// ----------------------------- External Operators ----------------------------

// ----------------------------- External Functions ----------------------------

} // namespace JMath
