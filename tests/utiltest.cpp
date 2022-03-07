#include <iostream>
#include <cassert>

#include <pixelbuffer/util.h>
#include <pixelbuffer/math/vec2.h>

int test_words()
{
	uint16_t word = 0xABCD;
	uint8_t high = rt::high_byte(word);
	uint8_t low = rt::low_byte(word);

	assert(high == 0xAB);
	assert(low == 0xCD);

	high = 0x7A;
	low = 0x42;

	word = rt::make_word(high, low);
	assert(word == 0x7A42);

    return 1;
}

int test_map()
{
	int val = rt::map(973, 0, 1023, 0, 255); // returns: 242
	assert(val == 242);

	return 1;
}

int test_constrain()
{
	int val = rt::constrain(12, 42, 48);
	assert(val == 42);

	val = rt::constrain(56, 42, 48);
	assert(val == 48);

	val = rt::constrain(45, 42, 48);
	assert(val == 45);

	return 1;
}

int test_field_index()
{
	int index = rt::index(3, 2, 5);
	assert(index == 13);

	return 1;
}

int test_rand_float()
{
	for (size_t i = 0; i < 100; i++) {
		float r = rt::rand_float();
		assert(r >= 0.0f);
		assert(r <= 1.0f);
	}

	return 1;
}

int test_rand_float_args()
{
	for (size_t i = 0; i < 100; i++) {
		float r = rt::rand_float(0.25f, 0.75f);
		assert(r >= 0.25f);
		assert(r <= 0.75f);
	}

	return 1;
}

int test_rand_double()
{
	for (size_t i = 0; i < 100; i++) {
		double r = rt::rand_double();
		assert(r >= 0.0);
		assert(r <= 1.0);
	}

	return 1;
}

int test_rand_double_args()
{
	for (size_t i = 0; i < 100; i++) {
		double r = rt::rand_double(0.25, 0.75);
		assert(r >= 0.25);
		assert(r <= 0.75);
	}

	return 1;
}

int test_rand_bm()
{
	for (size_t i = 0; i < 100; i++) {
		float r = rt::rand_bm();
		assert(r >= 0.0f);
		assert(r <= 1.0f);
	}

	return 1;
}

int test_deg_rad()
{
	assert(DEG_TO_RAD * 180 > 3.14158);
	assert(DEG_TO_RAD * 180 < 3.142);
	assert(RAD_TO_DEG * M_PI > 179);
	assert(RAD_TO_DEG * M_PI < 181);

	return 1;
}

int test_lerp()
{
	float l;
	l = rt::lerp(2, 5, 0.0f);
	assert(l == 2.0f);
	l = rt::lerp(2, 5, 0.4f);
	assert(l == 3.2f);
	l = rt::lerp(2, 5, 0.8f);
	assert(l == 4.4f);
	l = rt::lerp(2, 5, 1.0f);
	assert(l == 5.0f);

	// rt::vec2f v2 = rt::vec2();
	// v2 = rt::vec2f::lerp(rt::vec2f(-4, 3), rt::vec2f(4, 3), 0.75f);
	// std::cout << v2 << std::endl;

	return 1;
}

int main(void)
{
	srand(time(nullptr));

	rt::run_unit_test("test_words", test_words);
	rt::run_unit_test("test_map", test_map);
	rt::run_unit_test("test_constrain", test_constrain);
	rt::run_unit_test("test_field_index", test_field_index);
	rt::run_unit_test("test_rand_float", test_rand_float);
	rt::run_unit_test("test_rand_float_args", test_rand_float_args);
	rt::run_unit_test("test_rand_double", test_rand_double);
	rt::run_unit_test("test_rand_double_args", test_rand_double_args);
	rt::run_unit_test("test_rand_bm", test_rand_bm);
	rt::run_unit_test("test_deg_rad", test_deg_rad);
	rt::run_unit_test("test_lerp", test_lerp);

	std::cout << "## finished ##" << std::endl;

	return 0;
}
