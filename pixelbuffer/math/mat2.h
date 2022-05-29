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


// ###############################################
// # typedefs                                    #
// ############################################### 
typedef mat2_t<float>  mat2f;
typedef mat2_t<double> mat2d;
typedef mat2f          mat2;


} // namespace rt

#endif // MAT2_H
