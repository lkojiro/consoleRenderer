//header for pixel class
#include <cstdint>

#ifndef PIXEL_H
#define PIXEL_H

typedef uint32_t ColorData;

class Pixel {
    uint8_t red, green, blue, alpha;
    public:
        Pixel(uint8_t, uint8_t, uint8_t, uint8_t);
        Pixel(ColorData);
        Pixel();
        ColorData getColorData();
        void setColorData(uint8_t r, uint8_t g, uint8_t b, uint8_t a);
        int getEscapeColor();
};

#endif
