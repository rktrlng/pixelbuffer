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

#include <ostream>
#include <cmath>

namespace pb {

// vec2 definition
template <class T>
class vec2_t {
public:
	union { T x, u, i, s, p; };
	union { T y, v, j, t, q; };

	vec2_t<T>() : x(static_cast<T>(0)), y(static_cast<T>(0)) {}
	vec2_t<T>(T n) : x(n), y(n) {}
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
	inline bool operator<=(const vec2_t<T>& rhs) const { return (*this < rhs) || (this->magSQ() == rhs.magSQ()); }
	inline bool operator>=(const vec2_t<T>& rhs) const { return (*this > rhs) || (this->magSQ() == rhs.magSQ()); }

	inline T& operator[](size_t index) { return index%2 ? y : x; }

	inline T dot(const vec2_t<T>& b) const { return ((x*b.x) + (y*b.y)); }
	inline static T dot(const vec2_t<T>& a, const vec2_t<T>& b) { return ((a.x*b.x) + (a.y*b.y)); }

	inline T magSQ() const { return ((x*x) + (y*y)); }
	inline T mag() const { return sqrt(magSQ()); }
	inline const vec2_t<T>& mag(T m) { this->normalize(); *this *= m; return *this; }

	inline T distance(const vec2_t<T>& b) const { vec2_t<T> d(b.x-x, b.y-y); return d.mag(); }
	inline static T distance(const vec2_t<T>& a, const vec2_t<T>& b) { vec2_t<T> d=b-a; return d.mag(); }

	inline const vec2_t<T>& normalize() { *this /= mag(); return *this; }
	inline vec2_t<T> normalized() const { return vec2_t<T>(*this / mag()); }

	inline T angle() const { return atan2(y, x); }
	inline const vec2_t<T>& angle(T a) { T m = mag(); x = cos(a) * m; y = sin(a) * m; return *this; }
	inline const vec2_t<T>& rotate(T a) { angle(angle() + a); return *this; }

	inline static vec2_t<T> fromAngle(T a) { return vec2_t<T>(cos(a), sin(a)); }
	inline static vec2_t<T> random() { return vec2_t<T>::fromAngle((rand()%628318)/100000.0); }

	inline static vec2_t<T> lerp(vec2_t<T> a, vec2_t<T> b, vec2_t<T> t) { return a + (b-a) * t; }
	inline static vec2_t<T> bezier_cubic(vec2_t<T> p0, vec2_t<T> p1, vec2_t<T> p2, vec2_t<T> p3, float t) {
		float x =
			pow(1 - t, 3) * p0.x +
			3 * pow(1 - t, 2) * p1.x +
			3 * pow(1 - t, 2) * pow(t, 2) * p2.x +
			pow(t, 3) * p3.x;
		float y =
			pow(1 - t, 3) * p0.y +
			3 * pow(1 - t, 2) * p1.y +
			3 * pow(1 - t, 2) * pow(t, 2) * p2.y +
			pow(t, 3) * p3.x;
		return pb::vec2_t<T>(x, y);
	}

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


} // namespace pb

#endif // VEC2_H
