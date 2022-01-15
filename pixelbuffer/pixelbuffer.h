/**
 * @file pixelbuffer.h
 *
 * @brief PixelBuffer of RGBA Colors: pb::PixelBuffer
 *
 * Copyright 2015-2022 @rktrlng
 * https://github.com/rktrlng/pixelbuffer
 */

#ifndef PIXELBUFFER_H
#define PIXELBUFFER_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

#include <pixelbuffer/color.h>
#include <pixelbuffer/vec2.h>

namespace pb {

class PixelBuffer {
private:
	struct PBHeader {
		uint8_t typep = 0x70;      // 1 byte: 0x70 = 'p'
		uint8_t typeb = 0x62;      // 1 byte: 0x62 = 'b'
		uint16_t width = 0x0000;   // 2 bytes: 0-65535
		uint16_t height = 0x0000;  // 2 bytes: 0-65535
		uint8_t bitdepth = 0x00;   // 1 byte: 1, 8, 16, 24, 32
		uint8_t end = 0x3A;        // 1 byte: 0x3A = ':'
	};                             // sizeof(PBHeader) = 8 bytes
	// uint64_t header = 0x706208000400203A; // 8x4 pixels, bitdepth 32, Little Endian
	// uint64_t header = 0x706200080004203A; // 8x4 pixels, bitdepth 32, Big Endian

	PBHeader _header;
	std::vector<RGBAColor> _pixels;

	bool _validBitdepth(uint8_t b) const {
		return (
			b == 1 ||
			b == 8 ||
			b == 16 ||
			b == 24 ||
			b == 32
		);
	}

public:
	PixelBuffer()
	{
		// default header
		// empty list of pixels
	}

	PixelBuffer(uint16_t width, uint16_t height, uint8_t bitdepth, pb::RGBAColor color = TRANSPARENT)
	{
		_header.width = width;
		_header.height = height;
		_header.bitdepth = bitdepth;
		const size_t numpixels = width * height;
		_pixels.reserve(width*height);
		for (size_t i = 0; i < numpixels; i++) {
			_pixels.emplace_back(color);
		}
	}

	PixelBuffer(const std::string& filename)
	{
		read(filename);
	}

	PixelBuffer(const PixelBuffer& other)
	{
		_header.width = other._header.width;
		_header.height = other._header.height;
		_header.bitdepth = other._header.bitdepth;

		size_t numpixels = _header.width * _header.height;
		for (size_t i = 0; i < numpixels; i++) {
			_pixels.push_back(other._pixels[i]);
		}
	}

	~PixelBuffer()
	{
		_header.width = 0;
		_header.height = 0;
		_pixels.clear();
	}

	const PBHeader header() const { return _header; }
	std::vector<RGBAColor>& pixels() { return _pixels; }
	const std::vector<RGBAColor>& pixels() const { return _pixels; }
	inline RGBAColor& operator[](size_t index) {
		if (index < _pixels.size() && index >= 0) { return _pixels[index]; }
		return _pixels[0];
	}

	uint8_t width() const { return _header.width; }
	uint8_t height() const { return _header.height; }
	uint8_t bitdepth() const { return _header.bitdepth; }
	uint8_t bitdepth(uint8_t b) {
		if ( _validBitdepth(b) ) {
			_header.bitdepth = b;
		}
		return _header.bitdepth;
	}

	bool valid() const
	{
		return _header.typep == 0x70 &&
			_header.typeb == 0x62 &&
			( _validBitdepth(_header.bitdepth) ) &&
			_header.end == 0x3A &&
			_header.width * _header.height == _pixels.size();
	}

	void printInfo() const
	{
		uint16_t width = _header.width;
		uint16_t height = _header.height;
		uint8_t bitdepth = _header.bitdepth;

		// std::cout << "sizeof(header): " << sizeof(_header) << " B" << std::endl;
		std::cout << "width: " << width << " pixels" << std::endl;
		std::cout << "height: " << height << " pixels" << std::endl;
		std::cout << "bitdepth: " << (int) bitdepth << " b/pixel" << std::endl;
		std::cout << "#number of pixels: " << (int) _pixels.size() << std::endl;
		std::cout << "memsize of pixels: " << (width * height * (bitdepth/8.0f)) << " B";
		std::cout << " | " << (width * height * (bitdepth/8.0f)) / 1024.0f << " KiB";
		std::cout << " | " << (width * height * (bitdepth/8.0f)) / 1024 / 1024.0f << " MiB" << std::endl;
	}

