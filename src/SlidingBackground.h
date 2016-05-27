#ifndef SLIDINGBACKGROUND_H
#define SLIDINGBACKGROUND_H
#include <SFML/Graphics.hpp>
#include "main.h"


class SlidingBackground
{
protected:
    sf::Sprite _leftBig; // Sprite 1
    sf::Sprite _rightBig; // Sprite 2
    sf::Texture _leftTextureBig;
    sf::Texture _rightTextureBig;

    sf::Sprite _leftLittle; // Sprite 1 qui suit
    sf::Sprite _rightLittle; // Sprite 2 qui suit
    sf::Texture _leftTextureLittle;
    sf::Texture _rightTextureLittle;

    int _width;
    int _height;
    int _speedBig;
    int _speedLittle;
    int _posx;
    int _posy;


public:
    SlidingBackground();
    SlidingBackground(int w, int h, int sB, int sL);
    SlidingBackground(int posx, int posy, int w, int h, int sB, int sL);

    void move();
    bool loadTextures(std::string leftBig, std::string rightBig, std::string leftLittle, std::string rightLittle);
    void draw(sf::RenderWindow* window);
    void reset();
};

#endif // SLIDINGBACKGROUND_H
