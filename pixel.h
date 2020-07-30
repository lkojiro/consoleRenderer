//header for pixel primitive
#ifndef PIXEL_H
#define PIXEL_H

typedef ColorData uint32_t;

// paulbourke.net/dataformats/asciiart
const char *BRIGHTNESS = " .:-=+*#%@";
const char *EXTENDED_BRIGHTNESS = "$@B%8&WM#*oahkbdpqwmZO0QLCJUYXzcvunxrjft/\|()1{}[]?-_+~<>i!lI;:,"^`'. ";
class Pixel {
    uint8_t red, green, blue, alpha;
    public:
        Pixel(uint8_t, uint8_t, uint8_t, uint8_t);
        Pixel(uint64_t);
        Pixel();
        ColorData getColorData();
};

#endif
