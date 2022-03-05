/**
 * @file vec4.h
 *
 * @brief Vector4 Template: pb::vec4_t<T>
 *
 * Copyright 2015-2022 @rktrlng
 * https://github.com/rktrlng/pixelbuffer
 */

#ifndef VEC4_H
#define VEC4_H

#include <ostream>
#include <cmath>

#include <pixelbuffer/math/vec3.h>

namespace rt {

// vec4 definition
template <class T>
class vec4_t {
public:
	union { T x, i, s, r; };
	union { T y, j, t, g; };
	union { T z, k, p, b; };
	union { T w, l, q, a; };

	vec4_t<T>() : x(static_cast<T>(0)), y(static_cast<T>(0)), z(static_cast<T>(0)), w(static_cast<T>(1)) {}
	vec4_t<T>(T n) : x(n), y(n), z(n), w(n) {}
	vec4_t<T>(T x, T y, T z = static_cast<T>(0), T w = static_cast<T>(1)) : x(x), y(y), z(z), w(w) {}
	vec4_t<T>(const vec3_t<T>& v, T w = static_cast<T>(1)) : x(v.x), y(v.y), z(v.z), w(w) {}
	vec4_t<T>(const vec4_t<T>& v) : x(v.x), y(v.y), z(v.z), w(v.w) {}

	inline bool operator==(const vec4_t<T>& rhs) const { return (x==rhs.x && y==rhs.y && z==rhs.z && w==rhs.w); }
	inline bool operator!=(const vec4_t<T>& rhs) const { return !(*this == rhs); }

	inline T& operator[](size_t index) {
		index %= 4;
		if (index == 0) { return x; }
		if (index == 1) { return y; }
		if (index == 2) { return z; }
		if (index == 3) { return w; }
		return x;
	}

};
// implementations
template <class T>
inline std::ostream& operator<<(std::ostream& os, const vec4_t<T>& obj) { return os << "(" << obj.x << ", " << obj.y << ", " << obj.z << ", " << obj.w << ")"; }

// typedefs
typedef vec4_t<float>  vec4f;
typedef vec4_t<double> vec4d;
typedef vec4f          vec4;


} // namespace rt

#endif // VEC4_H
