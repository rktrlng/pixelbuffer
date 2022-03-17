/**
 * @file color.h
 *
 * @brief RGBA / HSVA Color: RGBAColor
 *
 * Copyright 2015-2022 @rktrlng
 * https://github.com/rktrlng/pixelbuffer
 */

#ifndef COLOR_H_
#define COLOR_H_

#define  _USE_MATH_DEFINES
#include <cmath>
#include <algorithm>

#include <pixelbuffer/math/vec4.h>

namespace rt {

// ###############################################
// # Data Types                                  #
// ###############################################

/// @brief A 32 bit RGBA color (Red, Green, Blue, Alpha). Each value is a uint8_t (0-255).
class RGBAColor : public vec4_t<uint8_t>
{
public:
	/// @brief constructor
	RGBAColor() : vec4_t<uint8_t>(255, 255, 255, 255) { }

	/// @brief 24/32 bit constructor
	/// @param red The red component of the color
	/// @param green The green component of the color
	/// @param blue The blue component of the color
	/// @param alpha The alpha component of the color
	RGBAColor(uint8_t red, uint8_t green, uint8_t blue, uint8_t alpha = 255) : vec4_t<uint8_t>(red, green, blue, alpha) { }

	/// @brief 8/16 bit constructor
	/// @param gray The gray component of the color
	/// @param alpha The alpha component of the color
	RGBAColor(uint8_t gray, uint8_t alpha = 255) : vec4_t<uint8_t>(gray, gray, gray, alpha) { }

	/// @brief fromInt static 'constructor'
	/// @param color The color as a 32 bits int
	/// @return RGBAColor from int
	static RGBAColor fromInt(uint32_t color) {
		uint8_t r = color >> 24 & 0xFF;
		uint8_t g = color >> 16 & 0xFF;
		uint8_t b = color >> 8 & 0xFF;
		uint8_t a = color & 0xFF;
		return RGBAColor(r, g, b, a);
	}

	/// @brief get color as a uint32_t
	/// @return uint32_t color as a 32 bits int
	uint32_t asInt() const {
		uint32_t color = (r << 24) + (g << 16) + (b << 8) + (a);
		return color;
	}
};

/// @brief A 32 bit HSV color (Hue, Saturation, Brightness, Alpha). Each value is a float between 0.0f and 1.0f.
class HSVAColor : public vec4_t<float>
{
public:
	/// @brief constructor
	HSVAColor() : vec4_t<float>(0.0f, 0.0f, 1.0f, 1.0f) { }
	/// @brief constructor
	/// @param hue The hue component of the color
	/// @param sat The saturation component of the color
	/// @param val The brightness/lightness/value component of the color
	/// @param alpha The alpha component of the color
	HSVAColor(float hue, float sat, float val, float alpha = 1.0f) : vec4_t<float>(hue, sat, val, alpha)  { }
};


// ###############################################
// # Converters                                  #
// ###############################################

// http://www.easyrgb.com/index.php?X=MATH&H=20#text20
/// @brief RGBA to HSVA conversion
/// @param rgba the RGBAColor to convert
/// @return return converted HSVAColor color
inline HSVAColor RGBA2HSVA(const RGBAColor& rgba) {
	float var_R = (float) rgba.r / 255; //RGB from 0 to 255
	float var_G = (float) rgba.g / 255;
	float var_B = (float) rgba.b / 255;
	float var_A = (float) rgba.a / 255;

	float var_Min = std::min( std::min(var_R, var_G), var_B ); // Min. value of RGB
	float var_Max = std::max( std::max(var_R, var_G), var_B ); // Max. value of RGB
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

		float del_R = (((var_Max - var_R) / 6.0f) + (del_Max / 2.0f)) / del_Max;
		float del_G = (((var_Max - var_G) / 6.0f) + (del_Max / 2.0f)) / del_Max;
		float del_B = (((var_Max - var_B) / 6.0f) + (del_Max / 2.0f)) / del_Max;

		if      (var_R == var_Max) H = del_B - del_G;
		else if (var_G == var_Max) H = (1.0f / 3.0f) + del_R - del_B;
		else if (var_B == var_Max) H = (2.0f / 3.0f) + del_G - del_R;

		if (H < 0.0f) H += 1.0f;
		if (H > 1.0f) H -= 1.0f;
	}
	return HSVAColor(H, S, V, A);
}