	int read(const std::string& filename)
	{
		// Try to open the file from disk
		std::ifstream file(filename, std::fstream::in|std::fstream::binary|std::fstream::ate);

		if (!file.is_open()) {
			std::cout << "Unable to open file: " << filename << std::endl;
			return 0;
		}

		// Read the file into a bytearray
		const int size = file.tellg();
		char* memblock = new char[size];
		file.seekg(0, std::fstream::beg);
		file.read(memblock, size);
		file.close();

		// Build header
		_header = *(PBHeader*)&memblock[0];

		// Build list of pixels
		size_t numpixels = _header.width * _header.height;
		_pixels.clear();
		_pixels.reserve(numpixels);
		size_t start = sizeof(_header);

		if (_header.bitdepth == 1) {
			for (size_t i = 0; i < numpixels / 8; i++) {
				char val = memblock[start+0];
				std::vector<pb::RGBAColor> vec = pb::Color::byte2vec(val);
				for (size_t i = 0; i < vec.size(); i++) {
					_pixels.emplace_back(vec[i]);
				}
				vec.clear();
				start++; // next byte
			}
		} else {
			for (size_t i = 0; i < numpixels; i++) {
				RGBAColor pixel;
				if (_header.bitdepth == 8 || _header.bitdepth == 16) {
					char val = memblock[start+0];
					pixel.r = val;
					pixel.g = val;
					pixel.b = val;
					pixel.a = 255;
				}

				if (_header.bitdepth == 16) {
					pixel.a = memblock[start+1];
				}
				else if (_header.bitdepth == 24 || _header.bitdepth == 32) {
					pixel.r = memblock[start+0];
					pixel.g = memblock[start+1];
					pixel.b = memblock[start+2];
					pixel.a = 255;
				}

				if (_header.bitdepth == 32) {
					pixel.a = memblock[start+3];
				}

				_pixels.emplace_back(pixel);

				start += _header.bitdepth / 8;
			}
		}

		delete[] memblock;

		return size;
	}

	int write(const std::string& filename) const
	{
		// Try to write to a file
		std::ofstream file(filename, std::fstream::out|std::fstream::binary|std::fstream::trunc);
		if (!file.is_open()) {
			std::cout << "Unable to write to file: " << filename << std::endl;
			return 0;
		}

		// Write header
		file.write((char*)&_header, sizeof(_header));

		// Write pixeldata
		// This would work if we only needed to write 4 bytes/pixel files:
		// file.write((char*)&_pixels[0], _pixels.size()*_header.bitdepth);

		// But we also need to handle the bitdepth
		if (_header.bitdepth == 1) {
			size_t start = 0;

			char value = 0;
			// width must be a multiple of 8 pixels
			std::vector<RGBAColor> vec;
			for (size_t i = 0; i < _pixels.size(); i += 8) { // set of 8 pixels
				for (size_t v = 0; v < 8; v++) {
					vec.push_back(_pixels[v+start]);
				}
				value = (char) pb::Color::vec2byte(vec);
				file.write(&value, 1);
				vec.clear();
				start += 8;
			}
		} else {
			for (auto& pixel : _pixels) {
				if (_header.bitdepth == 8 || _header.bitdepth == 16) {
					char value = (pixel.r + pixel.b + pixel.g) / 3;
					file.write(&value, 1);
				}

				if (_header.bitdepth == 16) {
					file.write((char*)&pixel.a, 1);
				}
				else if (_header.bitdepth == 24 || _header.bitdepth == 32) {
					file.write((char*)&pixel.r, 1);
					file.write((char*)&pixel.g, 1);
					file.write((char*)&pixel.b, 1);
				}

				if (_header.bitdepth == 32) {
					file.write((char*)&pixel.a, 1);
				}
			}
		}

		file.close();

		return 1;
	}

	std::string createFilename(const std::string& prefix, uint32_t counter = 0, uint8_t leading0 = 4) const
	{
		std::stringstream filename;
		filename << prefix;
		for (int i = 1; i < leading0+1; i++) {
			if (counter < pow(10, i)) { filename << "0"; }
		}
		filename << counter << ".pbf";
		return filename.str();
	}

