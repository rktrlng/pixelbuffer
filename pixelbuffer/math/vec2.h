/**
 * @file vec2.h
 * @brief Vector2 rt::vec2_t<T>
 * @see https://github.com/rktrlng/pixelbuffer
 */

#ifndef VEC2_H
#define VEC2_H

#define  _USE_MATH_DEFINES
#include <cmath>
#include <ostream>

#ifndef M_PI
	#define M_PI        3.14159265358979323846264
#endif
#ifndef HALF_PI
	#define HALF_PI     1.57079632679489661923132
#endif
#ifndef TWO_PI
	#define TWO_PI      6.28318530717958647692529
#endif
#ifndef DEG_TO_RAD
	#define DEG_TO_RAD  0.01745329251994329576924
#endif
#ifndef RAD_TO_DEG
	#define RAD_TO_DEG  57.2957795130823208767982
#endif


namespace rt {

// vec2 definition
template <class T>
class vec2_t {
public:
	union { T x, u, width; };
	union { T y, v, height; };

	vec2_t<T>() : x(static_cast<T>(0)), y(static_cast<T>(0)) {}
	vec2_t<T>(T n) : x(n), y(n) {}
	vec2_t<T>(T x, T y) : x(x), y(y) {}
	vec2_t<T>(const vec2_t<T>& v) : x(v.x), y(v.y) {}

	vec2_t<T>  operator+ (const vec2_t<T>& rhs) const { return vec2_t<T>(x+rhs.x, y+rhs.y); }
	vec2_t<T>& operator+=(const vec2_t<T>& rhs) { *this = *this + rhs; return *this; }
	vec2_t<T>  operator- (const vec2_t<T>& rhs) const { return vec2_t<T>(x-rhs.x, y-rhs.y); }
	vec2_t<T>& operator-=(const vec2_t<T>& rhs) { *this = *this - rhs; return *this; }
	vec2_t<T>  operator* (const vec2_t<T>& rhs) const { return vec2_t<T>(x*rhs.x, y*rhs.y); }
	vec2_t<T>& operator*=(const vec2_t<T>& rhs) { *this = *this * rhs; return *this; }
	vec2_t<T>  operator/ (const vec2_t<T>& rhs) const { if (rhs.x != 0 && rhs.y != 0) { return vec2_t<T>(x/rhs.x, y/rhs.y); } return *this; }
	vec2_t<T>& operator/=(const vec2_t<T>& rhs) { if (rhs.x != 0 && rhs.y != 0) { *this = *this / rhs; } return *this; }

	vec2_t<T>  operator+ (T rhs) const { return vec2_t<T>(x+rhs, y+rhs); }
	vec2_t<T>& operator+=(T rhs) { *this = *this + rhs; return *this; }
	vec2_t<T>  operator- (T rhs) const { return vec2_t<T>(x-rhs, y-rhs); }
	vec2_t<T>& operator-=(T rhs) { *this = *this - rhs; return *this; }
	vec2_t<T>  operator* (T rhs) const { return vec2_t<T>(x*rhs, y*rhs); }
	vec2_t<T>& operator*=(T rhs) { *this = *this * rhs; return *this; }
	vec2_t<T>  operator/ (T rhs) const { if (rhs != 0) { return vec2_t<T>(x/rhs, y/rhs); } else { return *this; } }
	vec2_t<T>& operator/=(T rhs) { if (rhs != 0) { *this = *this / rhs; } return *this; }

	bool operator==(const vec2_t<T>& rhs) const { return (x==rhs.x && y==rhs.y); }
	bool operator!=(const vec2_t<T>& rhs) const { return !(*this == rhs); }

	bool operator< (const vec2_t<T>& rhs) const { return (this->magSQ() < rhs.magSQ()); }
	bool operator> (const vec2_t<T>& rhs) const { return rhs < *this; }
	bool operator<=(const vec2_t<T>& rhs) const { return (*this < rhs) || (this->magSQ() == rhs.magSQ()); }
	bool operator>=(const vec2_t<T>& rhs) const { return (*this > rhs) || (this->magSQ() == rhs.magSQ()); }

	T& operator[](size_t index) { return index%2 ? y : x; }

	T dot(const vec2_t<T>& b) const { return ((x*b.x) + (y*b.y)); }
	static T dot(const vec2_t<T>& a, const vec2_t<T>& b) { return ((a.x*b.x) + (a.y*b.y)); }

	T magSQ() const { return ((x*x) + (y*y)); }
	T mag() const { return sqrt(magSQ()); }
	const vec2_t<T>& mag(T m) { this->normalize(); *this *= m; return *this; }

	T distance(const vec2_t<T>& b) const { vec2_t<T> d(b.x-x, b.y-y); return d.mag(); }
	static T distance(const vec2_t<T>& a, const vec2_t<T>& b) { vec2_t<T> d=b-a; return d.mag(); }

	const vec2_t<T>& normalize() { *this /= mag(); return *this; }
	vec2_t<T> normalized() const { return vec2_t<T>(*this / mag()); }
	const vec2_t<T>& limit(T m) { if (magSQ()>m*m) { normalize(); *this *= m; } return *this; }

	T angle() const { return atan2(y, x); }
	const vec2_t<T>& angle(T a) { T m = mag(); x = cos(a) * m; y = sin(a) * m; return *this; }
	const vec2_t<T>& rotate(T a) { angle(angle() + a); return *this; }

	T angle(const vec2_t<T>& b) const { return acos((*this).dot(b) / ((*this).mag() * b.mag())); }
	static T angle(const vec2_t<T>& a, const vec2_t<T>& b) { return acos(a.dot(b) / (a.mag() * b.mag())); }

	static vec2_t<T> fromAngle(T a) { return vec2_t<T>(cos(a), sin(a)); }
	static vec2_t<T> random() { return vec2_t<T>::fromAngle((rand()%628318)/100000.0); }

	static vec2_t<T> lerp(vec2_t<T> a, vec2_t<T> b, T t) { return a + (b-a) * t; }
	static vec2_t<T> lerp_quadratic(vec2_t<T> a, vec2_t<T> b, vec2_t<T> c, T t) {
		vec2_t<T> A = lerp(a, b, t);
		vec2_t<T> B = lerp(b, c, t);
		return lerp(A, B, t);
	}
	static vec2_t<T> lerp_cubic(vec2_t<T> a, vec2_t<T> b, vec2_t<T> c, vec2_t<T> d, T t) {
		vec2_t<T> A = lerp_quadratic(a, b, c, t);
		vec2_t<T> B = lerp_quadratic(b, c, d, t);
		return lerp(A, B, t);
	}

	static vec2_t<T> zero()  { return vec2_t<T>(static_cast<T>(0), static_cast<T>(0)); }
	static vec2_t<T> one()   { return vec2_t<T>(static_cast<T>(1), static_cast<T>(1)); }
	static vec2_t<T> unitx() { return vec2_t<T>(static_cast<T>(1), static_cast<T>(0)); }
	static vec2_t<T> unity() { return vec2_t<T>(static_cast<T>(0), static_cast<T>(1)); }

	friend std::ostream& operator<<(std::ostream& os, const vec2_t<T>& obj) { return os << "(" << obj.x << ", " << obj.y << ")"; }
	friend std::istream& operator>>(std::istream& stream, vec2_t<T>& ob) { stream >> ob.x >> ob.y; return stream; }
};

// typedefs
typedef vec2_t<short>  vec2s;
typedef vec2_t<int>    vec2i;
typedef vec2_t<float>  vec2f;
typedef vec2_t<double> vec2d;
typedef vec2f          vec2;


} // namespace rt

#endif // VEC2_H
