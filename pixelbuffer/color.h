/**
 * @file color.h
 *
 * @brief RGBA / HSVA Color: pb::RGBAColor
 *
 * Copyright 2015-2022 @rktrlng
 * https://github.com/rktrlng/pixelbuffer
 */

#ifndef COLOR_H_
#define COLOR_H_

#include <cstdint>
#include <algorithm>
#include <cmath>
#include <vector>

namespace pb {

/// @brief A 32 bit RGBA color.
///
/// A struct that defines an RGBA Color. Each value is a uint8_t (0-255).
struct RGBAColor
{
	/// @brief The red component of the color
	uint8_t r = 255;
	/// @brief The green component of the color
	uint8_t g = 255;
	/// @brief The blue component of the color
	uint8_t b = 255;
	/// @brief The alpha component of the color
	uint8_t a = 255;

	/// @brief constructor
	RGBAColor() {
		r = 255;
		g = 255;
		b = 255;
		a = 255;
	}
	/// @brief constructor
	/// @param red The red component of the color
	/// @param green The green component of the color
	/// @param blue The blue component of the color
	/// @param alpha The alpha component of the color
	RGBAColor(uint8_t red, uint8_t green, uint8_t blue, uint8_t alpha) {
		r = red;
		g = green;
		b = blue;
		a = alpha;
	}
	/// @brief constructor
	/// @param red The red component of the color
	/// @param green The green component of the color
	/// @param blue The blue component of the color
	RGBAColor(uint8_t red, uint8_t green, uint8_t blue) {
		r = red;
		g = green;
		b = blue;
		a = 255;
	}
	/// @brief constructor
	/// @param color The color as a 32 bits int
	RGBAColor(uint32_t color) {
		r = color >> 24 & 0xFF;
		g = color >> 16 & 0xFF;
		b = color >> 8 & 0xFF;
		a = color & 0xFF;
	}
	/// @brief get color as a uint32_t
	/// @return uint32_t color as a 32 bits int
	uint32_t asInt() {
		uint32_t color = (r << 24) + (g << 16) + (b << 8) + (a);
		return color;
	}
	/// @brief == operator overloader
	/// @param rhs the color to compare against
	/// @return bool equal or not
	inline bool operator==(const RGBAColor& rhs) {
		return ( r == rhs.r && g == rhs.g && b == rhs.b && a == rhs.a );
	}
	/// @brief != operator overloader
	/// @param rhs the color to compare against
	/// @return bool equal or not
	inline bool operator!=(const RGBAColor& rhs) {
		return !(*this == rhs);
	}

	/// @brief [] operator overloader
	/// @param index the index of the rgba color component
	/// @return uint8_t& rgba color component
	inline uint8_t& operator[](size_t index) {
		if (index == 0) { return r; }
		if (index == 1) { return g; }
		if (index == 2) { return b; }
		if (index == 3) { return a; }
		return r;
	}
};
inline std::ostream& operator<<(std::ostream& os, const RGBAColor& color) {
	return os << "(" << (int)color.r << ", " << (int)color.g << ", " << (int)color.b << ", " << (int)color.a << ")";
}


/// @brief A 24 bit HSV color.
///
/// A struct that defines an HSV Color (Hue, Saturation, Brightness). Each value is a float between 0.0f and 1.0f.
struct HSVAColor
{
	/// @brief The Hue component of the color
	float h = 0.0f;
	/// @brief The Saturation component of the color
	float s = 0.0f;
	/// @brief The Lightness/Brightness/Value component of the color
	float v = 1.0f;
	/// @brief The Alpha component of the color
	float a = 1.0f;

