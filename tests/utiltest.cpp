#include <iostream>
#include <cassert>

#include <pixelbuffer/util.h>

int test_words()
{
	uint16_t word = 0xABCD;
	uint8_t high = pb::high_byte(word);
	uint8_t low = pb::low_byte(word);

	assert(high == 0xAB);
	assert(low == 0xCD);

	high = 0x7A;
	low = 0x42;

	word = pb::make_word(high, low);
	assert(word == 0x7A42);

    return 1;
}

int test_map()
{
	int val = pb::map(973, 0, 1023, 0, 255); // returns: 242
	assert(val == 242);

	return 1;
}

int test_constrain()
{
	int val = pb::constrain(12, 42, 48);
	assert(val == 42);

	val = pb::constrain(56, 42, 48);
	assert(val == 48);

	val = pb::constrain(45, 42, 48);
	assert(val == 45);

	return 1;
}

int test_field_index()
{
	int index = pb::index(3, 2, 5);
	assert(index == 13);

	return 1;
}

int test_rand_float()
{
	for (size_t i = 0; i < 100; i++) {
		float r = pb::rand_float();
		assert(r >= 0.0f);
		assert(r <= 1.0f);
	}

	return 1;
}

int test_rand_float_args()
{
	for (size_t i = 0; i < 100; i++) {
		float r = pb::rand_float(0.25f, 0.75f);
		assert(r >= 0.25f);
		assert(r <= 0.75f);
	}

	return 1;
}

int test_rand_double()
{
	for (size_t i = 0; i < 100; i++) {
		double r = pb::rand_double();
		assert(r >= 0.0);
		assert(r <= 1.0);
	}

	return 1;
}

int test_rand_double_args()
{
	for (size_t i = 0; i < 100; i++) {
		double r = pb::rand_double(0.25, 0.75);
		assert(r >= 0.25);
		assert(r <= 0.75);
	}

	return 1;
}

int test_rand_bm()
{
	for (size_t i = 0; i < 100; i++) {
		float r = pb::rand_bm();
		assert(r >= 0.0f);
		assert(r <= 1.0f);
	}

	return 1;
}

int test_deg_rad()
{
	assert(pb::RADIANS * 180 > 3.14158);
	assert(pb::RADIANS * 180 < 3.14160);
	assert(pb::DEGREES * M_PI > 179);
	assert(pb::DEGREES * M_PI < 181);

	return 1;
}

int main(void)
{
	srand(time(nullptr));

	pb::run_unit_test("test_words", test_words);
	pb::run_unit_test("test_map", test_map);
	pb::run_unit_test("test_constrain", test_constrain);
	pb::run_unit_test("test_field_index", test_field_index);
	pb::run_unit_test("test_rand_float", test_rand_float);
	pb::run_unit_test("test_rand_float_args", test_rand_float_args);
	pb::run_unit_test("test_rand_double", test_rand_double);
	pb::run_unit_test("test_rand_double_args", test_rand_double_args);
	pb::run_unit_test("test_rand_bm", test_rand_bm);
	pb::run_unit_test("test_deg_rad", test_deg_rad);

	std::cout << "## finished ##" << std::endl;

	return 0;
}
