#ifndef _VEC2F_H
#define _VEC2F_H

#include <cmath>

class Vec2f {
public:
	float x;
	float y;

	Vec2f() {
		x = 0.0f;
		y = 0.0f;
	}

	Vec2f(float _x, float _y) {
		x = _x;
		y = _y;
	}

	float magnitude() const { return std::sqrt(x * x + y * y); }

	// copy assignment
	Vec2f& operator=(const Vec2f& other) {
		x = other.x;
		y = other.y;
		return *this;
	}

	Vec2f& operator++() {
		x++;
		y++;
		return *this;
	}

	Vec2f& operator--() {
		x--;
		y--;
		return *this;
	}

	Vec2f& operator+=(const Vec2f& other) {
		x += other.x;
		y += other.y;
		return *this;
	}

	Vec2f& operator+=(const float other) {
		x += other;
		y += other;
		return *this;
	}

	Vec2f& operator+=(const int other) {
		x += other;
		y += other;
		return *this;
	}

	Vec2f& operator-=(const Vec2f& other) {
		x -= other.x;
		y -= other.y;
		return *this;
	}

	Vec2f& operator-=(const float other) {
		x -= other;
		y -= other;
		return *this;
	}

	Vec2f& operator-=(const int other) {
		x -= other;
		y -= other;
		return *this;
	}

	friend Vec2f& operator+(Vec2f ob, const Vec2f& other) {
		ob += other;
		return ob;
	}

	friend Vec2f& operator-(Vec2f ob, const Vec2f& other) {
		ob -= other;
		return ob;
	}

	friend bool operator< (const Vec2f& lhs, const Vec2f& rhs) { return lhs.magnitude() < rhs.magnitude(); }
	friend bool operator> (const Vec2f& lhs, const Vec2f& rhs) { return rhs < lhs; }
	friend bool operator<=(const Vec2f& lhs, const Vec2f& rhs) { return !(lhs > rhs); }
	friend bool operator>=(const Vec2f& lhs, const Vec2f& rhs) { return !(lhs < rhs); }

	friend bool operator==(const Vec2f& lhs, const Vec2f& rhs) { return (lhs.x == rhs.x) && (lhs.y == rhs.y); }
	friend bool operator!=(const Vec2f& lhs, const Vec2f& rhs) { return !(lhs == rhs); }

	const float& operator[](std::size_t idx) const { return idx == 0 ? x : y; }
};

#endif // _VEC2F_H