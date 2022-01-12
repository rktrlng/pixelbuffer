#include <iostream>
#include <assert.h>

#include <pixelbuffer/pixelbuffer.h>

int main(void)
{
	std::cout << "read testpattern.tga" << std::endl;
	std::cout << "write fromTGA.pbf" << std::endl;

	pb::PixelBuffer pixelbuffer;
	pixelbuffer.fromTGA("testpattern.tga");
	pixelbuffer.write("fromTGA.pbf");

	return 0;
}
