#ifndef MOVABLEELEMENT_H
#define MOVABLEELEMENT_H7
#include "main.h"


class MovableElement
{
protected:
    int _posx;
    int _posy;
    int _width;
    int _height;
    int _mvtx;
    int _mvty;
    direction dir;

public:
    MovableElement();
    MovableElement(int posx, int posy, int width, int height, int mvtx, int mvty);
    ~MovableElement();

        void setMvtx(int mvtx);
        void setMvty(int mvty);

        int getPosx() const;
        int getPosy() const;
        int getMvtx() const;
        int getMvty() const;
        int getWidth() const;
        int getHeight() const;
        direction getDirection() const;

        void changeDirection(direction d);
        void move();
};

#endif // MOVABLEELEMENT_H
