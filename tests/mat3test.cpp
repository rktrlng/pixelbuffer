#include <iostream>
#include <cassert>

#include <pixelbuffer/math/mat3.h>
#include <pixelbuffer/util.h>

int create_mat3()
{
	rt::mat3 m;
	assert(m[0][0] == 0);
	assert(m[0][1] == 0);
	assert(m[0][2] == 0);

	assert(m[1][0] == 0);
	assert(m[1][1] == 1);
	assert(m[1][2] == 0);

	assert(m[2][0] == 0);
	assert(m[2][1] == 0);
	assert(m[2][2] == 0);

	std::cout << m << std::endl;

    return 1;
}


int main(void)
{
	srand(time(nullptr));

	rt::run_unit_test("create_mat3", create_mat3);
	std::cout << "## finished ##" << std::endl;

	return 0;
}
