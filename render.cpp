// render.cpp
#include <stdio.h>
#include <sys/ioctl.h>
#include <unistd.h>
#include <iostream>
#include <cstdint>
#include <stdlib.h>
#include <time.h>

#include "screen.h"
#include "primitives.h"

using namespace std;

int main() {
    Screen *s = new Screen();
    s->clear();

    Line *l = new Line();
    l->x0 = 0.5;
    l->y0 = 0.5;
    l->z0 = 0;
    
    l->x1 = 40;
    l->y1 = 50;
    l->z1 = 0;

    l->readyToDraw = true;
    s->clear();
    s->drawLine(l);
    s->refresh();
    delete l;

    delete s;
    return 0;
}