	int fromTGA(const std::string& filename)
	{
		// www.paulbourke.net/dataformats/tga/

		// Try to open the file from disk
		std::ifstream file(filename, std::fstream::in|std::fstream::binary|std::fstream::ate);

		if (!file.is_open()) {
			std::cout << "Unable to open file: " << filename << std::endl;
			return 0;
		}

		// Read the file into a bytearray
		const int size = file.tellg();
		char* memblock = new char[size];
		file.seekg(0, std::fstream::beg);
		file.read(memblock, size);
		file.close();

		// Read TGA header
		const uint8_t headersize = 18;
		const uint8_t datatype = memblock[2];
		// const uint16_t x_org   = (memblock[8] & 0xFF) + (memblock[9] << 8);
		const uint16_t y_org   = (memblock[10] & 0xFF) + (memblock[11] << 8);
		const uint16_t width   = (memblock[12] & 0xFF) + (memblock[13] << 8);
		const uint16_t height  = (memblock[14] & 0xFF) + (memblock[15] << 8);
		const uint8_t bitdepth = memblock[16];
		if (datatype > 3) { delete[] memblock; return 0; } // compressed image

		// std::cout << "datatype " << (int) datatype << std::endl;
		// std::cout << "x_org    " << (int) x_org << std::endl;
		// std::cout << "y_org    " << (int) y_org << std::endl;
		// std::cout << "width    " << (int) width << std::endl;
		// std::cout << "height   " << (int) height << std::endl;
		// std::cout << "bitdepth " << (int) bitdepth << std::endl;

		// Create and build the pixelbuffer
		_header.width = width;
		_header.height = height;
		_header.bitdepth = bitdepth;

		const size_t numpixels = width * height;
		_pixels.clear();
		_pixels.reserve(width*height);
		for (size_t i = 0; i < numpixels; i++) {
			_pixels.emplace_back(pb::RGBAColor(0, 0, 0, 255));
		}

		// Place the pixels
		size_t start = headersize;
		for (size_t i = 0; i < numpixels; i++) {
			pb::RGBAColor color;
			if (bitdepth == 8) {
				color.r = memblock[start+0];
				color.g = memblock[start+0];
				color.b = memblock[start+0];
				color.a = 255;
			}
			if (bitdepth == 24) { // BGR
				color.r = memblock[start+2];
				color.g = memblock[start+1];
				color.b = memblock[start+0];
				color.a = 255;
			}
			if (bitdepth == 32) { // BGRA
				color.r = memblock[start+2];
				color.g = memblock[start+1];
				color.b = memblock[start+0];
				color.a = memblock[start+3];
			}
			_pixels[i] = color;
			start += bitdepth / 8;
		}

		delete[] memblock;

		// tga: (0, 0) is bottom left
		// pbf: (0, 0) is top left
		if(y_org == 0) {
			flipRows();
		}

		return size;
	}

	void flipRows()
	{
		PixelBuffer* duplicate = new PixelBuffer(*this);
		fill(TRANSPARENT);

		uint16_t rows = header().height;
		uint16_t cols = header().width;

		for (size_t y = 0; y < rows; y++) {
			for (size_t x = 0; x < cols; x++) {
				pb::RGBAColor color = duplicate->getPixel(x, rows-y-1);
				setPixel(x, y, color);
			}
		}
		delete duplicate;
	}

	PixelBuffer copy(uint16_t x, uint16_t y, uint16_t width, uint16_t height) const
	{
		PixelBuffer buffer = PixelBuffer(width, height, header().bitdepth);

		size_t maxheight = height + y;
		size_t maxwidth = width + x;
		for (size_t ny = y; ny < maxheight; ny++) {
			for (size_t nx = x; nx < maxwidth; nx++) {
				RGBAColor pixel = getPixel(nx, ny);
				buffer.setPixel(nx-x, ny-y, pixel);
			}
		}

		return buffer;
	}

	int paste(const PixelBuffer& brush, short pos_x, short pos_y)
	{
		size_t height = brush.header().height;
		size_t width = brush.header().width;
		for (size_t y = 0; y < height; y++) {
			for (size_t x = 0; x < width; x++) {
				RGBAColor color = brush.getPixel(x, y);
				// setPixel handles alpha
				setPixel(x+pos_x, y+pos_y, color);
			}
		}

		return 1;
	}

