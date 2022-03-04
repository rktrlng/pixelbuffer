/**
 * @file geom.h
 *
 * @brief Geometry types
 *
 * Copyright 2015-2022 @rktrlng
 * https://github.com/rktrlng/pixelbuffer
 */

#ifndef GEOM_H
#define GEOM_H

#include <ostream>
#include <cmath>

#include <pixelbuffer/math/vec2.h>

namespace pb {

// ###############################################
// # Circle definition                           #
// ###############################################
template <class T>
class Circle_t {
public:
	T x;
	T y;
	T r;

	Circle_t<T>() : x(static_cast<T>(0)), y(static_cast<T>(0)), r(static_cast<T>(0)) {}
	Circle_t<T>(T x, T y, T r) : x(x), y(y), r(r) {}
	Circle_t<T>(vec2_t<T> p, T r) : x(p.x), y(p.y), r(r) {}

};
// implementations
template <class T>
inline std::ostream& operator<<(std::ostream& os, const Circle_t<T>& obj) { return os << "Circle pos: (" << obj.x << ", " << obj.y << ") radius: " << obj.r << ""; }

// typedefs
typedef Circle_t<float>  Circlef;
typedef Circle_t<double> Circled;
typedef Circlef          Circle;


// ###############################################
// # Rectangle definition                        #
// ###############################################
template <class T>
struct Rectangle_t {
	T x;
	T y;
	T width;
	T height;

	Rectangle_t<T>() : x(static_cast<T>(0)), y(static_cast<T>(0)), width(static_cast<T>(0)), height(static_cast<T>(0)) {}
	Rectangle_t<T>(T x, T y, T w, T h) : x(x), y(y), width(w), height(h) { }
};
// implementations
template <class T>
inline std::ostream& operator<<(std::ostream& os, const Rectangle_t<T>& obj) {
	return os << "Rectangle pos: (" << obj.x << ", " << obj.y << ") size: (" << obj.width << ", " << obj.height << ")"; 
}

// typedefs
typedef Rectangle_t<float>  Rectanglef;
typedef Rectangle_t<double> Rectangled;
typedef Rectanglef          Rectangle;


// ###############################################
// # Bezier cubic                                #
// ###############################################
template <class T>
struct BezierCubic_t {
	vec2_t<T> start;
	vec2_t<T> control_start;
	vec2_t<T> control_end;
	vec2_t<T> end;

	BezierCubic_t<T>() : start(static_cast<T>(0)), control_start(static_cast<T>(0)), control_end(static_cast<T>(0)), end(static_cast<T>(0)) {}

	vec2_t<T> point(T t) const {
		return vec2_t<T>::lerp_cubic(start, control_start, control_end, end, t);
	}
};

// typedefs
typedef BezierCubic_t<float>  BezierCubicf;
typedef BezierCubic_t<double> BezierCubicd;
typedef BezierCubicf          BezierCubic;


// ###############################################
// # Bezier Quadratic                            #
// ###############################################
template <class T>
struct BezierQuadratic_t {
	vec2_t<T> start;
	vec2_t<T> control;
	vec2_t<T> end;

	BezierQuadratic_t<T>() : start(static_cast<T>(0)), control(static_cast<T>(0)), end(static_cast<T>(0)) {}

	vec2_t<T> point(T t) const {
		return vec2_t<T>::lerp_quadratic(start, control, end, t);
	}
};

// typedefs
typedef BezierQuadratic_t<float>  BezierQuadraticf;
typedef BezierQuadratic_t<double> BezierQuadraticd;
typedef BezierQuadraticf          BezierQuadratic;


// ###############################################
// # Collisions                                  #
// ###############################################
template <class T>
inline bool point2circle(const vec2_t<T>& point, const Circle_t<T>& circle) {
	float dx = circle.x - point.x;
	float dy = circle.y - point.y;
	return (dx * dx + dy * dy) < (circle.r * circle.r);
}

template <class T>
inline bool point2rectangle(const vec2_t<T>& point, const Rectangle_t<T>& rect) {
	bool colx = point.x > rect.x && point.x < rect.x + rect.width;
	bool coly = point.y > rect.y && point.y < rect.y + rect.height;
	return colx && coly;
}

template <class T>
inline bool circle2circle(const Circle_t<T>& circle1, const Circle_t<T>& circle2) {
	T dx = circle1.x - circle2.x;
	T dy = circle1.y - circle2.y;
	T radii = circle1.radius + circle2.radius;
	return (dx * dx + dy * dy) < (radii * radii);
}

// https://yal.cc/rectangle-circle-intersection-test/
template <class T>
inline bool circle2rectangle(const Circle_t<T>& circle, const Rectangle_t<T>& rect) {
	T mx = std::max(rect.x, std::min(circle.x, rect.x + rect.width));
	T my = std::max(rect.y, std::min(circle.y, rect.y + rect.height));
	T dx = circle.x - mx;
	T dy = circle.y - my;
	return (dx * dx + dy * dy) < (circle.radius * circle.radius);
}

// AABB
template <class T>
inline bool rectangle2rectangle(const Rectangle_t<T>& rect1, const Rectangle_t<T>& rect2) {
	return (rect1.x < rect2.x + rect2.width &&
		rect1.x + rect1.width > rect2.x &&
		rect1.y < rect2.y + rect2.height &&
		rect1.y + rect1.height > rect2.y);
}


} // namespace pb

#endif // GEOM_H