	/// @brief constructor
	HSVAColor() {
		h = 0.0f;
		s = 0.0f;
		v = 1.0f;
		a = 1.0f;
	}
	/// @brief constructor
	/// @param hue The hue component of the color
	/// @param sat The saturation component of the color
	/// @param val The brightness/lightness/value component of the color
	HSVAColor(float hue, float sat, float val, float alpha = 1.0f) {
		h = hue;
		s = sat;
		v = val;
		a = alpha;
	}
	/// @brief [] operator overloader
	/// @param index the index of the hsva color component
	/// @return float& hsva color component
	inline float& operator[](size_t index) {
		if (index == 0) { return h; }
		if (index == 1) { return s; }
		if (index == 2) { return v; }
		if (index == 3) { return a; }
		return h;
	}
};
inline std::ostream& operator<<(std::ostream& os, const HSVAColor& color) {
	return os << "(" << color.h << ", " << color.s << ", " << color.v << ", " << color.a << ")";
}


/// @brief HSV <-> RGBA conversion
struct Color
{
	// http://www.easyrgb.com/index.php?X=MATH&H=20#text20
	/// @brief RGBA to HSV conversion
	/// @param rgba the RGBAColor to convert
	/// @return return converted HSVAColor color
	static HSVAColor RGBA2HSVA(RGBAColor rgba) {
		float var_R = (float) rgba.r / 255; //RGB from 0 to 255
		float var_G = (float) rgba.g / 255;
		float var_B = (float) rgba.b / 255;
		float var_A = (float) rgba.a / 255;

		float var_Min = std::min( std::min( var_R, var_G), var_B ); // Min. value of RGB
		float var_Max = std::max( std::max( var_R, var_G), var_B ); // Max. value of RGB
		float del_Max = var_Max - var_Min; // Delta RGB value

		float H = 0.0f;
		float S = 0.0f;
		float V = var_Max;
		float A = var_A;

		if ( del_Max == 0 ) { //This is a gray, no chroma...
			H = 0; // HSV results from 0 to 1
			S = 0;
		} else { //Chromatic data...
			S = del_Max / var_Max;

			float del_R = ( ( ( var_Max - var_R ) / 6.0f ) + ( del_Max / 2.0f ) ) / del_Max;
			float del_G = ( ( ( var_Max - var_G ) / 6.0f ) + ( del_Max / 2.0f ) ) / del_Max;
			float del_B = ( ( ( var_Max - var_B ) / 6.0f ) + ( del_Max / 2.0f ) ) / del_Max;

			if      ( var_R == var_Max ) H = del_B - del_G;
			else if ( var_G == var_Max ) H = ( 1.0f / 3.0f ) + del_R - del_B;
			else if ( var_B == var_Max ) H = ( 2.0f / 3.0f ) + del_G - del_R;

			if ( H < 0.0f ) H += 1.0f;
			if ( H > 1.0f ) H -= 1.0f;
		}
		return HSVAColor(H, S, V, A);
	}


	// http://www.easyrgb.com/index.php?X=MATH&H=21#text21
	/// @brief HSVA to RGBA conversion
	/// @param hsva the HSVAColor to convert
	/// @return return converted RGBAColor color
	static RGBAColor HSVA2RGBA(HSVAColor hsva) {
		uint8_t R = 0;
		uint8_t G = 0;
		uint8_t B = 0;
		uint8_t A = hsva.a * 255;
		if ( hsva.s == 0 ) { //HSV from 0 to 1
			R = hsva.v * 255;
			G = hsva.v * 255;
			B = hsva.v * 255;
		} else {
			float var_h = hsva.h * 6;
			if ( var_h >= 6.0f ) { var_h = 0; } //H must be < 1
			int var_i = int( var_h ); //Or ... var_i = floor( var_h )
			float var_1 = hsva.v * ( 1.0f - hsva.s );
			float var_2 = hsva.v * ( 1.0f - hsva.s * ( var_h - var_i ) );
			float var_3 = hsva.v * ( 1.0f - hsva.s * ( 1.0f - ( var_h - var_i ) ) );
			float var_r;
			float var_g;
			float var_b;
			if      ( var_i == 0 ) { var_r = hsva.v ; var_g = var_3 ; var_b = var_1 ; }
			else if ( var_i == 1 ) { var_r = var_2 ; var_g = hsva.v ; var_b = var_1 ; }
			else if ( var_i == 2 ) { var_r = var_1 ; var_g = hsva.v ; var_b = var_3 ; }
			else if ( var_i == 3 ) { var_r = var_1 ; var_g = var_2 ; var_b = hsva.v ; }
			else if ( var_i == 4 ) { var_r = var_3 ; var_g = var_1 ; var_b = hsva.v ; }
			else                   { var_r = hsva.v ; var_g = var_1 ; var_b = var_2 ; }

			R = var_r * 255; //RGB results from 0 to 255
			G = var_g * 255;
			B = var_b * 255;
		}
		return RGBAColor(R, G, B, A);
	}


	/// @brief Rotate RGBA color (use HSV)
	/// @param rgba the RGBAColor to rotate
	/// @param step amount to rotate
	/// @return return RGBAColor rotated color
	static RGBAColor rotate(RGBAColor rgba, float step) {
		HSVAColor hsva = RGBA2HSVA(rgba);
		hsva.h += step;
		if (hsva.h > 1.0f) { hsva.h -= 1.0f; }
		if (hsva.h < 0.0f) { hsva.h += 1.0f; }
		return HSVA2RGBA(hsva);
	}


