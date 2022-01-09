#include <iostream>
#include <assert.h>

#include <pixelbuffer/color.h>

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

	return 0;
}
