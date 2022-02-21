#include <iostream>
#include <cassert>

#include <pixelbuffer/vec2.h>
#include <pixelbuffer/util.h>

int create_vec()
{
	pb::vec2 v;
	assert(v.x == 0);
	assert(v.y == 0);

    return 1;
}

int create_vec_arg()
{
	pb::vec2 v = pb::vec2(5);
	assert(v.x == 5);
	assert(v.y == 5);

    return 1;
}

int create_vec_args()
{
	pb::vec2 v = pb::vec2(4, 3);
	assert(v.x == 4);
	assert(v.y == 3);

    return 1;
}

int create_vec_copy()
{
	pb::vec2 a = pb::vec2(4, 3);
	pb::vec2 b(a);
	assert(b.x == 4);
	assert(b.y == 3);

	// change original
	a.x = 5;
	a.y = 5;

	// current should be unchanged
	assert(b.x == 4);
	assert(b.y == 3);

    return 1;
}

int op_add_vec()
{
	pb::vec2 v = pb::vec2(2, 2);
	v = v + pb::vec2(2, 1);
	assert(v.x == 4);
	assert(v.y == 3);

    return 1;
}

int op_add_vec_eq()
{
	pb::vec2 v = pb::vec2(2, 2);
	v += pb::vec2(2, 1);
	assert(v.x == 4);
	assert(v.y == 3);

    return 1;
}

int op_minus_vec()
{
	pb::vec2 v = pb::vec2(5, 7);
	v = v - pb::vec2(1, 4);
	assert(v.x == 4);
	assert(v.y == 3);

    return 1;
}

int op_minus_vec_eq()
{
	pb::vec2 v = pb::vec2(5, 7);
	v -= pb::vec2(1, 4);
	assert(v.x == 4);
	assert(v.y == 3);

    return 1;
}

int op_mult_scalar()
{
	pb::vec2 v = pb::vec2(0.8f, 0.6f);
	v = v * 5;
	assert(v.x == 4);
	assert(v.y == 3);

    return 1;
}

int op_mult_scalar_eq()
{
	pb::vec2 v = pb::vec2(0.8f, 0.6f);
	v *= 5.0f;
	assert(v.x == 4.0f);
	assert(v.y == 3.0f);

    return 1;
}

int op_div_scalar()
{
	pb::vec2 v = pb::vec2(4, 3);
	v = v / 5;
	assert(v.x == 0.8f);
	assert(v.y == 0.6f);

	// divide by zero
	v = pb::vec2(4, 3);
	v = v / 0;
	assert(v.x == 4);
	assert(v.y == 3);

    return 1;
}

int op_div_scalar_eq()
{
	pb::vec2 v = pb::vec2(4, 3);
	v /= 5;
	assert(v.x == 0.8f);
	assert(v.y == 0.6f);

	// divide by zero
	v = pb::vec2(4, 3);
	v /= 0;
	assert(v.x == 4);
	assert(v.y == 3);

    return 1;
}

int op_vec_eq()
{
	pb::vec2 v = pb::vec2(4, 3);
	assert(v == pb::vec2(4, 3));

    return 1;
}

int op_lt_gt()
{
	pb::vec2 a = pb::vec2(4, 3);
	pb::vec2 b = pb::vec2(5, 5);
	assert(a < b);
	assert(b > a);

    return 1;
}

int op_lt_gt_eq()
{
	pb::vec2 a = pb::vec2(4, 3);
	pb::vec2 b = pb::vec2(5, 5);
	assert(a <= b);
	assert(b >= a);

	pb::vec2 c = pb::vec2(-4, 3);
	assert(a <= c);
	assert(c >= a);
	assert(a >= c);
	assert(c <= a);

	assert(b >= c);
	assert(c <= b);

    return 1;
}

int op_index()
{
	pb::vec2 v = pb::vec2(4, 3);
	float x = v[0];
	float y = v[1];
	assert(x == 4);
	assert(y == 3);

	x = v[2];
	y = v[3];
	assert(x == 4);
	assert(y == 3);

	v[4] = 5;
	v[5] = 7;
	assert(v.x == 5);
	assert(v.y == 7);

    return 1;
}

int vec_normalize()
{
	pb::vec2 v = pb::vec2(4, 3);
	v.normalize();
	
	assert(v.x == 0.8f);
	assert(v.y == 0.6f);

    return 1;
}

int vec_normalized()
{
	pb::vec2 a = pb::vec2(4, 3);
	pb::vec2 b = a.normalized();
	
	assert(a.x == 4);
	assert(a.y == 3);
	assert(b.x == 0.8f);
	assert(b.y == 0.6f);

    return 1;
}

int vec_mag()
{
	pb::vec2 a = pb::vec2(4, 3);
	
	assert(a.mag() == 5);
	assert(a.magSQ() == 25);

	pb::vec2 b = a.mag(1);
	assert(a.x == 0.8f);
	assert(a.y == 0.6f);
	assert(b.x == 0.8f);
	assert(b.y == 0.6f);

    return 1;
}

