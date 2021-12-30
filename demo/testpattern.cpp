#include <iostream>
#include <pixelbuffer/pixelbuffer.h>

int main(void)
{
	int width = 160;
	int height = 90;
	int step = 10;
	pb::PixelBuffer pb(width, height, 24);

	// gray grid
	for (int x = 0; x < width; x += step) {
		pb.drawLine(x, 0, x, height-1, GRAY);
	}
	for (int y = 0; y < height; y += step) {
		pb.drawLine(0, y, width-1, y, GRAY);
	}

	// red dots
	for (int y = 0; y < height; y += step) {
		for (int x = 0; x < width; x += step) {
			pb.setPixel(x, y, RED);
		}
	}

	// transparent blue cross
	pb.drawLine(0, 0, width, height-1, pb::RGBAColor(0, 0, 255, 128));
	pb.drawLine(0, height-1, width, 0, pb::RGBAColor(0, 0, 255, 128));

	// white outline and transparent yellow circle
	pb.drawSquare(0, 0, width-1, height-1, WHITE);
	pb.drawCircle(width/2, height/2, 31, pb::RGBAColor(255, 255, 0, 128));

	// write pixelbuffer to file
	std::cout << "Writing testpattern.pbf" << std::endl;
	std::cout << "convert with: pbf2img testpattern.pbf png" << std::endl;
	pb.write("testpattern.pbf");

	return 0;
}