// http://www.easyrgb.com/index.php?X=MATH&H=21#text21
/// @brief HSVA to RGBA conversion
/// @param hsva the HSVAColor to convert
/// @return return converted RGBAColor color
inline RGBAColor HSVA2RGBA(const HSVAColor& hsva) {
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
		if (var_h >= 6.0f) { var_h = 0; } //H must be < 1
		int var_i = int( var_h ); //Or ... var_i = floor( var_h )
		float var_1 = hsva.v * ( 1.0f - hsva.s );
		float var_2 = hsva.v * ( 1.0f - hsva.s * ( var_h - var_i ) );
		float var_3 = hsva.v * ( 1.0f - hsva.s * ( 1.0f - ( var_h - var_i ) ) );
		float var_r;
		float var_g;
		float var_b;
		if      (var_i == 0) { var_r = hsva.v; var_g = var_3;  var_b = var_1; }
		else if (var_i == 1) { var_r = var_2;  var_g = hsva.v; var_b = var_1; }
		else if (var_i == 2) { var_r = var_1;  var_g = hsva.v; var_b = var_3; }
		else if (var_i == 3) { var_r = var_1;  var_g = var_2;  var_b = hsva.v; }
		else if (var_i == 4) { var_r = var_3;  var_g = var_1;  var_b = hsva.v; }
		else                 { var_r = hsva.v; var_g = var_1;  var_b = var_2; }

		R = var_r * 255; //RGB results from 0 to 255
		G = var_g * 255;
		B = var_b * 255;
	}
	return RGBAColor(R, G, B, A);
}


// ###############################################
// # Helpers                                     #
// ###############################################

/// @brief Rotate RGBA color (use HSV)
/// @param rgba the RGBAColor to rotate
/// @param step amount to rotate
/// @return return RGBAColor rotated color
inline RGBAColor rotate(const RGBAColor& rgba, float step) {
	HSVAColor hsva = RGBA2HSVA(rgba);
	hsva.h += step;
	if (hsva.h > 1.0f) { hsva.h -= 1.0f; }
	if (hsva.h < 0.0f) { hsva.h += 1.0f; }
	return HSVA2RGBA(hsva);
}

// https://stackoverflow.com/questions/28900598/how-to-combine-two-colors-with-varying-alpha-values
// https://en.wikipedia.org/wiki/Alpha_compositing#Alpha_blending
/// @brief blend an alpha color over an alpha color
/// @param top top RGBAColor
/// @param bottom bottom RGBAColor
/// @return return RGBAColor blended color
inline RGBAColor alphaBlend(const RGBAColor& top, const RGBAColor& bottom) {
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

	return RGBAColor(r, g, b, a);
}

/// @brief quantize a color (find closest palette color)
/// @param rgba the color to quantize
/// @param factor number of palette colors. default 1 for 2 colors (eg. black/white)
/// @return return RGBAColor quatized color
inline RGBAColor quantize(const RGBAColor& rgba, int factor = 1) {
	float r = (float)rgba.r;
	float g = (float)rgba.g;
	float b = (float)rgba.b;

	uint8_t nr = round(factor * r / 255) * (255.0f / factor);
	uint8_t ng = round(factor * g / 255) * (255.0f / factor);
	uint8_t nb = round(factor * b / 255) * (255.0f / factor);

	return RGBAColor(nr, ng, nb, rgba.a);
}

/// @brief returns negative version of rgba color
/// @param rgba the color to invert
/// @return return RGBAColor negative color
inline RGBAColor negative(const RGBAColor& rgba) {
	return RGBAColor(255-rgba.r, 255-rgba.g, 255-rgba.b, rgba.a);
}

/// @brief convert rgba color to average grayscale
/// @param rgba the color to convert
/// @return return RGBAColor average grayscale color
inline RGBAColor average(const RGBAColor& rgba) {
	uint8_t avg = (rgba.r + rgba.g + rgba.b) / 3;
	return RGBAColor(avg, rgba.a);
}

/// @brief convert rgba color to luminance value
/// @param rgba the color to convert
/// @return return RGBAColor luminance color
inline RGBAColor luminance(const RGBAColor& rgba) {
	uint8_t lum = rgba.r * 0.3f + rgba.g * 0.59f + rgba.b * 0.11f;
	return RGBAColor(lum, rgba.a);
}


#define BLACK       rt::RGBAColor(0,   0,   0,   255) ///< @brief color black
#define GRAY        rt::RGBAColor(127, 127, 127, 255) ///< @brief color gray
#define RED         rt::RGBAColor(255, 0,   0,   255) ///< @brief color red
#define ORANGE      rt::RGBAColor(255, 127, 0,   255) ///< @brief color orange
#define YELLOW      rt::RGBAColor(255, 255, 0,   255) ///< @brief color yellow
#define GREEN       rt::RGBAColor(0,   255, 0,   255) ///< @brief color green
#define CYAN        rt::RGBAColor(0,   255, 255, 255) ///< @brief color cyan
#define BLUE        rt::RGBAColor(0,   0,   255, 255) ///< @brief color blue
#define MAGENTA     rt::RGBAColor(255, 0,   255, 255) ///< @brief color magenta
#define PURPLE      rt::RGBAColor(127, 0,   127, 255) ///< @brief color purple
#define PINK        rt::RGBAColor(255, 127, 255, 255) ///< @brief color pink
#define WHITE       rt::RGBAColor(255, 255, 255, 255) ///< @brief color white
#define TRANSPARENT rt::RGBAColor(0,   0,   0,   0  ) ///< @brief color transparent

} // namespace rt

#endif /* COLOR_H_ */
