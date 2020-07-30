// render.cpp
#include <stdio.h>
#include <sys/ioctl.h>
#include <unistd.h>
#include <iostream>
#include <cstdint>

using namespace std;

typedef struct pixel {
    uint8_t red;
    uint8_t green;
    uint8_t blue;
    uint8_t alpha;
} Pixel;

void clearBuffer(char *buf, int width, int height) {
    for (int j = 0; j < height; j++) {
        for (int i = 0; i < width; i++) {
            buf[j*width + i] = ' ';
        }
        buf[j*width + width] = '\n';
    }
}

void drawPixel(char *buf, char fill, int width, int height, int x, int y) {
    buf[y*width + x] = fill;
}

void drawScreen(char *buf, int width, int height) {
    for (int i = 0; i < (width*height); i++) {
        cout << buf[i];
    }
}
void clearScreen(int height) {
    cout << string(height, '\n');
}

int main() {
    struct winsize size;
    char *buf;
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &size);
    //cout << "Rows: " << size.ws_row << endl;
    //cout << "Cols: " << size.ws_col << endl;
    clearScreen(size.ws_row);
    buf = new char[(size.ws_row-2) * size.ws_col];
    clearBuffer(buf, size.ws_col, size.ws_row-2);
    drawPixel(buf, '0', size.ws_col, size.ws_row, 1, 0);
    drawPixel(buf, '1', size.ws_col, size.ws_row, 1, 1);
    drawPixel(buf, '2', size.ws_col, size.ws_row, 1, 2);
    drawPixel(buf, '#', size.ws_col, size.ws_row, size.ws_col-1, size.ws_row-3);
    drawScreen(buf, 
    cout << buf << endl;
    sleep(8);
    delete [] buf;
    return 0;
}
