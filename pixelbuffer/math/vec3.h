/**
 * @file vec3.h
 * @brief Vector3 rt::vec3_t<T>
 * @see https://github.com/rktrlng/pixelbuffer
 */

#ifndef VEC3_H
#define VEC3_H

#include <ostream>

#include <pixelbuffer/math/vec2.h>

namespace rt {

// vec3 definition
template <class T>
class vec3_t {
public:
	union { T x, u, r; };
	union { T y, v, g; };
	union { T z, w, b; };

	vec3_t<T>() : x(static_cast<T>(0)), y(static_cast<T>(0)), z(static_cast<T>(0)) {}
	vec3_t<T>(T n) : x(n), y(n), z(n) {}
	vec3_t<T>(T x, T y, T z = static_cast<T>(0)) : x(x), y(y), z(z) {}
	vec3_t<T>(const vec2_t<T>& v, T z = static_cast<T>(0)) : x(v.x), y(v.y), z(z) {}
	vec3_t<T>(const vec3_t<T>& v) : x(v.x), y(v.y), z(v.z) {}

	vec3_t<T>  operator+ (const vec3_t<T>& rhs) const { return vec3_t<T>(x+rhs.x, y+rhs.y, z+rhs.z); }
	vec3_t<T>& operator+=(const vec3_t<T>& rhs) { *this = *this + rhs; return *this; }
	vec3_t<T>  operator- (const vec3_t<T>& rhs) const { return vec3_t<T>(x-rhs.x, y-rhs.y, z-rhs.z); }
	vec3_t<T>& operator-=(const vec3_t<T>& rhs) { *this = *this - rhs; return *this; }
	vec3_t<T>  operator* (const vec3_t<T>& rhs) const { return vec3_t<T>(x*rhs.x, y*rhs.y, z*rhs.z); }
	vec3_t<T>& operator*=(const vec3_t<T>& rhs) { *this = *this * rhs; return *this; }
	vec3_t<T>  operator/ (const vec3_t<T>& rhs) const { if (rhs.x != 0 && rhs.y != 0 && rhs.z != 0) { return vec3_t<T>(x/rhs.x, y/rhs.y, z/rhs.z); } return *this; }
	vec3_t<T>& operator/=(const vec3_t<T>& rhs) { if (rhs.x != 0 && rhs.y != 0 && rhs.z != 0) { *this = *this / rhs; } return *this; }

	vec3_t<T>  operator+ (T rhs) const { return vec3_t<T>(x+rhs, y+rhs, z+rhs); }
	vec3_t<T>& operator+=(T rhs) { *this = *this + rhs; return *this; }
	vec3_t<T>  operator- (T rhs) const { return vec3_t<T>(x-rhs, y-rhs, z-rhs); }
	vec3_t<T>& operator-=(T rhs) { *this = *this - rhs; return *this; }
	vec3_t<T>  operator* (T rhs) const { return vec3_t<T>(x*rhs, y*rhs, z*rhs); }
	vec3_t<T>& operator*=(T rhs) { *this = *this * rhs; return *this; }
	vec3_t<T>  operator/ (T rhs) const { if (rhs != 0) { return vec3_t<T>(x/rhs, y/rhs, z/rhs); } else { return *this; } }
	vec3_t<T>& operator/=(T rhs) { if (rhs != 0) { *this = *this / rhs; } return *this; }

	bool operator==(const vec3_t<T>& rhs) const { return (x==rhs.x && y==rhs.y && z==rhs.z); }
	bool operator!=(const vec3_t<T>& rhs) const { return !(*this == rhs); }

	bool operator< (const vec3_t<T>& rhs) const { return (this->magSQ() < rhs.magSQ()); }
	bool operator> (const vec3_t<T>& rhs) const { return rhs < *this; }
	bool operator<=(const vec3_t<T>& rhs) const { return (*this < rhs) || (this->magSQ() == rhs.magSQ()); }
	bool operator>=(const vec3_t<T>& rhs) const { return (*this > rhs) || (this->magSQ() == rhs.magSQ()); }

