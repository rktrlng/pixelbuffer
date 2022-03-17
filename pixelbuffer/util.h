/**
 * @file util.h
 *
 * @brief collection of helper functions
 *
 * Copyright 2015-2022 @rktrlng
 * https://github.com/rktrlng/pixelbuffer
 */

#ifndef UTIL_H_
#define UTIL_H_

#define  _USE_MATH_DEFINES
#include <cmath>
#include <iostream>
#include <chrono>

namespace rt {

/**
 * @brief returns the low byte of a word
 * @param wrd The word we need the low byte from
 * @return the low byte of the word
 */
inline uint8_t low_byte(uint16_t wrd)
{
	return (uint8_t) (wrd & 0xFF);
}

/**
 * @brief returns the high byte of a word
 * @param wrd The word we need the high byte from
 * @return the high byte of the word
 */
inline uint8_t high_byte(uint16_t wrd)
{
	return (uint8_t) (wrd >> 8);
}

/**
 * @brief returns a word made of two bytes
 * @param high The high byte for the word
 * @param low The low byte for the word
 * @return the word
 */
inline uint16_t make_word(uint8_t high, uint8_t low)
{
	return (high << 8) | low;
}

/**
 * @brief maps a value from 1 range to another
 * usage example: int val = map(973, 0, 1023, 0, 255); // returns: 242
 * @param x The value we need to map
 * @param in_min  The low range of the input value
 * @param in_max  The upper range of the input value
 * @param out_min The low range of the output value
 * @param out_max The upper range of the output value
 * @return double the value
 */
inline double map(double x, double imin, double imax, double omin, double omax)
{
	return (x - imin) * (omax - omin) / (imax - imin) + omin;
}

/**
 * @brief Linear interpolation between two values.
 * Interpolates between the values a and b by the interpolant t.
 * @param a first value
 * @param b second value
 * @param t interpolant t
 * @return interpolated value
 */
inline double lerp(double a, double b, double t)
{
	return a + (b-a) * t;
}

/**
 * @brief Inversed Linear interpolation between two values.
 * @param a first value
 * @param b second value
 * @param v interpolated value
 * @return interpolant
 */
inline double ilerp(double a, double b, double v)
{
	return (v-a) / (b-a);
}

/**
 * @brief constrains a value between a range
 * @param value The value we need to constrain
 * @param min  The low range of the input value
 * @param max  The upper range of the input value
 * @return double value
 */
inline double constrain(double value, double min, double max)
{
	if (value < min) { value = min; }
	if (value > max) { value = max; }
	return value;
}

/**
 * @brief gets the index of a 1D array in a 2D grid
 * @param x x-position in grid
 * @param y y-position in grid
 * @param cols the width of the 2x2 grid
 * @return size_t index of element in array
 */
inline size_t index(int x, int y, int cols)
{
	return (y*cols)+x;
}

/**
 * @brief random uniformly distributed float
 * @return random float between 0.0f - 1.0f
 */
inline float rand_float(float a = 0.0f, float b = 1.0f)
{
	return (float) rand() / (float) RAND_MAX * (b - a) + a;
}

/**
 * @brief random uniformly distributed double
 * @return random double between 0.0 - 1.0
 */
inline double rand_double(double a = 0.0, double b = 1.0)
{
	return (double) rand() / (double) RAND_MAX * (b - a) + a;
}

/**
 * @brief random normally distributed float (box-muller transform)
 * https://en.wikipedia.org/wiki/Box%E2%80%93Muller_transform
 * @return random float between 0.0 - 1.0
 */
inline float rand_bm()
{
	const float RANGE = 3.6f;
	float u = 0.0f;
	float v = 0.0f;
	while (u == 0.0f) u = rand_float();
	while (v == 0.0f) v = rand_float();
	float n = sqrt(-2.0f * logf(u)) * cosf(2.0f * M_PI * v);
	while (n < -RANGE || n > RANGE) n = rand_bm();
	n = map(n, -RANGE, RANGE, 0.0f, 1.0f);
	return n;
}

/**
 * @brief run a unit test (function)
 * @param name name of the test
 * @param func function pointer, returns an int (pass/fail)
 * @return int 0 = fail (or assert Aborts), 1 = pass (default)
 */
inline int run_unit_test(const char* name, int (*func)())
{
	int r = func();
	if (r) {
		std::cout << "=> test passed: " << name << std::endl;
	} else {
		std::cout << "### test failed: " << name << std::endl;
	}
	return r;
}


struct AppTimer
{
	std::chrono::time_point<std::chrono::high_resolution_clock> start, end;
	std::chrono::duration<double> duration;

	AppTimer() {
		start = std::chrono::high_resolution_clock::now();
	}

	~AppTimer() {
		end = std::chrono::high_resolution_clock::now();
		duration = end - start;
		double ms = duration.count() * 1000;
		std:: cout << "Timer took: " << ms << "ms" << std::endl;
	}
};


} // namespace rt

#endif // UTIL_H_
