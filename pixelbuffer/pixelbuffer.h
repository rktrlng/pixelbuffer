/**
 * @file pixelbuffer.h
 *
 * @brief PixelBuffer of RGBA Colors: rt::PixelBuffer
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
#include <pixelbuffer/math/vec2.h>
#include <pixelbuffer/util.h>

namespace rt {

// =========================================================
inline vec2i wrap (const vec2i& pos, int cols, int rows);
inline vec2i clamp(const vec2i& pos, int cols, int rows);
// =========================================================

class PixelBuffer {
private:
	struct PBHeader {
		uint8_t typep = 0x70;      // 1 byte: 0x70 = 'p'
		uint8_t typeb = 0x62;      // 1 byte: 0x62 = 'b'
		uint16_t width = 0x0000;   // 2 bytes: 0-65535
		uint16_t height = 0x0000;  // 2 bytes: 0-65535
		uint8_t bitdepth = 0x20;   // 1 byte: 1, 8, 16, 24, 32
		uint8_t end = 0x3A;        // 1 byte: 0x3A = ':'
	};                             // sizeof(PBHeader) = 8 bytes
	// uint64_t header = 0x706208000400203A; // 8x4 pixels, bitdepth 32, Little Endian
	// uint64_t header = 0x706200080004203A; // 8x4 pixels, bitdepth 32, Big Endian

	PBHeader m_header;
	std::vector<RGBAColor> m_pixels;

	bool _validBitdepth(uint8_t b) const {
		return (
			(b == 1 && m_header.width%8 == 0) ||
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
		// 32 bits per pixel
	}

	PixelBuffer(uint16_t width, uint16_t height, uint8_t bitdepth = 32, RGBAColor color = TRANSPARENT)
	{
		m_header.width = width;
		m_header.height = height;
		m_header.bitdepth = bitdepth;
		const size_t numpixels = width * height;
		m_pixels.reserve(width*height);
		for (size_t i = 0; i < numpixels; i++) {
			m_pixels.emplace_back(color);
		}
	}

	PixelBuffer(const std::string& filename)
	{
		read(filename);
	}

	PixelBuffer(const PixelBuffer& other)
	{
		m_header.width = other.m_header.width;
		m_header.height = other.m_header.height;
		m_header.bitdepth = other.m_header.bitdepth;

		size_t numpixels = m_header.width * m_header.height;
		for (size_t i = 0; i < numpixels; i++) {
			m_pixels.push_back(other.m_pixels[i]);
		}
	}

	~PixelBuffer()
	{
		m_header.width = 0;
		m_header.height = 0;
		m_pixels.clear();
	}

	const PBHeader header() const { return m_header; }
	std::vector<RGBAColor>& pixels() { return m_pixels; }
	const std::vector<RGBAColor>& pixels() const { return m_pixels; }
	inline RGBAColor& operator[](size_t index) {
		if (index < m_pixels.size()) { return m_pixels[index]; }
		return m_pixels[0];
	}

	uint16_t width() const { return m_header.width; }
	uint16_t height() const { return m_header.height; }
	uint8_t bitdepth() const { return m_header.bitdepth; }
	uint8_t bitdepth(uint8_t b) {
		if ( _validBitdepth(b) ) {
			m_header.bitdepth = b;
		}
		return m_header.bitdepth;
	}

	bool valid() const
	{
		return m_header.typep == 0x70 &&
			m_header.typeb == 0x62 &&
			( _validBitdepth(m_header.bitdepth) ) &&
			m_header.end == 0x3A &&
			m_header.width * m_header.height == m_pixels.size();
	}

	void printInfo() const
	{
		uint16_t width = m_header.width;
		uint16_t height = m_header.height;
		uint8_t bitdepth = m_header.bitdepth;

		std::cout << "sizeof(header): " << sizeof(m_header) << " B" << std::endl;
		std::cout << "width: " << width << " pixels" << std::endl;
		std::cout << "height: " << height << " pixels" << std::endl;
		std::cout << "bitdepth: " << (int) bitdepth << " b/pixel" << std::endl;
		std::cout << "number of pixels: " << (int) m_pixels.size() << std::endl;
		std::cout << "memsize of pbf: " << (width * height * (bitdepth/8.0f)) + sizeof(m_header) << " B" << std::endl;
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
		uint8_t* memblock = new uint8_t[size];
		file.seekg(0, std::fstream::beg);
		file.read((char*)memblock, size);
		file.close();

		// Build header
		m_header = *(PBHeader*)&memblock[0];

		// Build list of pixels
		size_t numpixels = m_header.width * m_header.height;
		m_pixels.clear();
		m_pixels.reserve(numpixels);
		size_t start = sizeof(m_header);

		if (m_header.bitdepth == 1) {
			for (size_t i = 0; i < numpixels / 8; i++) {
				uint8_t val = memblock[start+0];
				std::vector<RGBAColor> vec = byte2vec(val);
				for (size_t i = 0; i < vec.size(); i++) {
					m_pixels.emplace_back(vec[i]);
				}
				vec.clear();
				start++; // next byte
			}
		} else {
			for (size_t i = 0; i < numpixels; i++) {
				RGBAColor pixel;
				if (m_header.bitdepth == 8 || m_header.bitdepth == 16) {
					uint8_t val = memblock[start+0];
					pixel.r = val;
					pixel.g = val;
					pixel.b = val;
					pixel.a = 255;
				}

				if (m_header.bitdepth == 16) {
					pixel.a = memblock[start+1];
				}
				else if (m_header.bitdepth == 24 || m_header.bitdepth == 32) {
					pixel.r = memblock[start+0];
					pixel.g = memblock[start+1];
					pixel.b = memblock[start+2];
					pixel.a = 255;
				}

				if (m_header.bitdepth == 32) {
					pixel.a = memblock[start+3];
				}

				m_pixels.emplace_back(pixel);

				start += m_header.bitdepth / 8;
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
		file.write((char*)&m_header, sizeof(m_header));

		// Write pixeldata
		// This would work if we only needed to write 4 bytes/pixel files:
		// file.write((char*)&m_pixels[0], m_pixels.size()*m_header.bitdepth);

		// But we also need to handle the bitdepth
		if (m_header.bitdepth == 1) {
			size_t start = 0;

			char value = 0;
			// width must be a multiple of 8 pixels
			std::vector<RGBAColor> vec;
			for (size_t i = 0; i < m_pixels.size(); i += 8) { // set of 8 pixels
				for (size_t v = 0; v < 8; v++) {
					vec.push_back(m_pixels[v+start]);
				}
				value = (char) vec2byte(vec);
				file.write(&value, 1);
				vec.clear();
				start += 8;
			}
		} else {
			for (auto& pixel : m_pixels) {
				if (m_header.bitdepth == 8 || m_header.bitdepth == 16) {
					RGBAColor gray = rt::luminance(pixel);
					char value = (char) gray.r;
					file.write(&value, 1);
				}

				if (m_header.bitdepth == 16) {
					file.write((char*)&pixel.a, 1);
				}
				else if (m_header.bitdepth == 24 || m_header.bitdepth == 32) {
					file.write((char*)&pixel.r, 1);
					file.write((char*)&pixel.g, 1);
					file.write((char*)&pixel.b, 1);
				}

				if (m_header.bitdepth == 32) {
					file.write((char*)&pixel.a, 1);
				}
			}
		}

		file.close();

		return 1;
	}

	static std::vector<RGBAColor> byte2vec(uint8_t value) {
		std::vector<RGBAColor> colors(8);
		for (size_t i = 0; i < colors.size(); i++) {
			RGBAColor color = { 0, 0, 0, 255 }; // black
			if ( value & 1) { color = { 255, 255, 255, 255 }; } // white
			colors[7-i] = color;
			value >>= 1;
		}
		return colors;
	}

	static uint8_t vec2byte(const std::vector<RGBAColor>& colors) {
		size_t size = colors.size();
		if (size != 8) { return 0; }
		uint8_t value = 0;
		for (size_t i = 0; i < size; i++) {
			int avg = (colors[i].r + colors[i].g + colors[i].b) / 3;
			if (avg < 128 || colors[i].a < 128) { // black
				value &= ~(1 << (7-i)); // 0 on this bit (most significant bit first)
			} else { // white (not black)
				value |=  (1 << (7-i)); // 1 on this bit (most significant bit first)
			}
		}
		return value;
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

	// www.paulbourke.net/dataformats/tga/
	int fromTGA(const std::string& filename)
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

		// Read TGA header
		const uint8_t headersize = 18;
		const uint8_t datatype = memblock[2];
		// const uint16_t x_org   = (memblock[8] & 0xFF) + (memblock[9] << 8);
		// const uint16_t y_org   = (memblock[10] & 0xFF) + (memblock[11] << 8);
		const uint16_t width   = (memblock[12] & 0xFF) + (memblock[13] << 8);
		const uint16_t height  = (memblock[14] & 0xFF) + (memblock[15] << 8);
		const uint8_t bitdepth = memblock[16];
		// screen origin bit
		// 0 = Origin in lower left-hand corner
		// 1 = Origin in upper left-hand corner
		const bool origin_bit = (memblock[17] >> 5) & 1;

		if (datatype > 3) { delete[] memblock; return 0; } // compressed image

		// std::cout << "datatype " << (int) datatype << std::endl;
		// std::cout << "x_org    " << (int) x_org << std::endl;
		// std::cout << "y_org    " << (int) y_org << std::endl;
		// std::cout << "width    " << (int) width << std::endl;
		// std::cout << "height   " << (int) height << std::endl;
		// std::cout << "bitdepth " << (int) bitdepth << std::endl;

		// Create and build the pixelbuffer
		m_header.width = width;
		m_header.height = height;
		m_header.bitdepth = bitdepth;

		const size_t numpixels = width * height;
		m_pixels.clear();
		m_pixels.reserve(width*height);
		for (size_t i = 0; i < numpixels; i++) {
			m_pixels.emplace_back(RGBAColor(0, 0, 0, 255));
		}

		// Place the pixels
		size_t start = headersize;
		for (size_t i = 0; i < numpixels; i++) {
			RGBAColor color;
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
			m_pixels[i] = color;
			start += bitdepth / 8;
		}

		delete[] memblock;

		// origin top-left
		if (!origin_bit) {
			flipRows();
		}

		return size;
	}

	// http://paulbourke.net/dataformats/tga/
	int writeTGA(const std::string&  filename)
	{
		// Try to write to a file
		std::ofstream file(filename, std::fstream::out|std::fstream::binary|std::fstream::trunc);

		if (!file.is_open()) {
			std::cout << "Unable to write to file: " << filename << std::endl;
			return 0;
		}

		// set bitdepth for tga (1 bit is grayscale)
		int bd = bitdepth();
		if (bd == 1 || bd == 8) { bd = 24; }
		if (bd == 16) { bd = 32; }

		// The image header
		unsigned char tgaheader[ 18 ] = { 0 };
		tgaheader[ 2 ] = 2; // true color (grayscale saved as rgb for now)
		// tgaheader[ 10 ] = height() & 0xFF; // y_org low byte
		// tgaheader[ 11 ] = (height() >> 8) & 0xFF; // y_org high byte
		tgaheader[ 12 ] = width() & 0xFF;
		tgaheader[ 13 ] = (width() >> 8) & 0xFF;
		tgaheader[ 14 ] = height() & 0xFF;
		tgaheader[ 15 ] = (height() >> 8) & 0xFF;
		tgaheader[ 16 ] = bd;
		tgaheader[ 17 ] = (1 << 5); // origin top-left

		// Write header
		file.write((char*)&tgaheader, sizeof(tgaheader));

		for (int y = 0; y < height(); y++) {
			for (int x = 0; x < width(); x++) {
				size_t index = rt::index(x, y, width());
				RGBAColor pixel = m_pixels[index];

				if (bd == 24 || bd == 32) {
					RGBAColor gray = rt::luminance(m_pixels[index]);
					if (bitdepth() == 8 || bitdepth() == 16) {
						file.write((char*)&gray.b, 1);
						file.write((char*)&gray.g, 1);
						file.write((char*)&gray.r, 1);
					} else {
						file.write((char*)&pixel.b, 1);
						file.write((char*)&pixel.g, 1);
						file.write((char*)&pixel.r, 1);
					}
					if (bitdepth() == 16 || bitdepth() == 32) {
						file.write((char*)&pixel.a, 1);
					}
				}
			}
		}

		file.close();

		return 1;
	}

	void flipRows()
	{
		PixelBuffer* duplicate = new PixelBuffer(*this);
		fill(TRANSPARENT);

		uint16_t rows = height();
		uint16_t cols = width();

		for (size_t y = 0; y < rows; y++) {
			for (size_t x = 0; x < cols; x++) {
				RGBAColor color = duplicate->getPixel(x, rows-y-1);
				setPixel(x, y, color);
			}
		}
		delete duplicate;
	}

	PixelBuffer copy(uint16_t x, uint16_t y, uint16_t width, uint16_t height) const
	{
		PixelBuffer buffer = PixelBuffer(width, height, bitdepth());

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
				// setPixel handles alpha if we set blend true
				setPixel(x+pos_x, y+pos_y, color, true);
			}
		}

		return 1;
	}

	int setPixel(int x, int y, RGBAColor color, bool blend = false)
	{
		// Sanity check
		if ( (x < 0) || (x >=m_header.width) || (y < 0) || (y >= m_header.height) ) {
			return 0;
		}

		size_t index = (y * m_header.width) + x;
		if (index >= m_pixels.size()) { // invalid pixels!
			return 0;
		}

		if (color.a < 255 && blend) {
			color = rt::alphaBlend(color, getPixel(x, y));
		}
		m_pixels[index] = color;

		return 1;
	}

	RGBAColor getPixel(int x, int y) const
	{
		// Sanity check
		if ( (x < 0) || (x >=m_header.width) || (y < 0) || (y >= m_header.height) ) {
			return { 0, 0, 0, 0 };
		}

		size_t index = (y * m_header.width) + x;
		if (index >= m_pixels.size()) { // invalid pixels!
			return { 0, 0, 0, 0 };
		}

		return m_pixels[index];
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
				setPixel(y, x, color, true);
			} else {
				setPixel(x, y, color, true);
			}
			error2 += derror2;

			if (error2 > dx) {
				y += (y1 > y0 ? 1 : -1);
				error2 -= dx*2;
			}
		}
	}

	void drawSquare(int x, int y, int width, int height, RGBAColor color)
	{
		drawLine(x,       y,        x+width, y,        color);
		drawLine(x+width, y,        x+width, y+height, color);
		drawLine(x,       y+height, x+width, y+height, color);
		drawLine(x,       y,        x,       y+height, color);
	}

	void drawSquareFilled(int x, int y, int width, int height, RGBAColor color)
	{
		PixelBuffer pb = PixelBuffer(width, height, m_header.bitdepth);
		pb.fill(color);
		paste(pb, x, y);
	}

	void fill(RGBAColor color)
	{
		size_t numpixels = m_header.width * m_header.height;
		for (size_t i = 0; i < numpixels; i++) {
			m_pixels[i] = color;
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
			setPixel(local.x + circlex, local.y + circley, color, true);
		}
	}

	void drawCircleFilled(int circlex, int circley, int radius, RGBAColor color)
	{
		// drawCircle(circlex, circley, radius, color);
		int size = radius*2;
		PixelBuffer pb = PixelBuffer(size, size, m_header.bitdepth);
		pb.drawCircle(size/2, size/2, radius, color);
		pb.floodFill(size/2, size/2, color);
		paste(pb, circlex-radius, circley-radius);
	}

	// sharpness 1 = fully blurred
	// sharpness ..50+ = less blurred
	void blur(int sharpness = 1)
	{
		size_t rows = m_header.height;
		size_t cols = m_header.width;

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
				setPixel(x, y, avg, true);
			}
		}
	}

	void contrast_8() {
		// find min + max
		uint8_t min = 255;
		uint8_t max = 0;
		for (size_t i = 0; i < m_pixels.size(); i++) {
			if (m_pixels[i].r < min) min = m_pixels[i].r;
			if (m_pixels[i].r > max) max = m_pixels[i].r;
		}

		// map values
		for (size_t i = 0; i < m_pixels.size(); i++) {
			uint8_t readvalue = m_pixels[i].r;
			uint8_t writevalue = rt::map(readvalue, min, max, 0, 255);
			m_pixels[i] = {writevalue, writevalue, writevalue, 255};
		}
	}

	void posterize_8(uint8_t levels) {
		for (size_t i = 0; i < m_pixels.size(); i++) {
			uint8_t readvalue = m_pixels[i].r;
			uint8_t writevalue = rt::map(readvalue, 0, 255, 0, levels);
			writevalue = rt::map(writevalue, 0, levels, 0, 255);
			m_pixels[i] = {writevalue, writevalue, writevalue, 255};
		}
	}

	void floodFill(vec2i pos, RGBAColor fill_color)
	{
		floodFill(pos.x, pos.y, fill_color);
	}

	// Warning: hardcoded crazy color in 2 places
	void floodFill(int x, int y, RGBAColor fill_color, RGBAColor check_color = {242, 13, 248, 1})
	{
		int height = m_header.height;
		int width = m_header.width;

		if (check_color == RGBAColor(242, 13, 248, 1)) { check_color = getPixel(x, y); }
		std::vector<vec2i> neighbours = { {0,-1}, {1,0}, {0,1}, {-1,0} };

		if ((x > 0 && x < width-1) && (y > 0 && y < height-1)) {
			for (size_t i = 0; i < neighbours.size(); i++) {
				vec2i npos = vec2i(x, y) + neighbours[i];
				RGBAColor back_color = getPixel(npos.x, npos.y);
				if (back_color == check_color) {
					setPixel(npos.x, npos.y, fill_color, true);
					floodFill(npos.x, npos.y, fill_color, check_color);
				}
			}
		}
	}


}; // PixelBuffer


// =========================================================
// helper functions wrap & clamp
inline vec2i wrap(const vec2i& pos, int cols, int rows) {
	vec2i wrapped(pos);

	if (pos.x < 0) { wrapped.x = cols-1; }
	if (pos.x > cols-1) { wrapped.x = 0; }
	if (pos.y < 0) { wrapped.y = rows-1; }
	if (pos.y > rows-1) { wrapped.y = 0; }

	return wrapped;
}

inline vec2i clamp(const vec2i& pos, int cols, int rows) {
	vec2i clamped(pos);

	if (pos.x < 0) { clamped.x = 0; }
	if (pos.x > cols-1) { clamped.x = cols-1; }
	if (pos.y < 0) { clamped.y = 0; }
	if (pos.y > rows-1) { clamped.y = rows-1; }

	return clamped;
}


} // namespace rt

#endif // PIXELBUFFER_H
