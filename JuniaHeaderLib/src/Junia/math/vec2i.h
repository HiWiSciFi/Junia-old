#ifndef _VEC2I_H
#define _VEC2I_H

#include <cmath>

class Vec2i {
public:
	float x;
	float y;

	Vec2i() {
		x = 0.0f;
		y = 0.0f;
	}

	Vec2i(float _x, float _y) {
		x = _x;
		y = _y;
	}

	float magnitude() const { return std::sqrt(x * x + y * y); }

	// copy assignment
	Vec2i& operator=(const Vec2i& other) {
		x = other.x;
		y = other.y;
		return *this;
	}

	Vec2i& operator++() {
		x++;
		y++;
		return *this;
	}

	Vec2i& operator--() {
		x--;
		y--;
		return *this;
	}

	Vec2i& operator+=(const Vec2i& other) {
		x += other.x;
		y += other.y;
		return *this;
	}

	Vec2i& operator+=(const float other) {
		x += other;
		y += other;
		return *this;
	}

	Vec2i& operator+=(const int other) {
		x += other;
		y += other;
		return *this;
	}

	Vec2i& operator-=(const Vec2i& other) {
		x -= other.x;
		y -= other.y;
		return *this;
	}

	Vec2i& operator-=(const int other) {
		x -= other;
		y -= other;
		return *this;
	}

	friend Vec2i& operator+(Vec2i ob, const Vec2i& other) {
		ob += other;
		return ob;
	}

	friend Vec2i& operator+(Vec2i ob, const int& other) {
		ob.x += other;
		ob.y += other;
		return ob;
	}

	friend Vec2i& operator-(Vec2i ob, const Vec2i& other) {
		ob -= other;
		return ob;
	}

	friend Vec2i& operator-(Vec2i ob, const int& other) {
		ob.x -= other;
		ob.y -= other;
		return ob;
	}

	friend bool operator< (const Vec2i& lhs, const Vec2i& rhs) { return lhs.magnitude() < rhs.magnitude(); }
	friend bool operator> (const Vec2i& lhs, const Vec2i& rhs) { return rhs < lhs; }
	friend bool operator<=(const Vec2i& lhs, const Vec2i& rhs) { return !(lhs > rhs); }
	friend bool operator>=(const Vec2i& lhs, const Vec2i& rhs) { return !(lhs < rhs); }

	friend bool operator==(const Vec2i& lhs, const Vec2i& rhs) { return (lhs.x == rhs.x) && (lhs.y == rhs.y); }
	friend bool operator!=(const Vec2i& lhs, const Vec2i& rhs) { return !(lhs == rhs); }

	const int& operator[](std::size_t idx) const { return idx == 0 ? x : y; }
};

#endif // _VEC2I_H