	T& operator[](size_t index) {
		index %= 3;
		if (index == 0) { return x; }
		if (index == 1) { return y; }
		if (index == 2) { return z; }
		return x;
	}

	T dot(const vec3_t<T>& b) const { return ((x*b.x) + (y*b.y) + (z*b.z)); }
	static T dot(const vec3_t<T>& a, const vec3_t<T>& b) { return ((a.x*b.x) + (a.y*b.y) + (a.z*b.z)); }

	vec3_t<T> cross(vec3_t<T> b) const {
		return vec3_t<T>((y * b.z) - (z * b.y), (z * b.x) - (x * b.z), (x * b.y) - (y * b.x));
	}
	static vec3_t<T> cross(vec3_t<T> a, vec3_t<T> b) {
		return vec3_t<T>((a.y * b.z) - (a.z * b.y), (a.z * b.x) - (a.x * b.z), (a.x * b.y) - (a.y * b.x));
	}

	T magSQ() const { return ((x*x) + (y*y) + (z*z)); }
	T mag() const { return sqrt(magSQ()); }
	const vec3_t<T>& mag(T m) { this->normalize(); *this *= m; return *this; }

	T distance(const vec3_t<T>& b) const { vec3_t<T> d(b.x-x, b.y-y, b.z-z); return d.mag(); }
	static T distance(const vec3_t<T>& a, const vec3_t<T>& b) { vec3_t<T> d=b-a; return d.mag(); }

	const vec3_t<T>& normalize() { *this /= mag(); return *this; }
	vec3_t<T> normalized() const { return vec3_t<T>(*this / mag()); }
	const vec3_t<T>& limit(T m) { if (magSQ()>m*m) { normalize(); *this *= m; } return *this;  }

	T angle(const vec3_t<T>& b) const { return acos((*this).dot(b) / ((*this).mag() * b.mag())); }
	static T angle(const vec3_t<T>& a, const vec3_t<T>& b) { return acos(a.dot(b) / (a.mag() * b.mag())); }

	static vec3_t<T> random() {
		T a = -1.0f;
		T b = 1.0f;
		T x_ = (T)rand() / (T)RAND_MAX * (b - a) + a;
		T y_ = (T)rand() / (T)RAND_MAX * (b - a) + a;
		T z_ = (T)rand() / (T)RAND_MAX * (b - a) + a;
		vec3_t<T> v = vec3_t<T>(x_, y_, z_);
		v.normalize();
		return v;
	}

	static vec3_t<T> lerp(vec3_t<T> a, vec3_t<T> b, T t) { return a + (b-a) * t; }
	static vec3_t<T> lerp_quadratic(vec3_t<T> a, vec3_t<T> b, vec3_t<T> c, T t) {
		vec3_t<T> A = lerp(a, b, t);
		vec3_t<T> B = lerp(b, c, t);
		return lerp(A, B, t);
	}
	static vec3_t<T> lerp_cubic(vec3_t<T> a, vec3_t<T> b, vec3_t<T> c, vec3_t<T> d, T t) {
		vec3_t<T> A = lerp_quadratic(a, b, c, t);
		vec3_t<T> B = lerp_quadratic(b, c, d, t);
		return lerp(A, B, t);
	}

	static vec3_t<T> zero()  { return vec3_t<T>(static_cast<T>(0), static_cast<T>(0), static_cast<T>(0)); }
	static vec3_t<T> one()   { return vec3_t<T>(static_cast<T>(1), static_cast<T>(1), static_cast<T>(1)); }
	static vec3_t<T> unitx() { return vec3_t<T>(static_cast<T>(1), static_cast<T>(0), static_cast<T>(0)); }
	static vec3_t<T> unity() { return vec3_t<T>(static_cast<T>(0), static_cast<T>(1), static_cast<T>(0)); }

	friend std::ostream& operator<<(std::ostream& os, const vec3_t<T>& obj) { return os << "(" << obj.x << ", " << obj.y << ", " << obj.z << ")"; }
};

// typedefs
typedef vec3_t<float>  vec3f;
typedef vec3_t<double> vec3d;
typedef vec3f          vec3;


} // namespace rt

#endif // VEC3_H
