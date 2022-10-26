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

int matmulMV()
{
	// 90 deg rotation counterclockwise
	rt::mat2 m;
	m[0][0] = 0;
	m[0][1] = -1;
	m[1][0] = 1;
	m[1][1] = 0;

	rt::vec2 v(4,3);
	rt::vec2 res = m * v;

	std::cout << m << std::endl;
	std::cout << v << std::endl;
	std::cout << res << std::endl;

	assert(res.x == -3);
	assert(res.y == 4);

    return 1;
}


int main(void)
{
	srand(time(nullptr));

	rt::run_unit_test("create_mat2", create_mat2);
	rt::run_unit_test("matmulMV", matmulMV);
	std::cout << "## finished ##" << std::endl;

	return 0;
}
