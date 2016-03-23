#include "SlidingBackground.h"

SlidingBackground::SlidingBackground()
{

}

SlidingBackground::SlidingBackground(int w, int h, int s)
    : _width {w}, _height {h}, _speed {s}
{
    _right.setPosition(sf::Vector2f(_width, 0));
    _left.setPosition(sf::Vector2f(0, 0));
}

SlidingBackground::SlidingBackground(int posx, int posy, int w, int h, int s)
    : _width {w}, _height {h}, _speed {s}
{
    _right.setPosition(sf::Vector2f(_width, posy));
    _left.setPosition(sf::Vector2f(posx, posy));
}

//========================================
//========================================

void SlidingBackground::move()
{
    if(_left.getPosition().x <= -SCREEN_WIDTH)
        _left.setPosition(sf::Vector2f(_width - 5, 0));

    else if(_right.getPosition().x <= -SCREEN_WIDTH)
        _right.setPosition(sf::Vector2f(_width - 5 , 0));

    else
    {
        _left.move(-_speed, 0);
        _right.move(-_speed, 0);
    }
}

bool SlidingBackground::loadTextures(std::string left, std::string right)
{
    if(!_leftTexture.loadFromFile(left))
        return false;

    else if(!_rightTexture.loadFromFile(right))
        return false;

    else
    {
        _left.setTexture(_leftTexture);
        _right.setTexture(_rightTexture);
        return true;
    }

}

void SlidingBackground::draw(sf::RenderWindow *window)
{
    window->draw(_left);
    window->draw(_right);
}
