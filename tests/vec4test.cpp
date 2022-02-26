#include <iostream>
#include <cassert>

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

    return 1;
}


int main(void)
{
	srand(time(nullptr));

	pb::run_unit_test("create_vec", create_vec);

	std::cout << "## finished ##" << std::endl;

	return 0;
}
