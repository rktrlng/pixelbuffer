#include <iostream>
#include <assert.h>

#include <pixelbuffer/pixelbuffer.h>

int main(void)
{
	uint8_t value = 0x55; // 0x55 is (dec) 85

	std::cout << "value: " << (int) value << std::endl;

	std::vector<pb::RGBAColor> colors;
	colors = pb::Color::byte2vec(value);

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
	value = pb::Color::vec2byte(colors);

	std::cout << "value: " << (int) value << std::endl;

	// generate and write binarycounter.pbf
	size_t height = 256;
	pb::PixelBuffer pixelbuffer(8, height, 1);
	pixelbuffer.pixels().clear();
	for (size_t row = 0; row < height; row++) {
		std::vector<pb::RGBAColor> colorvec = pb::Color::byte2vec(row);
		for (size_t i = 0; i < 8; i++) {
			pixelbuffer.pixels().push_back(colorvec[i]);
		}
	}
	// writing
	pixelbuffer.write("binarycounter.pbf");
	// pixelbuffer.printInfo();

	// reading
	pb::PixelBuffer pbr("binarycounter.pbf");
	// pbr.printInfo();

	return 0;
}
