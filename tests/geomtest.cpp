#include <iostream>
#include <cassert>

#include <pixelbuffer/math/geom.h>
#include <pixelbuffer/util.h>

int create_circle()
{
	rt::Circle c(100, 150, 5);
	std::cout << c << std::endl;

    return 1;
}


int main(void)
{
	srand(time(nullptr));

	rt::run_unit_test("create_circle", create_circle);

	std::cout << "## finished ##" << std::endl;

	return 0;
}
