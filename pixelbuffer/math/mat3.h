/**
 * @file mat3.h
 * @brief Mat3x3 rt::mat3_t<T>
 * @see https://github.com/rktrlng/pixelbuffer
 */

#ifndef MAT3_H
#define MAT3_H

#include <ostream>

#include <pixelbuffer/math/vec3.h>

namespace rt {

// mat3 definition
template <class T>
class mat3_t {
public:
	vec3_t<T> v0;
	vec3_t<T> v1;
	vec3_t<T> v2;

	mat3_t<T>() : v0({0,0,0}), v1({0,1,0}), v2({0,0,0}) {}

	const mat3_t<T>& identity() { *this = mat3_t<T>(); return *this; }

	bool operator==(const mat3_t<T>& rhs) const { return (v0==rhs.v0 && v1==rhs.v1 && v2==rhs.v2); }
	bool operator!=(const mat3_t<T>& rhs) const { return !(*this == rhs); }

	vec3_t<T>& operator[](size_t index) {
		index %= 3;
		if (index == 0) { return v0; }
		if (index == 1) { return v1; }
		if (index == 2) { return v2; }
		return v0;
	}

	friend std::ostream& operator<<(std::ostream& os, const mat3_t<T>& obj) {
		return os << "{ " << obj.v0 << "\n  " << obj.v1 << "\n  " << obj.v2 << " }";
	}
};


// ###############################################
// # Basic Functions                             #
// ############################################### 


// ###############################################
// # typedefs                                    #
// ############################################### 
typedef mat3_t<float>  mat3f;
typedef mat3_t<double> mat3d;
typedef mat3f          mat3;


} // namespace rt

#endif // MAT3_H
