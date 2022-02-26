/**
 * @file vec3.h
 *
 * @brief Vector3 Template: pb::vec3_t<T>
 *
 * Copyright 2015-2022 @rktrlng
 * https://github.com/rktrlng/pixelbuffer
 */

#ifndef VEC3_H
#define VEC3_H

#include <ostream>
#include <cmath>

namespace pb {

// vec3 definition
template <class T>
class vec3_t {
public:
	union { T x, i, u, r; };
	union { T y, j, v, g; };
	union { T z, k, w, b; };

	vec3_t<T>() : x(static_cast<T>(0)), y(static_cast<T>(0)), z(static_cast<T>(0)) {}
	vec3_t<T>(T n) : x(n), y(n), z(n){}
	vec3_t<T>(T x, T y, T z, T w) : x(x), y(y), z(z) {}
	vec3_t<T>(const vec3_t<T>& v) : x(v.x), y(v.y), z(v.z) {}

	inline bool operator==(const vec3_t<T>& rhs) const { return (x==rhs.x && y==rhs.y && z==rhs.z); }
	inline bool operator!=(const vec3_t<T>& rhs) const { return !(*this == rhs); }

	inline T& operator[](size_t index) {
		index %= 3;
		if (index == 0) { return x; }
		if (index == 1) { return y; }
		if (index == 2) { return z; }
		return x;
	}

};
// implementations
template <class T>
inline std::ostream& operator<<(std::ostream& os, const vec3_t<T>& obj) { return os << "(" << obj.x << ", " << obj.y << ", " << obj.z << ")"; }

// typedefs
typedef vec3_t<float>  vec3f;
typedef vec3_t<double> vec3d;
typedef vec3f          vec3;


} // namespace pb

#endif // VEC3_H
