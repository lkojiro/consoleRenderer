#include "pixel.h"

//constructor with individual rgba values
Pixel::Pixel(uint8_t r, uint8_t g, uint8_t b, uint8_t a) {
    red = r;
    green = g;
    blue = b;
    alpha = a;
}

//constructor with single colordata (uint32_t) value
Pixel::Pixel(ColorData colorData) {
    red = uint8_t((colorData & 0xFF000000)>>24);
    green = uint8_t((colorData & 0x00FF0000)>>16);
    blue = uint8_t((colorData & 0x0000FF00)>>8);
    alpha = uint8_t((colorData & 0x000000FF));
}

//default constructor
Pixel::Pixel() {
    red = 0;
    green = 0;
    blue = 0;
    alpha = 0;
}

//return rgba values of pixel as ColorData (uint32_t)
Pixel::getColorData() {
    ColorData colorData;
    colorData | (ColorData(red)<<24);
    colorData | (ColorData(green)<<16);
    colorData | (ColorData(blue)<<8);
    colorData | (ColorData(alpha));
    return colorData;
}
