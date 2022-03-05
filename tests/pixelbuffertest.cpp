#include <iostream>
#include <cassert>

#include <pixelbuffer/pixelbuffer.h>
#include <pixelbuffer/util.h>

// ########################################################
int floodfill()
{
	rt::PixelBuffer pixelbuffer(256, 256, 32);

	srand(time(nullptr));
	rt::RGBAColor color = RED;
	for (size_t i = 0; i < 25; i++) {
		float x = rt::rand_bm() * 256;
		float y = rt::rand_bm() * 256;
		pixelbuffer.drawCircleFilled(x, y, rt::rand_bm() * 32, color);
		// pixelbuffer.drawSquare(x, y, rt::rand_bm() * 64, rt::rand_bm() * 64, color);
		// pixelbuffer.drawSquareFilled(x, y, rt::rand_bm() * 64, rt::rand_bm() * 64, color);
		color = rt::rotate(color, 0.006f);
	}

	// writing
	pixelbuffer.write("floodfill.pbf");
	std::cout << "floodfill.pbf" << std::endl;

	pixelbuffer.bitdepth(32);
	pixelbuffer.writeTGA("floodfill.tga");
	std::cout << "floodfill.tga" << std::endl;

	pixelbuffer.fromTGA("floodfill.tga");
	pixelbuffer.write("floodfilltga.pbf");
	std::cout << "floodfilltga.pbf" << std::endl;

	return 1;
}

int pattern()
{
	int width = 160;
	int height = 90;
	int step = 10;
	rt::PixelBuffer pb(width, height, 24);
	pb.fill(BLACK);

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
	pb.drawLine(0, 0, width, height-1, rt::RGBAColor(0, 0, 255, 128));
	pb.drawLine(0, height-1, width, 0, rt::RGBAColor(0, 0, 255, 128));

	// white outline and transparent yellow circle
	pb.drawSquare(0, 0, width-1, height-1, WHITE);
	pb.drawCircle(width/2, height/2, 31, rt::RGBAColor(255, 255, 0, 128));

	// write pixelbuffer to file
	std::cout << "Writing testpattern.pbf" << std::endl;
	std::cout << "convert with: pbf2img testpattern.pbf png" << std::endl;
	pb.write("testpattern.pbf");
	pb.writeTGA("testpattern.tga");

	return 1;
}

int onebit()
{
	size_t height = 256;
	rt::PixelBuffer pixelbuffer(8, height, 1);
	pixelbuffer.pixels().clear();

	uint8_t value = 0x55; // 0x55 is (dec) 85

	std::cout << "value: " << (int) value << std::endl;

	std::vector<rt::RGBAColor> colors;
	colors = pixelbuffer.byte2vec(value);

	std::string colorstring = "";
	for (size_t i = 0; i < colors.size(); i++) {
		colorstring += "color[" + std::to_string(i) + "].r: " + std::to_string(colors[i].r) + "\n";
		if (colors[i].r == 0) {
			std::cout << (int) 0;
		} else {
			std::cout << (int) 1;
		}
	}
	std::cout << "\n";
	std::cout << colorstring;

	value = 0;
	value = pixelbuffer.vec2byte(colors);

	std::cout << "value: " << (int) value << std::endl;

	// generate and write binarycounter.pbf
	for (size_t row = 0; row < height; row++) {
		std::vector<rt::RGBAColor> colorvec = pixelbuffer.byte2vec(row);
		for (size_t i = 0; i < 8; i++) {
			pixelbuffer.pixels().push_back(colorvec[i]);
		}
	}
	// writing
	pixelbuffer.write("binarycounter.pbf");
	// pixelbuffer.printInfo();

	// reading
	rt::PixelBuffer pbr("binarycounter.pbf");
	// pbr.printInfo();

	return 1;
}

int tga_read_write()
{
	std::cout << "read testpattern.tga" << std::endl;
	std::cout << "write fromTGA.pbf" << std::endl;

	rt::PixelBuffer pixelbuffer;
	pixelbuffer.fromTGA("testpattern.tga");
	pixelbuffer.write("fromTGA.pbf");

	return 1;
}
// ########################################################

int test_create()
{
	rt::PixelBuffer pb;

	assert((int)pb.valid() == 1);
	assert(pb.width() == 0);
	assert(pb.height() == 0);
	assert(pb.bitdepth() == 32);

	pb = rt::PixelBuffer(8, 8, 32);
	assert((int)pb.valid() == 1);
	assert(pb.width() == 8);
	assert(pb.height() == 8);
	assert(pb.bitdepth() == 32);

	assert(pb.getPixel(0, 0) == rt::RGBAColor(0, 0, 0, 0));

	return 1;
}

int test_drawline()
{
	rt::PixelBuffer pb = rt::PixelBuffer(8, 8, 32);
	rt::RGBAColor color = rt::RGBAColor(255, 0, 0);
	pb.drawLine(0, 0, 8, 8, color);
	assert(pb.getPixel(0, 0) == color);
	assert(pb.getPixel(1, 1) == color);
	assert(pb.getPixel(2, 2) == color);
	assert(pb.getPixel(3, 3) == color);
	assert(pb.getPixel(4, 4) == color);
	assert(pb.getPixel(5, 5) == color);
	assert(pb.getPixel(6, 6) == color);
	assert(pb.getPixel(7, 7) == color);

	assert(pb.getPixel(1, 3) != color);
	assert(pb.getPixel(4, 2) != color);

	assert(pb.getPixel(4, 2) == rt::RGBAColor(0, 0, 0, 0));

	return 1;
}

int main(void)
{
	srand(time(nullptr));

	// floodfill();
	// pattern();
	// onebit();
	// tga_read_write();

	rt::run_unit_test("test_create", test_create);
	rt::run_unit_test("test_drawline", test_drawline);

	return 0;
}
