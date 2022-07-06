/**
 * @file geom.h
 * @brief Geometry types
 * @see https://github.com/rktrlng/pixelbuffer
 */

#ifndef GEOM_H
#define GEOM_H

#define  _USE_MATH_DEFINES
#include <cmath>
#include <ostream>
#include <vector>

#include <pixelbuffer/math/vec2.h>

namespace rt {

// ###############################################
// # Line definition                             #
// ###############################################
template <class T>
class Line_t {
public:
	vec2_t<T> begin;
	vec2_t<T> end;

	Line_t<T>() : begin(vec2_t<T>::zero()), end(vec2_t<T>::unitx()) {}
	Line_t<T>(T x1, T y1, T x2, T y2) : begin(vec2_t<T>(x1, y1)), end(vec2_t<T>(x2, y2)) {}
	Line_t<T>(const vec2_t<T>& a) : begin(a), end(a + vec2_t<T>::unitx()) {}
	Line_t<T>(const vec2_t<T>& a, const vec2_t<T>& b) : begin(a), end(b) {}
	Line_t<T>(const Line_t<T>& l) : begin(l.begin), end(l.end) {}

	friend std::ostream& operator<<(std::ostream& os, const Line_t<T>& obj) { return os << "Line begin: " << obj.begin << " end: " << obj.end; }
};
// typedefs
typedef Line_t<float>  Linef;
typedef Line_t<double> Lined;
typedef Linef          Line;


// ###############################################
// # Circle definition                           #
// ###############################################
template <class T>
class Circle_t {
public:
	vec2_t<T> pos;
	T radius;

	Circle_t<T>() : pos(vec2_t<T>()), radius(static_cast<T>(1)) {}
	Circle_t<T>(T x, T y, T r = static_cast<T>(1)) : pos(vec2_t<T>(x,y)), radius(r) {}
	Circle_t<T>(const vec2_t<T>& p, T r = static_cast<T>(1)) : pos(p), radius(r) {}
	Circle_t<T>(const Circle_t<T>& c) : pos(c.pos), radius(c.radius) {}

	friend std::ostream& operator<<(std::ostream& os, const Circle_t<T>& obj) { return os << "Circle pos: " << obj.pos << " radius: " << obj.radius; }
};
// typedefs
typedef Circle_t<float>  Circlef;
typedef Circle_t<double> Circled;
typedef Circlef          Circle;


// ###############################################
// # Rectangle definition                        #
// ###############################################
template <class T>
struct Rectangle_t {
	vec2_t<T> pos;
	vec2_t<T> size;

	Rectangle_t<T>() : pos(vec2_t<T>::zero()), size(vec2_t<T>::one()) {}
	Rectangle_t<T>(T x, T y, T w, T h) : pos(vec2_t<T>(x,y)), size(vec2_t<T>(w,h)) { }
	Rectangle_t<T>(const vec2_t<T>& p) : pos(p), size(vec2_t<T>::one()) {}
	Rectangle_t<T>(const vec2_t<T>& p, const vec2_t<T>& d) : pos(p), size(d) {}
	Rectangle_t<T>(const Rectangle_t<T>& r) : pos(r.pos), size(r.size) {}

	friend std::ostream& operator<<(std::ostream& os, const Rectangle_t<T>& obj) { return os << "Rectangle pos: " << obj.pos << " size: " << obj.size; }
};
// typedefs
typedef Rectangle_t<float>  Rectanglef;
typedef Rectangle_t<double> Rectangled;
typedef Rectanglef          Rectangle;


// ###############################################
// # Bezier cubic                                #
// ###############################################
template <class T>
struct BezierCubic_t {
	vec2_t<T> begin;
	vec2_t<T> control_begin;
	vec2_t<T> control_end;
	vec2_t<T> end;

	BezierCubic_t<T>() : begin(static_cast<T>(0)), control_begin(static_cast<T>(0)), control_end(static_cast<T>(0)), end(static_cast<T>(0)) {}

	vec2_t<T> point(T t) const { return vec2_t<T>::lerp_cubic(begin, control_begin, control_end, end, t); }
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
	vec2_t<T> begin;
	vec2_t<T> control;
	vec2_t<T> end;

	BezierQuadratic_t<T>() : begin(static_cast<T>(0)), control(static_cast<T>(0)), end(static_cast<T>(0)) {}

