#include <iostream>
#include <cassert>

#include <pixelbuffer/math/mat4.h>
#include <pixelbuffer/util.h>

int create_mat4()
{
	pb::mat4 m;
	assert(m[0][0] == 1);
	assert(m[1][1] == 1);
	assert(m[2][2] == 1);
	assert(m[3][3] == 1);

	assert(m[1][0] == 0);
	assert(m[0][1] == 0);

	// std::cout << m << std::endl;

    return 1;
}

int matmulMV_test()
{
	pb::mat4 m;
	m[0][3] = 5; // x translate
	m[1][3] = 7; // y translate

	pb::vec4 v;
	v.x = 4;
	v.y = 3;
	v.z = 0;
	v.w = 1;

	pb::vec4 mv = pb::matmulMV(m, v);
	// std::cout << mv << std::endl;

	assert(mv.x == 9);
	assert(mv.y == 10);
	assert(mv.z == 0);
	assert(mv.w == 1);

	pb::mat4 im;
	im *= m;
	// std::cout << im << std::endl;
	assert(im[0][3] == 5);
	assert(im[1][3] == 7);

	v = im * mv;
	// std::cout << v << std::endl;
	assert(v.x == 14);
	assert(v.y == 17);

	im.identity();
	// std::cout << im << std::endl;
	assert(im == pb::mat4());

	return 1;
}

int matmulMM_test()
{
	pb::mat4 m0;
	pb::mat4 m1;

	pb::mat4 mm = pb::matmulMM(m0, m1);
	assert(mm == pb::mat4());
	// std::cout << mm << std::endl;

	return 1;
}


int main(void)
{
	srand(time(nullptr));

	pb::run_unit_test("create_mat4", create_mat4);
	pb::run_unit_test("matmulMV_test", matmulMV_test);
	pb::run_unit_test("matmulMM_test", matmulMM_test);

	std::cout << "## finished ##" << std::endl;

	return 0;
}
