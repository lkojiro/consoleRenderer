// hold the class definitions for geometry primitives
#ifndef PRIMITIVES_H
#define PRIMITIVES_H

class Line {
   public:
        bool readyToDraw;
        float x0, y0, z0;
        float x1, y1, z1;

        void toViewport();
        void toCameraView();
};

class Triangle {
    public:
        bool readyToDraw;
        float x0, y0, z0;
        float x1, y1, z1;
        float x2, y2, z2;

        void toViewport();
        void toCameraView();
};

#endif
