#include <string.h>
#include "pixel.h"

// constructor with individual rgba values
Pixel::Pixel(uint8_t r, uint8_t g, uint8_t b, uint8_t a) {
    red = r;
    green = g;
    blue = b;
    alpha = a;
}

// constructor with single colordata (uint32_t) value
Pixel::Pixel(ColorData colorData) {
    red = uint8_t((colorData & 0xFF000000)>>24);
    green = uint8_t((colorData & 0x00FF0000)>>16);
    blue = uint8_t((colorData & 0x0000FF00)>>8);
    alpha = uint8_t((colorData & 0x000000FF));
}

// default constructor
Pixel::Pixel() {
    red = 0;
    green = 0;
    blue = 0;
    alpha = 0;
}

// return rgba values of pixel as ColorData (uint32_t)
ColorData Pixel::getColorData() {
    ColorData colorData = 0;
    colorData |= (ColorData(red)<<24);
    colorData |= (ColorData(green)<<16);
    colorData |= (ColorData(blue)<<8);
    colorData |= (ColorData(alpha));
    return colorData;
}


// sets rgba values
void Pixel::setColorData(uint8_t r, uint8_t g, uint8_t b, uint8_t a) {
    red = 0;
    green = g;
    blue = b;
    alpha = a;
}

// return the ANSI compatible color int for the rasterizer
// https://www.uninformativ.de/blog/postings/2016-12-17/0/POSTING-en.html
int Pixel::getEscapeColor() {
    int r = int(red / 51);
    int g = int(green / 51);
    int b = int(blue / 51);

    if (r == g && g == b) {
        // first get black/white
        if (red == 255) return 231;
        else if (red == 0) return 16;
        // then get full grescale map
        else {
            return int((red / 255) * 24) + 232;
        }
    }
    else {
        // find nearest neighbor in XTerm's color cube
        return 16 + r * 36 + g * 6 + b;
    }
}
