// header for screen class
#ifndef SCREEN_H
#define SCREEN_H
#include "primitives.h"
#include "pixel.h"

class Screen {
    private:
        Pixel **buf;

        void plot(int x, int y, float c);

    public:
        int width, height;

        Screen();
        ~Screen();
        void clear();
        void drawLine(Line *l);
        void drawTriangle(Triangle t);
        void refresh();
};

#endif