	vec2_t<T> point(T t) const { return vec2_t<T>::lerp_quadratic(begin, control, end, t); }
};
// typedefs
typedef BezierQuadratic_t<float>  BezierQuadraticf;
typedef BezierQuadratic_t<double> BezierQuadraticd;
typedef BezierQuadraticf          BezierQuadratic;


// ###############################################
// # Vertices                                    #
// ###############################################
template <class T>
inline std::vector<rt::vec2_t<T>> vertices(const Line_t<T>& line) {
	std::vector<rt::vec2_t<T>> vertices;
	vertices.push_back(rt::vec2_t<T>(line.begin.x, line.begin.y));
	vertices.push_back(rt::vec2_t<T>(line.end.x, line.end.y));
	return vertices;
}

template <class T>
inline std::vector<rt::vec2_t<T>> vertices(const Circle_t<T>& circle, size_t amount = 32) {
	std::vector<rt::vec2_t<T>> vertices;
	T da = TWO_PI / amount;
	T angle = 0;
	for (size_t i = 0; i < amount; i++) {
		rt::vec2_t<T> vertex;
		vertex.x = cos(angle) * circle.radius;
		vertex.y = sin(angle) * circle.radius;
		vertex += circle.pos;
		angle += da;
		vertices.push_back(vertex);
	}
	return vertices;
}

template <class T>
inline std::vector<rt::vec2_t<T>> vertices(const Rectangle_t<T>& rectangle) {
	std::vector<rt::vec2_t<T>> vertices;
	vertices.push_back(rt::vec2_t<T>(rectangle.pos.x, rectangle.pos.y));
	vertices.push_back(rt::vec2_t<T>(rectangle.pos.x + rectangle.size.x, rectangle.pos.y));
	vertices.push_back(rt::vec2_t<T>(rectangle.pos.x + rectangle.size.x, rectangle.pos.y + rectangle.size.y));
	vertices.push_back(rt::vec2_t<T>(rectangle.pos.x, rectangle.pos.y + rectangle.size.y));
	return vertices;
}

// ###############################################
// # Collisions                                  #
// ###############################################
template <class T>
inline bool point2circle(const vec2_t<T>& point, const Circle_t<T>& circle) {
	float dx = circle.pos.x - point.x;
	float dy = circle.pos.y - point.y;
	return (dx * dx + dy * dy) < (circle.radius * circle.radius);
}

template <class T>
inline bool point2rectangle(const vec2_t<T>& point, const Rectangle_t<T>& rect) {
	bool colx = point.x > rect.pos.x && point.x < rect.pos.x + rect.size.x;
	bool coly = point.y > rect.pos.y && point.y < rect.pos.y + rect.size.y;
	return colx && coly;
}

template <class T>
inline bool circle2circle(const Circle_t<T>& circle1, const Circle_t<T>& circle2) {
	T dx = circle1.pos.x - circle2.pos.x;
	T dy = circle1.pos.y - circle2.pos.y;
	T radii = circle1.radius + circle2.radius;
	return (dx * dx + dy * dy) < (radii * radii);
}

// https://yal.cc/rectangle-circle-intersection-test/
template <class T>
inline bool circle2rectangle(const Circle_t<T>& circle, const Rectangle_t<T>& rect) {
	T mx = std::max(rect.pos.x, std::min(circle.pos.x, rect.pos.x + rect.size.x));
	T my = std::max(rect.pos.y, std::min(circle.pos.y, rect.pos.y + rect.size.y));
	T dx = circle.pos.x - mx;
	T dy = circle.pos.y - my;
	return (dx * dx + dy * dy) < (circle.radius * circle.radius);
}

// AABB
template <class T>
inline bool rectangle2rectangle(const Rectangle_t<T>& rect1, const Rectangle_t<T>& rect2) {
	return (rect1.pos.x < rect2.pos.x + rect2.size.x &&
		rect1.pos.x + rect1.size.x > rect2.pos.x &&
		rect1.pos.y < rect2.size.y + rect2.size.y &&
		rect1.pos.y + rect1.size.y > rect2.pos.y);
}

// https://flassari.is/2008/11/line-line-intersection-in-cplusplus/
template <class T>
inline vec2_t<T> line2line(const Line_t<T>& line1, const Line_t<T>& line2) {
	// return value
	vec2_t<T> ret;

	// Store values for easy equations-to-code conversion
	vec2_t<T> p1 = line1.begin, p2 = line1.end, p3 = line2.begin, p4 = line2.end;

	T x1 = p1.x, x2 = p2.x, x3 = p3.x, x4 = p4.x;
	T y1 = p1.y, y2 = p2.y, y3 = p3.y, y4 = p4.y;

	T d = (x1 - x2) * (y3 - y4) - (y1 - y2) * (x3 - x4);
	// If d is zero, there is no intersection
	if (d == 0) return ret;

	// Get the x and y
	T pre = (x1*y2 - y1*x2), post = (x3*y4 - y3*x4);
	T x = ( pre * (x3 - x4) - (x1 - x2) * post ) / d;
	T y = ( pre * (y3 - y4) - (y1 - y2) * post ) / d;

	// Check if the x and y coordinates are within both lines
	if ( x < std::min(x1, x2) || x > std::max(x1, x2) || x < std::min(x3, x4) || x > std::max(x3, x4) ) return ret;
	if ( y < std::min(y1, y2) || y > std::max(y1, y2) || y < std::min(y3, y4) || y > std::max(y3, y4) ) return ret;

	// We found an intersection at (x, y)
	ret.x = x;
	ret.y = y;

	return ret;
}


} // namespace rt

#endif // GEOM_H
