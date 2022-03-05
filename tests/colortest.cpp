#include <iostream>
#include <cassert>

#include <pixelbuffer/color.h>
#include <pixelbuffer/util.h>

int create_color()
{
	rt::RGBAColor white;
	assert(white.r == 255);
	assert(white.g == 255);
	assert(white.b == 255);
	assert(white.a == 255);

	rt::RGBAColor rgb = rt::RGBAColor(127, 42, 35);
	assert(rgb.r == 127);
	assert(rgb.g == 42);
	assert(rgb.b == 35);
	assert(rgb.a == 255);

	rt::RGBAColor gray = rt::RGBAColor(42, 127);
	assert(gray.r == 42);
	assert(gray.g == 42);
	assert(gray.b == 42);
	assert(gray.a == 127);

	rt::RGBAColor frm_int = rt::RGBAColor::fromInt(1439445930);
	// 0101 0101  1100 1100  0011 0011  1010 1010
	assert(frm_int.r == 85);
	assert(frm_int.g == 204);
	assert(frm_int.b == 51);
	assert(frm_int.a == 170);

	rt::RGBAColor to_int = rt::RGBAColor(85, 204, 51, 170);
	int fi = to_int.asInt();
	assert(fi == 1439445930);

    return 1;
}

int color_eq()
{
	rt::RGBAColor a;
	a.g = 0;
	rt::RGBAColor b;
	b.g = 0;

	assert(a == b);
	b.g = 127;
	assert(a != b);

    return 1;
}

int color_index()
{
	rt::RGBAColor rgb = rt::RGBAColor(127, 42, 35);
	assert(rgb[0] == 127);
	assert(rgb[1] == 42);
	assert(rgb[2] == 35);
	assert(rgb[3] == 255);

	rgb[0] = 42;
	rgb[1] = 35;
	rgb[2] = 127;
	rgb[3] = 170;

	assert(rgb.r == 42);
	assert(rgb.g == 35);
	assert(rgb.b == 127);
	assert(rgb.a == 170);

	return 1;
}

int color_rotate()
{
	rt::RGBAColor rgb = rt::RGBAColor(255, 0, 0, 255);
	rgb = rt::rotate(rgb, 0.25f);
	assert(rgb.r == 127);
	assert(rgb.g == 255);
	assert(rgb.b == 0);
	assert(rgb.a == 255);

	rgb = rt::RGBAColor(255, 0, 0, 255);
	rgb = rt::rotate(rgb, 0.5f);
	assert(rgb.r == 0);
	assert(rgb.g == 255);
	assert(rgb.b == 255);
	assert(rgb.a == 255);
	
	rgb = rt::RGBAColor(255, 0, 0, 127);
	rgb = rt::rotate(rgb, 1.0f);
	assert(rgb.r == 255);
	assert(rgb.g == 0);
	assert(rgb.b == 0);
	assert(rgb.a == 127);

	return 1;
}


int main(void)
{
	rt::run_unit_test("create_color", create_color);
	rt::run_unit_test("color_eq", color_eq);
	rt::run_unit_test("color_index", color_index);
	rt::run_unit_test("color_rotate", color_rotate);

	std::cout << "## finished ##" << std::endl;

	return 0;
}