	/// @brief lerp from color to another color
	/// @param c1 first RGBAColor
	/// @param c2 second RGBAColor
	/// @param amount between 0 and 1
	/// @return return RGBAColor lerped color
	static RGBAColor lerpColor(RGBAColor c1, RGBAColor c2, float amount) {
		if (amount < 0) { amount = 0; }
		if (amount > 1) { amount = 1; }

		uint8_t r = floor(c1.r + (c2.r-c1.r)*amount);
		uint8_t g = floor(c1.g + (c2.g-c1.g)*amount);
		uint8_t b = floor(c1.b + (c2.b-c1.b)*amount);
		uint8_t a = floor(c1.a + (c2.a-c1.a)*amount);

		return RGBAColor(r, g, b, a);
	}


	// https://stackoverflow.com/questions/28900598/how-to-combine-two-colors-with-varying-alpha-values
	// https://en.wikipedia.org/wiki/Alpha_compositing#Alpha_blending
	/// @brief blend an alpha color over an alpha color
	/// @param top top RGBAColor
	/// @param bottom bottom RGBAColor
	/// @return return RGBAColor blended color
	static RGBAColor alphaBlend(RGBAColor top, RGBAColor bottom) {
		// if we want to overlay top(0) over bottom(1) both with some alpha then:

		// uint8_t 0-255 to float 0.0-1.0
		float r0 = top.r / 255.0f;
		float g0 = top.g / 255.0f;
		float b0 = top.b / 255.0f;
		float a0 = top.a / 255.0f;

		float r1 = bottom.r / 255.0f;
		float g1 = bottom.g / 255.0f;
		float b1 = bottom.b / 255.0f;
		float a1 = bottom.a / 255.0f;

		// Note the division by a01 in the formulas for the components of color. It's important.
		float a01 =  (1 - a0) * a1 + a0;
		float r01 = ((1 - a0) * a1 * r1 + a0 * r0) / a01;
		float g01 = ((1 - a0) * a1 * g1 + a0 * g0) / a01;
		float b01 = ((1 - a0) * a1 * b1 + a0 * b0) / a01;

		uint8_t r = r01 * 255;
		uint8_t g = g01 * 255;
		uint8_t b = b01 * 255;
		uint8_t a = a01 * 255;

		return pb::RGBAColor(r, g, b, a);
	}

	/// @brief uint8_t to vector of 8 colors
	/// most significant bit is colors[0]
	/// least significant bit is colors[7]
	/// @param value 8 bit value to convert
	/// @return vector of RGBAColors 
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

	/// @brief vector of 8 colors to uint8_t
	/// most significant bit is colors[0]
	/// least significant bit is colors[7]
	/// @param colors vector of colors to convert
	/// @return value as uint8_t
	static uint8_t vec2byte(const std::vector<RGBAColor>& colors) {
		size_t size = colors.size();
		if (size != 8) { return 0; }
		uint8_t value = 0;
		for (size_t i = 0; i < size; i++) {
			if (colors[i].r == 0 && colors[i].g == 0 && colors[i].b == 0 ) { // black
				value &= ~(1 << (7-i)); // 0 on this bit
			} else { // white (not black)
				value |=  (1 << (7-i)); // 1 on this bit
			}
		}
		return value;
	}

};


#define BLACK   pb::RGBAColor(0,   0,   0,   255) ///< @brief color black
#define GRAY    pb::RGBAColor(127, 127, 127, 255) ///< @brief color gray
#define RED     pb::RGBAColor(255, 0,   0,   255) ///< @brief color red
#define ORANGE  pb::RGBAColor(255, 127, 0,   255) ///< @brief color orange
#define YELLOW  pb::RGBAColor(255, 255, 0,   255) ///< @brief color yellow
#define GREEN   pb::RGBAColor(0,   255, 0,   255) ///< @brief color green
#define CYAN    pb::RGBAColor(0,   255, 255, 255) ///< @brief color cyan
#define BLUE    pb::RGBAColor(0,   0,   255, 255) ///< @brief color blue
#define MAGENTA pb::RGBAColor(255, 0,   255, 255) ///< @brief color magenta
#define PURPLE  pb::RGBAColor(127, 0,   127, 255) ///< @brief color purple
#define PINK    pb::RGBAColor(255, 127, 255, 255) ///< @brief color pink
#define WHITE   pb::RGBAColor(255, 255, 255, 255) ///< @brief color white

} // namespace pb

#endif /* COLOR_H_ */