int vec_dot()
{
	pb::vec2 a = pb::vec2(2, 1);
	pb::vec2 b = pb::vec2(3, 4);

	// method
	float d = a.dot(b);

	assert(d == 10);
	assert(a.x == 2);
	assert(a.y == 1);
	assert(b.x == 3);
	assert(b.y == 4);

	// static
	d = 0;
	d = pb::vec2::dot(a, b);

	assert(d == 10);
	assert(a.x == 2);
	assert(a.y == 1);
	assert(b.x == 3);
	assert(b.y == 4);

    return 1;
}

int vec_distance()
{
	pb::vec2 a = pb::vec2(2, 1);
	pb::vec2 b = pb::vec2(2, 2);

	// method
	float d = a.distance(b);

	assert(d == 1);
	assert(a.x == 2);
	assert(a.y == 1);
	assert(b.x == 2);
	assert(b.y == 2);

	// static
	d = 0;
	d = pb::vec2::distance(a, b);

	assert(d == 1);
	assert(a.x == 2);
	assert(a.y == 1);
	assert(b.x == 2);
	assert(b.y == 2);

    return 1;
}

int vec_angle()
{
	pb::vec2 a = pb::vec2::unity(); // unity = (0, 1)

	// M_PI/2 = 1.5708f
	assert(a.angle() > 1.570f);
	assert(a.angle() < 1.571f);

	a.angle(0); // unitx = (1, 0)
	assert(a.x == 1);
	assert(a.y == 0);
	assert(a == pb::vec2::unitx());

	a.rotate(M_PI / 4);
	// (M_PI / 4) radians = 45 degrees
	assert(a.x == a.y); // (0.707107, 0.707107)
	assert(a.x > 0.707f);
	assert(a.x < 0.708f);

	pb::vec2 b = pb::vec2::fromAngle(a.angle());
	assert(b.x == b.y);
	assert(b.x > 0.707f);
	assert(b.x < 0.708f);

    return 1;
}

int vec_random()
{
	for (size_t i = 0; i < 100; i++) {
		pb::vec2 a = pb::vec2::random();
		assert(a.x >= -M_PI);
		assert(a.x <= M_PI);
		assert(a.y >= -M_PI);
		assert(a.y <= M_PI);
		assert(a.mag() > 0.999f);
		assert(a.mag() < 1.001f);
	}

    return 1;
}

int vec_static_defined()
{
	assert(pb::vec2::zero()  == pb::vec2(0, 0));
	assert(pb::vec2::one()   == pb::vec2(1, 1));
	assert(pb::vec2::unitx() == pb::vec2(1, 0));
	assert(pb::vec2::unity() == pb::vec2(0, 1));

    return 1;
}


int main(void)
{
	srand(time(nullptr));

	pb::run_unit_test("create_vec", create_vec);
	pb::run_unit_test("create_vec_arg", create_vec_arg);
	pb::run_unit_test("create_vec_args", create_vec_args);
	pb::run_unit_test("create_vec_copy", create_vec_copy);
	pb::run_unit_test("op_add_vec", op_add_vec);
	pb::run_unit_test("op_add_vec_eq", op_add_vec_eq);
	pb::run_unit_test("op_minus_vec", op_minus_vec);
	pb::run_unit_test("op_minus_vec_eq", op_minus_vec_eq);
	pb::run_unit_test("op_mult_scalar", op_mult_scalar);
	pb::run_unit_test("op_mult_scalar_eq", op_mult_scalar_eq);
	pb::run_unit_test("op_div_scalar", op_div_scalar);
	pb::run_unit_test("op_div_scalar_eq", op_div_scalar_eq);
	pb::run_unit_test("op_vec_eq", op_vec_eq);
	pb::run_unit_test("op_lt_gt", op_lt_gt);
	pb::run_unit_test("op_lt_gt_eq", op_lt_gt_eq);
	pb::run_unit_test("op_index", op_index);
	pb::run_unit_test("vec_normalize", vec_normalize);
	pb::run_unit_test("vec_normalized", vec_normalized);
	pb::run_unit_test("vec_mag", vec_mag);
	pb::run_unit_test("vec_dot", vec_dot);
	pb::run_unit_test("vec_distance", vec_distance);
	pb::run_unit_test("vec_angle", vec_angle);
	pb::run_unit_test("vec_random", vec_random);
	pb::run_unit_test("vec_static_defined", vec_static_defined);

#if 0
	const int N = 25;
	const int AMOUNT = 1000;

	std::cout << "Uniform distributed random floats:" << std::endl;
	int uvalues[N] = {0};
	for (size_t i = 0; i < AMOUNT; i++) {
		float v = pb::rand_float();
		int index = (int) (v*N);
		uvalues[index]++;
	}

	for (size_t i = 0; i < N; i++) {
		std::cout << i << ": ";
		for (int s = 0; s < uvalues[i]; s++) {
			std::cout << "*";
		}
		std::cout << std::endl;
	}

	std::cout << "Normal distributed random floats:" << std::endl;
	int nvalues[N] = {0};
	for (size_t i = 0; i < AMOUNT; i++) {
		float v = pb::rand_bm();
		int index = (int) (v*N);
		nvalues[index]++;
	}

	for (size_t i = 0; i < N; i++) {
		std::cout << i << ": ";
		for (int s = 0; s < nvalues[i]; s++) {
			std::cout << "*";
		}
		std::cout << std::endl;
	}
#endif

	std::cout << "## finished ##" << std::endl;

	return 0;
}
