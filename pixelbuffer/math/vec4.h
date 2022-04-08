/**
 * @file vec4.h
 * @brief Vector4 rt::vec4_t<T>
 * @see https://github.com/rktrlng/pixelbuffer
 */

#ifndef VEC4_H
#define VEC4_H

#include <ostream>

#include <pixelbuffer/math/vec3.h>

namespace rt {

// vec4 definition
template <class T>
class vec4_t {
public:
	union { T x, r, h, i; };
	union { T y, g, s, j; };
	union { T z, b, v, l; };
	union { T w, a, n, m; };

	vec4_t<T>() : x(static_cast<T>(0)), y(static_cast<T>(0)), z(static_cast<T>(0)), w(static_cast<T>(1)) {}
	vec4_t<T>(T n) : x(n), y(n), z(n), w(n) {}
	vec4_t<T>(T x, T y, T z = static_cast<T>(0), T w = static_cast<T>(1)) : x(x), y(y), z(z), w(w) {}
	vec4_t<T>(const vec3_t<T>& v, T w = static_cast<T>(1)) : x(v.x), y(v.y), z(v.z), w(w) {}
	vec4_t<T>(const vec4_t<T>& v) : x(v.x), y(v.y), z(v.z), w(v.w) {}

	vec4_t<T>  operator+ (const vec4_t<T>& rhs) const { return vec4_t<T>(x+rhs.x, y+rhs.y, z+rhs.z, w+rhs.w); }
	vec4_t<T>& operator+=(const vec4_t<T>& rhs) { *this = *this + rhs; return *this; }
	vec4_t<T>  operator- (const vec4_t<T>& rhs) const { return vec4_t<T>(x-rhs.x, y-rhs.y, z-rhs.z, w-rhs.w); }
	vec4_t<T>& operator-=(const vec4_t<T>& rhs) { *this = *this - rhs; return *this; }
	vec4_t<T>  operator* (const vec4_t<T>& rhs) const { return vec4_t<T>(x*rhs.x, y*rhs.y, z*rhs.z, w*rhs.w); }
	vec4_t<T>& operator*=(const vec4_t<T>& rhs) { *this = *this * rhs; return *this; }
	vec4_t<T>  operator/ (const vec4_t<T>& rhs) const { return vec4_t<T>(x/rhs.x, y/rhs.y, z/rhs.z, w/rhs.w); }
	vec4_t<T>& operator/=(const vec4_t<T>& rhs) { *this = *this / rhs; return *this; }

	vec4_t<T>  operator+ (T rhs) const { return vec4_t<T>(x+rhs, y+rhs, z+rhs, w+rhs); }
	vec4_t<T>& operator+=(T rhs) { *this = *this + rhs; return *this; }
	vec4_t<T>  operator- (T rhs) const { return vec4_t<T>(x-rhs, y-rhs, z-rhs, w-rhs); }
	vec4_t<T>& operator-=(T rhs) { *this = *this - rhs; return *this; }
	vec4_t<T>  operator* (T rhs) const { return vec4_t<T>(x*rhs, y*rhs, z*rhs, w*rhs); }
	vec4_t<T>& operator*=(T rhs) { *this = *this * rhs; return *this; }
	vec4_t<T>  operator/ (T rhs) const { return vec4_t<T>(x/rhs, y/rhs, z/rhs, w/rhs); }
	vec4_t<T>& operator/=(T rhs) { *this = *this / rhs; return *this; }

	bool operator==(const vec4_t<T>& rhs) const { return (x==rhs.x && y==rhs.y && z==rhs.z && w==rhs.w); }
	bool operator!=(const vec4_t<T>& rhs) const { return !(*this == rhs); }

	bool operator< (const vec4_t<T>& rhs) const { return (this->magSQ() < rhs.magSQ()); }
	bool operator> (const vec4_t<T>& rhs) const { return rhs < *this; }
	bool operator<=(const vec4_t<T>& rhs) const { return (*this < rhs) || (this->magSQ() == rhs.magSQ()); }
	bool operator>=(const vec4_t<T>& rhs) const { return (*this > rhs) || (this->magSQ() == rhs.magSQ()); }

	T& operator[](size_t index) {
		index %= 4;
		if (index == 0) { return x; }
		if (index == 1) { return y; }
		if (index == 2) { return z; }
		if (index == 3) { return w; }
		return x;
	}

	T magSQ() const { return ((x*x) + (y*y) + (z*z) + (w*w)); }
	T mag() const { return sqrt(magSQ()); }
	const vec4_t<T>& mag(T m) { this->normalize(); *this *= m; return *this; }

	static vec4_t<T> lerp(vec4_t<T> a, vec4_t<T> b, T t) { return a + (b-a) * t; }
	static vec4_t<T> lerp_quadratic(vec4_t<T> a, vec4_t<T> b, vec4_t<T> c, T t) {
		vec4_t<T> A = lerp(a, b, t);
		vec4_t<T> B = lerp(b, c, t);
		return lerp(A, B, t);
	}
	static vec4_t<T> lerp_cubic(vec4_t<T> a, vec4_t<T> b, vec4_t<T> c, vec4_t<T> d, T t) {
		vec4_t<T> A = lerp_quadratic(a, b, c, t);
		vec4_t<T> B = lerp_quadratic(b, c, d, t);
		return lerp(A, B, t);
	}

	friend std::ostream& operator<<(std::ostream& os, const vec4_t<T>& obj) {
		return os << "(" << obj.x << ", " << obj.y << ", " << obj.z << ", " << obj.w << ")";
	}
};

// typedefs
typedef vec4_t<float>  vec4f;
typedef vec4_t<double> vec4d;
typedef vec4f          vec4;


} // namespace rt

#endif // VEC4_H
