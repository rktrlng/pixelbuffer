/**
 * @file mat2.h
 * @brief Mat2x2 rt::mat2_t<T>
 * @see https://github.com/rktrlng/pixelbuffer
 */

#ifndef MAT2_H
#define MAT2_H

#include <ostream>

#include <pixelbuffer/math/vec2.h>

namespace rt {

// mat2 definition
template <class T>
class mat2_t {
public:
	vec2_t<T> v0;
	vec2_t<T> v1;

	mat2_t<T>() : v0({1,0}), v1({0,1}) {}

	const mat2_t<T>& identity() { *this = mat2_t<T>(); return *this; }

	mat2_t<T>  operator* (const mat2_t<T>& rhs) const { return matmulMM(*this, rhs); }
	mat2_t<T>& operator*=(const mat2_t<T>& rhs) { *this = *this * rhs; return *this; }

	vec2_t<T>  operator* (const vec2_t<T>& rhs) const { return matmulMV(*this, rhs); }

	bool operator==(const mat2_t<T>& rhs) const { return (v0==rhs.v0 && v1==rhs.v1); }
	bool operator!=(const mat2_t<T>& rhs) const { return !(*this == rhs); }

	vec2_t<T>& operator[](size_t index) {
		index %= 2;
		if (index == 0) { return v0; }
		if (index == 1) { return v1; }
		return v0;
	}

	friend std::ostream& operator<<(std::ostream& os, const mat2_t<T>& obj) {
		return os << "{ " << obj.v0 << "\n  " << obj.v1 <<  " }";
	}
};


// ###############################################
// # Basic Functions                             #
// ############################################### 
template <class T>
inline vec2_t<T> matmulMV(mat2_t<T> m, const vec2_t<T>& v) {
	vec2_t<T> result = vec2_t<T>();
	result.x = (m[0][0] * v.x) + (m[0][1] * v.y);
	result.y = (m[1][0] * v.x) + (m[1][1] * v.y);
	return result;
}

template <class T>
inline mat2_t<T> matmulMM(mat2_t<T> a, mat2_t<T> b) {
	mat2_t<T> result = mat2_t<T>();
	for (size_t i = 0; i < 2; i++) {
		for (size_t j = 0; j < 2; j++) {
			T sum = 0;
			for (size_t k = 0; k < 2; k++) {
				sum += a[i][k] * b[k][j];
			}
			result[i][j] = sum;
		}
	}
	return result;
}

// ###############################################
// # typedefs                                    #
// ############################################### 
typedef mat2_t<float>  mat2f;
typedef mat2_t<double> mat2d;
typedef mat2f          mat2;


} // namespace rt

#endif // MAT2_H
