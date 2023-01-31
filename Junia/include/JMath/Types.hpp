#pragma once

namespace JMath
{
	/**
	 * @brief A Vector with S dimensions
	 * @tparam T the datatype for the vector components to use
	 * @tparam S the amount of components
	*/
	template<unsigned char S, typename T> struct Vector;
	/**
	 * @brief A Matrix with C columns and R rows
	 * @tparam T the datatype for the matrix components to use
	 * @tparam C the amount of columns
	 * @tparam R the amount of rows
	*/
	template<unsigned char C, unsigned char R, typename T> struct Matrix;
	/**
	 * @brief A Quaternion
	 * @tparam T the datatype for the quaternion components to use
	*/
	template<typename T> struct Quat;
}
