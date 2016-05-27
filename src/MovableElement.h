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
    virtual ~MovableElement() = 0;

    void setMvtx(int mvtx);
    void setMvty(int mvty);
    void changeDirection(direction d);
    int getMvtx() const;
    int getMvty() const;
    sf::Vector2f getPos() const;
    int getPosx() const;
    int getPosy() const;
    int getWidth() const;
    int getHeight() const;
    direction getDirection() const;

    void move();
};

#endif // MOVABLEELEMENT_H
