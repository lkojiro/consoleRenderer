#include <sys/ioctl.h>
#include <stdio.h>
#include <iostream>
#include <unistd.h>
#include <math.h>
#include "screen.h"
#include "pixel.h"
#include "primitives.h"

// constructor for screen class
Screen::Screen() {
    struct winsize size;
    // get the size of the terminal
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &size);
    buf = new Pixel*[(size.ws_row*2-2) * size.ws_col];
    width = size.ws_col;
    height = size.ws_row * 2 - 2;
    if (height%2 != 0) {
        height--; // only allow even heights
    }
    for (int j = 0; j < height; j++) {
        for (int i = 0; i < width; i++) {
            buf[j*width + i] = new Pixel();
        }
    }
}

// destructor for screen class
Screen::~Screen() {
    for (int j = 0; j < height; j++) {
        for (int i = 0; i < width; i++) {
            delete buf[j*width + i];
        }
    }
    delete []buf;
}

// replace the screen with blank space
void Screen::clear() {
    for (int j = 0; j < height; j++) {
        for (int i = 0; i < width; i++) {
            Pixel *p = buf[j*width + i];
            p->setColorData((uint8_t)0,(uint8_t)0,(uint8_t)0,(uint8_t)0);
        }
    }
}

//plot at point x,y with brightness c (0 <= c <= 1)
void Screen::plot(int x, int y, float c) {
    int alpha = int(c*255);
    buf[y*width + x]->setColorData(alpha, alpha, alpha, alpha);
}

// integer part of x
int ipart(float x) {
    return floor(x);
}

// round x down
int roundDown(float x) {
    return ipart(x + 0.5);
}

// fractional part of x
float fpart(float x) {
    return x - floor(x);
}

// remainder of fractional part of x
float rfpart(float x) {
    return 1 - fpart(x);
}

/* take a line in viewport coordinates
 * and rasterize it to the frame buffer
 * (Xiaolin Wu's algorithm)
 */
void Screen::drawLine(Line *l) {
    if (!(l->readyToDraw)) {
        return;
    }
    float x0 = l->x0;
    float x1 = l->x1;
    float y0 = l->y0;
    float y1 = l->y1;

    bool steep = abs(y1 - y0) > abs(x1 - x0);
    
    //draw in the correct direction
    if (steep) {
        std::swap(x0, y0);
        std::swap(x1, y1);
    }
    if (x0 > x1) {
        std::swap(x0, x1);
        std::swap(y0, y1);
    }

    float dx = x1 - x0;
    float dy = y1 - y0;
    float gradient;
    
    if (dx == 0.f) {
        gradient = 1.0;
    }
    else {
        gradient = dy / dx;
    }

    // first endpoint
    int xend = round(x0);
    float yend = y0 + gradient * (xend - x0);
    float xgap = rfpart(x0 + 0.5);
    int xpxl1 = xend;
    int ypxl1 = ipart(yend);

    if (steep) {
        this->plot(ypxl1, xpxl1, rfpart(yend) * xgap);
        this->plot(ypxl1 + 1, xpxl1, fpart(yend) * xgap);
    }
    else {
        this->plot(xpxl1, ypxl1, rfpart(yend) * xgap);
        this->plot(xpxl1, ypxl1 + 1, fpart(yend) * xgap);
    }
    float intery = yend + gradient;

    // second endpoint
    xend = round(x1);
    yend = y1 + gradient * (xend - x1);
    xgap = fpart(x1 + 0.5);
    int xpxl2 = xend;
    int ypxl2 = ipart(yend);

    if (steep) {
        this->plot(ypxl2, xpxl2, rfpart(yend) * xgap);
        this->plot(ypxl2 + 1, xpxl2, fpart(yend) * xgap);
    }
    else {
        this->plot(xpxl2, ypxl2, rfpart(yend) * xgap);
        this->plot(xpxl2, ypxl2 + 1, fpart(yend) * xgap);
    }

    //main drawing loop
    if (steep) {
        for (int x = xpxl1 + 1; x < xpxl2; x ++) {
            this->plot(ipart(intery), x, rfpart(intery));
            this->plot(ipart(intery) + 1, x, fpart(intery));
            intery = intery + gradient;
        }
    }
    else {
        for (int x = xpxl1 + 1; x < xpxl2; x ++) {
            this->plot(x, ipart(intery), rfpart(intery));
            this->plot(x, ipart(intery), fpart(intery));
            intery = intery + gradient;
        }
    }
}

/* take a triangle in viewport coordinates
 * and rasterize it to the frame buffer
 */
void Screen::drawTriangle(Triangle t) {
    //TODO
}

/* re-draw the screen by outputing the buffer
 * to cout
 */
void Screen::refresh() {
    // draw the rows two at a time because each
    // character is two pixels
    for (int j=0; j < height; j+=2) {
        for (int i=0; i < width; i++) {
            Pixel *top = buf[j*width + i];
            Pixel *bot = buf[(j+1)*width + i];
            int topColor = top->getEscapeColor();
            int botColor = bot->getEscapeColor();
            printf("\033[38;5;%dm\033[48;5;%dm%s\033[0m", topColor, botColor, "▀");
        }
        printf("\n");
    }
    
}
