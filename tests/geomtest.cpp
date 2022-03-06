#include <iostream>
#include <cassert>

#include <pixelbuffer/math/geom.h>
#include <pixelbuffer/util.h>

int create_line()
{
	// rt::Line l(100, 100, 200, 100);
	rt::Line l({100, 100}, {200, 100});
	// rt::Line l(rt::vec2(100, 100));
	// rt::Line l;
	std::cout << l << std::endl;

    return 1;
}

int create_circle()
{
	// rt::Circle c(100, 150);
	// rt::Circle c;
	rt::Circle c(100, 150, 5);
	std::cout << c << std::endl;

    return 1;
}

int create_rectangle()
{
	// rt::Rectangle r;
	// rt::Rectangle r({100, 100}, {40, 30});
	// rt::Rectangle r(100, 100, 40, 30);
	rt::Rectangle r(rt::vec2(100, 100), rt::vec2(40, 30));
	std::cout << r << std::endl;

    return 1;
}

int main(void)
{
	srand(time(nullptr));

	rt::run_unit_test("create_line", create_line);
	rt::run_unit_test("create_circle", create_circle);
	rt::run_unit_test("create_rectangle", create_rectangle);

	std::cout << "## finished ##" << std::endl;

	return 0;
}
