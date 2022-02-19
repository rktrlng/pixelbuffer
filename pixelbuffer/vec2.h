/**
 * @file vec2.h
 *
 * @brief Vector2 Template: pb::vec2_t<T>
 *
 * Copyright 2015-2022 @rktrlng
 * https://github.com/rktrlng/pixelbuffer
 */

#ifndef VEC2_H
#define VEC2_H

#include <iostream>
#include <cmath>
#include <cstdlib>

namespace pb {

// vec2 definition
template <class T>
class vec2_t {
public:
	T x = 0;
	T y = 0;

	vec2_t<T>() : x(static_cast<T>(0)), y(static_cast<T>(0)) {}
	vec2_t<T>(T x, T y) : x(x), y(y) {}
	vec2_t<T>(const vec2_t<T>& v) : x(v.x), y(v.y) {}

	inline vec2_t<T>  operator+ (const vec2_t<T>& rhs) const { return vec2_t<T>(x+rhs.x, y+rhs.y); }
	inline vec2_t<T>& operator+=(const vec2_t<T>& rhs) { *this = *this + rhs; return *this; }
	inline vec2_t<T>  operator- (const vec2_t<T>& rhs) const { return vec2_t<T>(x-rhs.x, y-rhs.y); }
	inline vec2_t<T>& operator-=(const vec2_t<T>& rhs) { *this = *this - rhs; return *this; }
	inline vec2_t<T>  operator* (const vec2_t<T>& rhs) const { return vec2_t<T>(x*rhs.x, y*rhs.y); }
	inline vec2_t<T>& operator*=(const vec2_t<T>& rhs) { *this = *this * rhs; return *this; }
	inline vec2_t<T>  operator/ (const vec2_t<T>& rhs) const { if (rhs.x != 0 && rhs.y != 0) { return vec2_t<T>(x/rhs.x, y/rhs.y); } return *this; }
	inline vec2_t<T>& operator/=(const vec2_t<T>& rhs) { if (rhs.x != 0 && rhs.y != 0) { *this = *this / rhs; } return *this; }

	inline vec2_t<T>  operator+ (T rhs) const { return vec2_t<T>(x+rhs, y+rhs); }
	inline vec2_t<T>& operator+=(T rhs) { *this = *this + rhs; return *this; }
	inline vec2_t<T>  operator- (T rhs) const { return vec2_t<T>(x-rhs, y-rhs); }
	inline vec2_t<T>& operator-=(T rhs) { *this = *this - rhs; return *this; }
	inline vec2_t<T>  operator* (T rhs) const { return vec2_t<T>(x*rhs, y*rhs); }
	inline vec2_t<T>& operator*=(T rhs) { *this = *this * rhs; return *this; }
	inline vec2_t<T>  operator/ (T rhs) const { if (rhs != 0) { return vec2_t<T>(x/rhs, y/rhs); } else { return *this; } }
	inline vec2_t<T>& operator/=(T rhs) { if (rhs != 0) { *this = *this / rhs; } return *this; }

	inline bool operator==(const vec2_t<T>& rhs) const { return (x==rhs.x && y==rhs.y); }
	inline bool operator!=(const vec2_t<T>& rhs) const { return !(*this == rhs); }

	inline bool operator< (const vec2_t<T>& rhs) const { return (this->magSQ() < rhs.magSQ()); }
	inline bool operator> (const vec2_t<T>& rhs) const { return rhs < *this; }
	inline bool operator<=(const vec2_t<T>& rhs) const { return !(*this > rhs); }
	inline bool operator>=(const vec2_t<T>& rhs) const { return !(*this < rhs); }

	inline T& operator[](size_t index) { return index == 1 ? y : x; }

	inline T magSQ() const { return ((x*x) + (y*y)); }
	inline T mag()   const { return sqrt(magSQ()); }

	inline T angle() const { return atan2(y, x); }
	inline vec2_t<T>& angle(T a) { T m = mag(); x = cos(a) * m; y = sin(a) * m; return *this; }
	inline vec2_t<T>& rotate(T a) { angle(angle() + a); return *this; }

	inline vec2_t<T>& normalize() { T m = mag(); x /= m; y /= m; return *this; }
	inline vec2_t<T> normalized() { T m = mag(); return pb::vec2_t<T>(x/m, y/m); }

	inline static vec2_t<T> fromAngle(T a) { return pb::vec2_t<T>(cos(a), sin(a)); }
	inline static vec2_t<T> random() { return vec2_t<T>().fromAngle((rand()%62832)/10000.0f); }

	inline static vec2_t<T> zero()  { return vec2_t<T>(static_cast<T>(0), static_cast<T>(0)); }
	inline static vec2_t<T> one()   { return vec2_t<T>(static_cast<T>(1), static_cast<T>(1)); }
	inline static vec2_t<T> unitx() { return vec2_t<T>(static_cast<T>(1), static_cast<T>(0)); }
	inline static vec2_t<T> unity() { return vec2_t<T>(static_cast<T>(0), static_cast<T>(1)); }
};
// implementations
template <class T>
inline std::ostream& operator<<(std::ostream& os, const vec2_t<T>& obj) { return os << "(" << obj.x << ", " << obj.y << ")"; }

// typedefs
typedef vec2_t<short>  vec2s;
typedef vec2_t<int>    vec2i;
typedef vec2_t<float>  vec2f;
typedef vec2_t<double> vec2d;
typedef vec2f          vec2;


// helper functions
// =========================================================
inline static vec2i wrap(const vec2i& pos, int cols, int rows) {
	vec2i wrapped(pos);

	if (pos.x < 0) { wrapped.x = cols-1; }
	if (pos.x > cols-1) { wrapped.x = 0; }
	if (pos.y < 0) { wrapped.y = rows-1; }
	if (pos.y > rows-1) { wrapped.y = 0; }

	return wrapped;
}

inline static vec2i clamp(const vec2i& pos, int cols, int rows) {
	vec2i clamped(pos);

	if (pos.x < 0) { clamped.x = 0; }
	if (pos.x > cols-1) { clamped.x = cols-1; }
	if (pos.y < 0) { clamped.y = 0; }
	if (pos.y > rows-1) { clamped.y = rows-1; }

	return clamped;
}

inline static int index(int x, int y, int cols) {
	return (y*cols)+x;
}

inline static int index(const vec2i& pos, int cols) {
	return index(pos.x, pos.y, cols);
}

// map(973, 0, 1023, 0, 255); // returns: 242
inline static double map(double x, double in_min, double in_max, double out_min, double out_max) {
	return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

// uniform distribution 0.0f - 1.0f
inline static float rand_float() {
	return (float) rand() / (float) RAND_MAX;
}

// normal distribution: box-muller transform 0.0f - 1.0f
// https://en.wikipedia.org/wiki/Box%E2%80%93Muller_transform
inline static float rand_bm() {
	const float PI = 3.14159265359f;
	const float RANGE = 3.6f;
	float u = 0.0f;
	float v = 0.0f;
	while (u == 0.0f) u = rand_float();
	while (v == 0.0f) v = rand_float();
	float n = sqrt(-2.0f * logf(u)) * cosf(2.0f * PI * v);
	while (n < -RANGE || n > RANGE) n = rand_bm();
	n = map(n, -RANGE, RANGE, 0.0f, 1.0f);
	return n;
}

// =========================================================


} // namespace pb

#endif // VEC2_H
