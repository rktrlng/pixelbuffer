/**
 * @file mat4.h
 *
 * @brief Matrix4x4 Template: pb::mat4_t<T>
 *
 * Copyright 2015-2022 @rktrlng
 * https://github.com/rktrlng/pixelbuffer
 */

#ifndef MAT4_H
#define MAT4_H

#include <ostream>
#include <cmath>

#include <pixelbuffer/math/vec4.h>

namespace pb {

// mat4 definition
template <class T>
class mat4_t {
public:
	vec4_t<T> v0;
	vec4_t<T> v1;
	vec4_t<T> v2;
	vec4_t<T> v3;

	mat4_t<T>() : v0({1,0,0,0}), v1({0,1,0,0}), v2({0,0,1,0}), v3({0,0,0,1}) {}

	inline bool operator==(const mat4_t<T>& rhs) const { return (v0==rhs.v0 && v1==rhs.v1 && v2==rhs.v2 && v3==rhs.v3); }
	inline bool operator!=(const mat4_t<T>& rhs) const { return !(*this == rhs); }

	inline vec4_t<T>& operator[](size_t index) {
		index %= 4;
		if (index == 0) { return v0; }
		if (index == 1) { return v1; }
		if (index == 2) { return v2; }
		if (index == 3) { return v3; }
		return v0;
	}

};
// implementations
template <class T>
inline std::ostream& operator<<(std::ostream& os, const mat4_t<T>& obj) { return os << "" << obj.v0 << "\n" << obj.v1 << "\n" << obj.v2 << "\n" << obj.v3; }


// #################### Basic Functions ####################
template <class T>
inline vec4_t<T> matmulMV(mat4_t<T> m, vec4_t<T> v) {
    vec4_t<T> result = vec4_t<T>();
    result.x = (m[0][0] * v.x) + (m[0][1] * v.y) + (m[0][2] * v.z) + (m[0][3] * v.w);
    result.y = (m[1][0] * v.x) + (m[1][1] * v.y) + (m[1][2] * v.z) + (m[1][3] * v.w);
    result.z = (m[2][0] * v.x) + (m[2][1] * v.y) + (m[2][2] * v.z) + (m[2][3] * v.w);
    result.w = (m[3][0] * v.x) + (m[3][1] * v.y) + (m[3][2] * v.z) + (m[3][3] * v.w);
    return result;
}

template <class T>
inline mat4_t<T> matmulMM(mat4_t<T> a, mat4_t<T> b) {
    mat4_t<T> result = mat4_t<T>();
    for (size_t i = 0; i < 4; i++) {
        for (size_t j = 0; j < 4; j++) {
            double sum = 0;
            for (size_t k = 0; k < 4; k++) {
                sum += a[i][k] * b[k][j];
            }
            result[i][j] = sum;
        }
    }
    return result;
}



// typedefs
typedef mat4_t<float>  mat4f;
typedef mat4_t<double> mat4d;
typedef mat4f          mat4;


} // namespace pb

#endif // VEC2_H
