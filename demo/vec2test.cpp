#include <iostream>
#include <assert.h>

#include <pixelbuffer/vec2.h>

const double DEGREES = 180.0 / M_PI;
const double RADIANS = M_PI / 180.0;

int main(void)
{
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

	pb::vec2 vec(0 - v.mag());
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

	std::cout << "## finished ##" << std::endl;

	return 0;
}
