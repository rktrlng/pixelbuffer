#include <iostream>
#include <cassert>

#include <pixelbuffer/math/vec3.h>
#include <pixelbuffer/util.h>

int create_vec()
{
	rt::vec3 v;
	assert(v.x == 0);
	assert(v.y == 0);
	assert(v.z == 0);
	// std::cout << v << std::endl;

	rt::vec2 v2(4, 3);
	rt::vec3 v3(v2, 1);
	// std::cout << v3 << std::endl;
	assert(v3.x == 4);
	assert(v3.y == 3);
	assert(v3.z == 1);

	v2.limit(2);
	assert(v2.x == 1.6f);
	assert(v2.y == 1.2f);


    return 1;
}

int anglewith_vec()
{
	rt::vec3 v1(0, 1, 0);
	rt::vec3 v2(0, 0, 1);

	float a = rt::vec3::angle(v1, v2);
	assert(a > 1.570f && a < 1.571f); // 90 degrees

    return 1;
}

int random_test()
{
	rt::vec3 v1 = rt::vec3::random();

	assert(v1.x <= 1 && v1.x >= -1);
	assert(v1.y <= 1 && v1.y >= -1);
	assert(v1.z <= 1 && v1.z >= -1);
	assert(v1.mag() < 1.001f);
	assert(v1.mag() > 0.999f);

    return 1;
}


int main(void)
{
	srand(time(nullptr));

	rt::run_unit_test("create_vec", create_vec);
	rt::run_unit_test("anglewith_vec", anglewith_vec);
	rt::run_unit_test("random_test", random_test);

	std::cout << "## finished ##" << std::endl;

	return 0;
}
