/**
 * @file mat4.h
 *
 * @brief mat4_t<T>x4 Template: pb::mat4_t<T>
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

	const mat4_t<T>& identity() { *this = mat4_t<T>(); return *this; }

	inline mat4_t<T>  operator* (const mat4_t<T>& rhs) const { return matmulMM(*this, rhs); }
	inline mat4_t<T>& operator*=(const mat4_t<T>& rhs) { *this = *this * rhs; return *this; }

	inline vec4_t<T>  operator* (vec4_t<T> rhs) const { return matmulMV(*this, rhs); }

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
inline std::ostream& operator<<(std::ostream& os, const mat4_t<T>& obj) { return os << "{ " << obj.v0 << "\n  " << obj.v1 << "\n  " << obj.v2 << "\n  " << obj.v3 << " }"; }


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
			T sum = 0;
			for (size_t k = 0; k < 4; k++) {
				sum += a[i][k] * b[k][j];
			}
			result[i][j] = sum;
		}
	}
	return result;
}

// ######################## Helpers ########################
template <class T>
inline mat4_t<T> rotationZMatrix(T angle) {
	mat4_t<T> rm = mat4_t<T>();
	rm[0][0] = cos(angle);
	rm[0][1] = -sin(angle);
	rm[1][0] = sin(angle);
	rm[1][1] = cos(angle);

	// rm[0][0] = cos(angle); rm[0][1] = -sin(angle); rm[0][2] = 0.0; rm[0][3] = 0.0;
	// rm[1][0] = sin(angle); rm[1][1] = cos(angle);  rm[1][2] = 0.0; rm[1][3] = 0.0;
	// rm[2][0] = 0.0;        rm[2][1] = 0.0;         rm[2][2] = 1.0; rm[2][3] = 0.0;
	// rm[3][0] = 0.0;        rm[3][1] = 0.0;         rm[3][2] = 0.0; rm[3][3] = 1.0;
	return rm;
}

template <class T>
inline mat4_t<T> rotationYMatrix(T angle) {
	mat4_t<T> rm = mat4_t<T>();
	rm[0][0] = cos(angle);
	rm[0][2] = sin(angle);
	rm[2][0] = -sin(angle);
	rm[2][2] = cos(angle);

	// rm[0][0] = cos(angle);  rm[0][1] = 0.0; rm[0][2] = sin(angle); rm[0][3] = 0.0;
	// rm[1][0] = 0.0;         rm[1][1] = 1.0; rm[1][2] = 0.0;        rm[1][3] = 0.0;
	// rm[2][0] = -sin(angle); rm[2][1] = 0.0; rm[2][2] = cos(angle); rm[2][3] = 0.0;
	// rm[3][0] = 0.0;         rm[3][1] = 0.0; rm[3][2] = 0.0;        rm[3][3] = 1.0;
	return rm;
}

template <class T>
inline mat4_t<T> rotationXMatrix(T angle) {
	mat4_t<T> rm = mat4_t<T>();
	rm[1][1] = cos(angle);
	rm[1][2] = -sin(angle);
	rm[2][1] = sin(angle);
	rm[2][2] = cos(angle);

	// rm[0][0] = 1.0; rm[0][1] = 0.0;        rm[0][2] = 0.0;         rm[0][3] = 0.0;
	// rm[1][0] = 0.0; rm[1][1] = cos(angle); rm[1][2] = -sin(angle); rm[1][3] = 0.0;
	// rm[2][0] = 0.0; rm[2][1] = sin(angle); rm[2][2] = cos(angle);  rm[2][3] = 0.0;
	// rm[3][0] = 0.0; rm[3][1] = 0.0;        rm[3][2] = 0.0;         rm[3][3] = 1.0;
	return rm;
}

// #################### Matrices ####################
template <class T>
inline mat4_t<T> scaleMatrix(vec4_t<T> scale) {
	mat4_t<T> sm = mat4_t<T>();
	sm[0][0] = scale.x;
	sm[1][1] = scale.y;
	sm[2][2] = scale.z;

	// sm[0][0] = scale.x; sm[0][1] = 0.0;     sm[0][2] = 0.0;     sm[0][3] = 0.0;
	// sm[1][0] = 0.0;     sm[1][1] = scale.y; sm[1][2] = 0.0;     sm[1][3] = 0.0;
	// sm[2][0] = 0.0;     sm[2][1] = 0.0;     sm[2][2] = scale.z; sm[2][3] = 0.0;
	// sm[3][0] = 0.0;     sm[3][1] = 0.0;     sm[3][2] = 0.0;     sm[3][3] = 1.0;
	return sm;
}

template <class T>
inline mat4_t<T> rotationMatrix(vec4_t<T> angles) {
	mat4_t<T> rz = rotationZMatrix(angles.z);
	mat4_t<T> ry = rotationYMatrix(angles.y);
	mat4_t<T> rx = rotationXMatrix(angles.x);

	mat4_t<T> result = rz * ry * rx;

	return result;
}

template <class T>
inline mat4_t<T> translationMatrix(vec4_t<T> delta) {
	mat4_t<T> tm = mat4_t<T>();
	tm[0][3] = delta.x;
	tm[1][3] = delta.y;
	tm[2][3] = delta.z;

	// tm[0][0] = 1.0; tm[0][1] = 0.0; tm[0][2] = 0.0; tm[0][3] = delta.x;
	// tm[1][0] = 0.0; tm[1][1] = 1.0; tm[1][2] = 0.0; tm[1][3] = delta.y;
	// tm[2][0] = 0.0; tm[2][1] = 0.0; tm[2][2] = 1.0; tm[2][3] = delta.z;
	// tm[3][0] = 0.0; tm[3][1] = 0.0; tm[3][2] = 0.0; tm[3][3] = 1.0;
	return tm;
}

template <class T>
inline mat4_t<T> modelMatrix(vec4_t<T> position, vec4_t<T> rotation, vec4_t<T> scale) {
	// get corresponding matrices
	mat4_t<T> scalematrix = scaleMatrix(scale);
	mat4_t<T> rotmatrix = rotationMatrix(rotation);
	mat4_t<T> transmatrix = translationMatrix(position);

	// create modelmatrix. order is important (first scale, then rotate, finally translate).
	mat4_t<T> modelmatrix = transmatrix * rotmatrix * scalematrix;
	return modelmatrix;
}


template <class T>
inline mat4_t<T> perspectiveMatrix(T fov, T aspect, T near, T far)
{
	mat4_t<T> m;
    T RADIANS = M_PI / 180.0;
    T yScale = 1.0 / tan(RADIANS * fov / 2);
    T xScale = yScale / aspect;

	m[0][0] = xScale;
	m[1][1] = yScale;
	m[2][2] = (far + near) / (near - far);
	m[2][3] = -1;
	m[3][2] = 2*far*near / (near - far);
	m[3][3] = 0;
	return m;
}

// #################### Scale ####################
template <class T>
inline vec4_t<T> scale(vec4_t<T> origin, vec4_t<T> scale) {
	return scaleMatrix(scale) * origin;
}
template <class T>
inline vec3_t<T> scale(vec3_t<T> origin, vec3_t<T> scale) {
	vec4_t<T> v = scaleMatrix(vec4_t<T>(scale)) * vec4_t<T>(origin);
	return vec3_t<T>(v.x, v.y, v.z);
}

// #################### Rotation ####################
// Z
template <class T>
inline vec4_t<T> rotateZ(vec4_t<T> vec, T angle) {
	return rotationZMatrix(angle) * vec;
}
template <class T>
inline vec3_t<T> rotateZ(vec3_t<T> vec, T angle) {
	vec4_t<T> v = rotationZMatrix(angle) * vec4_t<T>(vec);
	return vec3_t<T>(v.x, v.y, v.z);
}

// Y
template <class T>
inline vec4_t<T> rotateY(vec4_t<T> vec, T angle) {
	return rotationYMatrix(angle) * vec;
}
template <class T>
inline vec3_t<T> rotateY(vec3_t<T> vec, T angle) {
	vec4_t<T> v = rotationYMatrix(angle) * vec4_t<T>(vec);
	return vec3_t<T>(v.x, v.y, v.z);
}

// X
template <class T>
inline vec4_t<T> rotateX(vec4_t<T> vec, T angle) {
	return rotationXMatrix(angle) * vec;
}
template <class T>
inline vec3_t<T> rotateX(vec3_t<T> vec, T angle) {
	vec4_t<T> v = rotationXMatrix(angle) * vec4_t<T>(vec);
	return vec3_t<T>(v.x, v.y, v.z);
}

// all
template <class T>
inline vec4_t<T> rotate(vec4_t<T> vec, vec4_t<T> angles) {
	vec4_t<T> ret = vec4_t<T>(vec.x, vec.y, vec.z, vec.w);
	ret = rotateZ(ret, angles.z);
	ret = rotateY(ret, angles.y);
	ret = rotateX(ret, angles.x);
	return ret;
}
template <class T>
inline vec3_t<T> rotate(vec3_t<T> vec, vec3_t<T> angles) {
	vec3_t<T> ret = vec3_t<T>(vec.x, vec.y, vec.z);
	ret = rotateZ(ret, angles.z);
	ret = rotateY(ret, angles.y);
	ret = rotateX(ret, angles.x);
	return ret;
}

// #################### Translation ####################
template <class T>
inline vec4_t<T> translate(vec4_t<T> origin, vec4_t<T> delta) {
	return translationMatrix(delta) * origin;
}
template <class T>
inline vec3_t<T> translate(vec3_t<T> origin, vec3_t<T> delta) {
	vec4_t<T> v = translationMatrix(vec4_t<T>(delta)) * vec4_t<T>(origin);
	return vec3_t<T>(v.x, v.y, v.z);
}


// typedefs
typedef mat4_t<float>  mat4f;
typedef mat4_t<double> mat4d;
typedef mat4f          mat4;


} // namespace pb

#endif // VEC2_H
