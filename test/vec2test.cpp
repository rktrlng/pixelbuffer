#include <iostream>
#include <assert.h>

#include <pixelbuffer/vec2.h>

const double DEGREES = 180.0 / M_PI;
const double RADIANS = M_PI / 180.0;

int main(void)
{
	srand(time(nullptr));
	pb::vec2 v0 = pb::vec2(1, 1);
	v0 *= 2;
	v0 += pb::vec2(2, 1);
	pb::vec2 v(v0);

	assert(v0 == pb::vec2(4, 3));
	assert(v == v0);
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
	vec[0] = 5;
	vec[1] = 7;
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
