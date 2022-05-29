#include <iostream>
#include <cassert>

#include <pixelbuffer/math/mat2.h>
#include <pixelbuffer/util.h>

int create_mat2()
{
	rt::mat2 m;
	assert(m[0][0] == 1);
	assert(m[0][1] == 0);

	assert(m[1][0] == 0);
	assert(m[1][1] == 1);

	std::cout << m << std::endl;

    return 1;
}


int main(void)
{
	srand(time(nullptr));

	rt::run_unit_test("create_mat2", create_mat2);
	std::cout << "## finished ##" << std::endl;

	return 0;
}
