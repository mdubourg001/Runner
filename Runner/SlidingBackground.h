#ifndef SLIDINGBACKGROUND_H
#define SLIDINGBACKGROUND_H
#include <SFML/Graphics.hpp>
#include "main.h"


class SlidingBackground
{
protected:
    sf::Sprite _left;
    sf::Sprite _right;
    sf::Texture _leftTexture;
    sf::Texture _rightTexture;
    int _height;
    int _width;
    int _posx;
    int _posy;
    int _speed;
public:
    SlidingBackground();
    SlidingBackground(int w, int h, int s);

    void move();
    bool loadTextures(std::string left, std::string right);
    void draw(sf::RenderWindow* window);

};

#endif // SLIDINGBACKGROUND_H