	int setPixel(int x, int y, RGBAColor color)
	{
		// Sanity check
		if ( (x < 0) || (x >_header.width) || (y < 0) || (y > _header.height) ) {
			return 0;
		}

		size_t index = (y * _header.width) + x;
		if (index >= _pixels.size()) { // invalid pixels!
			return 0;
		}

		if (color.a < 255) {
			color = pb::Color::alphaBlend(color, getPixel(x, y));
		}
		_pixels[index] = color;

		return 1;
	}

	RGBAColor getPixel(int x, int y) const
	{
		// Sanity check
		if ( (x < 0) || (x >_header.width) || (y < 0) || (y > _header.height) ) {
			return { 0, 0, 0, 0 };
		}

		size_t index = (y * _header.width) + x;
		if (index >= _pixels.size()) { // invalid pixels!
			return { 0, 0, 0, 0 };
		}

		return _pixels[index];
	}

	void drawLine(int x0, int y0, int x1, int y1, RGBAColor color)
	{
		bool steep = false;
		if (std::abs(x0-x1) < std::abs(y0-y1)) {
			std::swap(x0, y0);
			std::swap(x1, y1);
			steep = true;
		}
		if (x0 > x1) {
			std::swap(x0, x1);
			std::swap(y0, y1);
		}
		int dx = x1-x0;
		int dy = y1-y0;
		int derror2 = std::abs(dy)*2;
		int error2 = 0;
		int y = y0;

		for (int x = x0; x <= x1; x++) {
			if (steep) {
				setPixel(y, x, color);
			} else {
				setPixel(x, y, color);
			}
			error2 += derror2;

			if (error2 > dx) {
				y += (y1 > y0 ? 1 : -1);
				error2 -= dx*2;
			}
		}
	}

	void drawSquare(int x0, int y0, int x1, int y1, RGBAColor color)
	{
		drawLine(x0,    y0,    x0+x1, y0,    color);
		drawLine(x0+x1, y0,    x0+x1, y0+y1, color);
		drawLine(x0,    y0+y1, x0+x1, y0+y1, color);
		drawLine(x0,    y0,    x0,    y0+y1, color);
	}

	void fill(RGBAColor color)
	{
		size_t numpixels = _header.width * _header.height;
		for (size_t i = 0; i < numpixels; i++) {
			_pixels[i] = color;
		}
	}

	void drawCircle(int circlex, int circley, int radius, RGBAColor color)
	{
		int x = radius;
		int y = 0;
		int err = 0;

		std::vector<vec2i> positions;

		while (x >= y) {
			positions.push_back( {  x,  y } );
			positions.push_back( {  y,  x } );
			positions.push_back( { -y,  x } );
			positions.push_back( { -x,  y } );
			positions.push_back( { -x, -y } );
			positions.push_back( { -y, -x } );
			positions.push_back( {  y, -x } );
			positions.push_back( {  x, -y } );

			if (err <= 0) {
				y += 1;
				err += 2*y + 1;
			}
			if (err > 0) {
				x -= 1;
				err -= 2*x + 1;
			}
		}

		for (auto local : positions) {
			setPixel(local.x + circlex, local.y + circley, color);
		}
	}

	// sharpness 1 = fully blurred
	// sharpness ..50+ = less blurred
	void blur(int sharpness = 1)
	{
		size_t rows = _header.height;
		size_t cols = _header.width;

		for (size_t y = 0; y < rows; y++) {
			for (size_t x = 0; x < cols; x++) {
				// check surrounding colors and average values
				int totalr = 0; // total red
				int totalg = 0; // total green
				int totalb = 0; // total blue
				int totala = 0; // total alpha
				for (int r = -1; r < 2; r++) {
					for (int c = -1; c < 2; c++) {
						vec2i n = clamp(vec2i(x+c, y+r), cols, rows);
						RGBAColor color = getPixel(n.x, n.y);
						if (r==0 && c==0) {
							totalr += color.r * sharpness;
							totalg += color.g * sharpness;
							totalb += color.b * sharpness;
							totala += color.a * sharpness;
						} else {
							totalr += color.r;
							totalg += color.g;
							totalb += color.b;
							totala += color.a;
						}
					}
				}
				uint8_t r = totalr / (8 + sharpness);
				uint8_t g = totalg / (8 + sharpness);
				uint8_t b = totalb / (8 + sharpness);
				uint8_t a = totala / (8 + sharpness);
				RGBAColor avg = { r, g, b, a };
				setPixel(x, y, avg);
			}
		}
	}

}; // PixelBuffer

} // namespace pb

#endif // PIXELBUFFER_H
