#include <iostream>
#include <cassert>

#include <pixelbuffer/math/vec3.h>
#include <pixelbuffer/math/vec4.h>
#include <pixelbuffer/util.h>

int create_vec()
{
	pb::vec4 v;
	assert(v.x == 0);
	assert(v.y == 0);
	assert(v.z == 0);
	assert(v.w == 1);
	// std::cout << v << std::endl;

	pb::vec3 v3 = pb::vec3(4, 3, 0);
	pb::vec4 v34 = pb::vec4(v3, 1);
	// std::cout << v34 << std::endl;
	assert(v34.x == 4);
	assert(v34.y == 3);
	assert(v34.z == 0);
	assert(v34.w == 1);

	pb::vec4 v4 = pb::vec4(v3);
	// std::cout << v4 << std::endl;
	assert(v4.x == 4);
	assert(v4.y == 3);
	assert(v4.z == 0);
	assert(v4.w == 1);

    return 1;
}


int main(void)
{
	srand(time(nullptr));

	pb::run_unit_test("create_vec", create_vec);

	std::cout << "## finished ##" << std::endl;

	return 0;
}
