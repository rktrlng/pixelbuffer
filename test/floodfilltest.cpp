#include <iostream>
#include <assert.h>

#include <pixelbuffer/pixelbuffer.h>

int main(void)
{
	pb::PixelBuffer pixelbuffer(256, 256, 24);
	pixelbuffer.fill(GRAY);

	pixelbuffer.drawSquare(64, 64, 128, 128, GREEN);
	pixelbuffer.floodFill(128, 128, ORANGE);

	pixelbuffer.drawCircle(128, 128, 42, WHITE);
	pixelbuffer.floodFill(128, 128, BLUE);

	pixelbuffer.drawCircle(55, 55, 32, WHITE);
	pixelbuffer.floodFill(pb::vec2i(55, 55), RED);
	pixelbuffer.floodFill(70, 70, CYAN);

	// writing
	pixelbuffer.write("floodfill.pbf");
	std::cout << "floodfill.pbf" << std::endl;

	return 0;
}
