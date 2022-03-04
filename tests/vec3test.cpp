#include <iostream>
#include <cassert>

#include <pixelbuffer/math/vec3.h>
#include <pixelbuffer/util.h>

int create_vec()
{
	pb::vec3 v;
	assert(v.x == 0);
	assert(v.y == 0);
	assert(v.z == 0);
	// std::cout << v << std::endl;

	pb::vec2 v2(4, 3);
	pb::vec3 v3(v2, 1);
	// std::cout << v3 << std::endl;
	assert(v3.x == 4);
	assert(v3.y == 3);
	assert(v3.z == 1);

	v2.limit(2);
	assert(v2.x == 1.6f);
	assert(v2.y == 1.2f);


    return 1;
}


int main(void)
{
	srand(time(nullptr));

	pb::run_unit_test("create_vec", create_vec);

	std::cout << "## finished ##" << std::endl;

	return 0;
}
