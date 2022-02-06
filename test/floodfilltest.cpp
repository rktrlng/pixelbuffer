#include <iostream>
#include <assert.h>

#include <pixelbuffer/pixelbuffer.h>

int main(void)
{
	pb::PixelBuffer pixelbuffer(256, 256, 32);
	// pixelbuffer.fill(GRAY);

	srand(time(nullptr));
	pb::RGBAColor color = RED;
	for (size_t i = 0; i < 25; i++) {
		float x = pb::rand_bm() * 256;
		float y = pb::rand_bm() * 256;
		pixelbuffer.drawCircleFilled(x, y, pb::rand_bm() * 32, color);
		// pixelbuffer.drawSquare(x, y, pb::rand_bm() * 64, pb::rand_bm() * 64, color);
		// pixelbuffer.drawSquareFilled(x, y, pb::rand_bm() * 64, pb::rand_bm() * 64, color);
		color = pb::Color::rotate(color, 0.006f);
	}

	// writing
	pixelbuffer.write("floodfill.pbf");
	std::cout << "floodfill.pbf" << std::endl;

	pixelbuffer.bitdepth(32);
	pixelbuffer.writeTGA("floodfill.tga");
	std::cout << "floodfill.tga" << std::endl;

	return 0;
}
