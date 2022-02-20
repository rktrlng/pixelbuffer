#include <iostream>
#include <string>
#include <assert.h>

#include <pixelbuffer/vec2.h>

const double DEGREES = 180.0 / M_PI;
const double RADIANS = M_PI / 180.0;

// #####################
int run_test(const std::string& name, int (*func)())
{
	int r = func();
	if (r) {
		std::cout << "test passed: " << name << std::endl;
	}
    return r;
}
// #####################

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

int main(void)
{
	srand(time(nullptr));

	run_test("create_vec", create_vec);
	run_test("create_vec_arg", create_vec_arg);
	run_test("create_vec_args", create_vec_args);
	run_test("create_vec_copy", create_vec_copy);
	run_test("op_add_vec", op_add_vec);
	run_test("op_add_vec_eq", op_add_vec_eq);
	run_test("op_minus_vec", op_minus_vec);
	run_test("op_minus_vec_eq", op_minus_vec_eq);
	run_test("op_mult_scalar", op_mult_scalar);
	run_test("op_mult_scalar_eq", op_mult_scalar_eq);
	run_test("op_div_scalar", op_div_scalar);
	run_test("op_div_scalar_eq", op_div_scalar_eq);
	run_test("op_vec_eq", op_vec_eq);
	run_test("op_lt_gt", op_lt_gt);
	run_test("op_lt_gt_eq", op_lt_gt_eq);
	run_test("op_index", op_index);
	run_test("vec_normalize", vec_normalize);
	run_test("vec_normalized", vec_normalized);
	run_test("vec_mag", vec_mag);


/*
	pb::vec2 a = pb::vec2(1, 1);
	a *= 2;
	a += pb::vec2(2, 1);
	pb::vec2 v(a);

	assert(a == pb::vec2(4, 3));
	assert(v == a);
	assert(v.mag() == 5);

	std::cout << "vec2:  " << v << std::endl;
	std::cout << "radians: " << v.angle() << std::endl;
	std::cout << "degrees: " << v.angle() * DEGREES << std::endl;
	std::cout << "mag:   " << v.mag() << std::endl;

	pb::vec2 vf = pb::vec2::fromAngle(v.angle());
	std::cout << "static vf:  " << vf << std::endl;
	assert(vf == pb::vec2(0.8, 0.6));

	pb::vec2 vec(-v.mag(), 0);
	std::cout << "vec:  " << vec << std::endl;
	assert(vec == pb::vec2(-5, 0));
	std::cout << "radians:  " << vec.angle() << std::endl;
	int degrees = vec.angle() * DEGREES;
	std::cout << "degrees:  " << degrees << std::endl;
	assert(degrees == 180);
	vec.angle(v.angle());
	std::cout << "vec:  " << vec << std::endl;
	assert(vec == pb::vec2(4, 3));
	assert(v == vec);
	std::cout << "radians:  " << vec.angle() << std::endl;
	std::cout << "degrees:  " << vec.angle() * DEGREES << std::endl;

	assert(pb::vec2::zero()  == pb::vec2(0, 0));
	std::cout << "zero():  " << pb::vec2::zero() << std::endl;
	assert(pb::vec2::one()   == pb::vec2(1, 1));
	std::cout << "one():   " << pb::vec2::one() << std::endl;
	assert(pb::vec2::unitx() == pb::vec2(1, 0));
	std::cout << "unitx(): " << pb::vec2::unitx() << std::endl;
	assert(pb::vec2::unity() == pb::vec2(0, 1));
	std::cout << "unity(): " << pb::vec2::unity() << std::endl;

	std::cout << "vec:  " << vec << std::endl;
	assert(vec[0] == 4);
	assert(vec[1] == 3);
	std::cout << "vec[0]:  " << vec[0] << std::endl;
	std::cout << "vec[1]:  " << vec[1] << std::endl;
	std::cout << "vec[2] = 5  (index%2)" << std::endl; vec[2] = 5;
	std::cout << "vec[3] = 7  (index%2)" << std::endl; vec[3] = 7;
	assert(vec == pb::vec2(5, 7));
	std::cout << "vec:  " << vec << std::endl;

	pb::vec2 n(4, 3);

	std::cout << "####" << std::endl;
	std::cout << "n:  " << n << std::endl;
	std::cout << "n.normalized:  " << n.normalized() << std::endl;
	std::cout << "n:  " << n << std::endl;
	std::cout << "n.normalize:  " << n.normalize() << std::endl;
	std::cout << "n:  " << n << std::endl;

	pb::vec2 r = pb::vec2::random();
	for (size_t i = 0; i < 10; i++) {
		r = pb::vec2::random();
		std::cout << "random:  " << r << " mag: " << r.magSQ() << " angle: " << r.angle() << " deg: " << r.angle() * 180 / 3.14159f << std::endl;
	}

	std::cout << "####" << std::endl;
	std::cout << "n:  " << n << std::endl;
	n.mag(0.5f);
	std::cout << "n:  " << n << std::endl;
	n.mag(5);
	std::cout << "n:  " << n << std::endl;

	pb::vec2 f = n-vec;
	std::cout << "f:  " << f << std::endl;
	std::cout << "f.mag:  " << f.mag() << std::endl;
	std::cout << "distance:  " << pb::vec2::distance(vec, n) << std::endl;

	std::cout << "n:  " << n << std::endl;
	std::cout << "vec:  " << vec << std::endl;
	std::cout << "n.dot(vec): " << n.dot(vec) << std::endl;
	std::cout << "dot(n, vec): " << pb::vec2::dot(n, vec) << std::endl;
*/

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
