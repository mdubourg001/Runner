#ifndef CUBE_H
#define CUBE_H
#include "main.h"
#include <iostream>

class Cube : sf::Sprite
{
protected:
    int _color; //1->red 2->blue 3->green 4->yellow 5->purple
    sf::Texture _texture;
public:
    Cube();
    Cube(int color, int stage);

    void setColor(int color);
    void draw(sf::RenderWindow* w);
    void move(int movespeed);
};

#endif // CUBE_H
