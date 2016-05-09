#include "SlidingBackground.h"

SlidingBackground::SlidingBackground(int posx, int posy, int w, int h, int sB, int sL)
    : _width {w}, _height {h}, _speedBig {sB}, _speedLittle{sL}, _posx{posx}, _posy{posy}
{
    _rightBig.setPosition(sf::Vector2f(_posx + _width -5 , posy));
    _leftBig.setPosition(sf::Vector2f(posx, posy));

    _rightLittle.setPosition(sf::Vector2f(_posx + _width - 5 , posy));
    _leftLittle.setPosition(sf::Vector2f(posx, posy));
}

//========================================
//========================================

void SlidingBackground::move() //gestion du défilement paralaxe
{
    if(_leftBig.getPosition().x <= _posx -_width)
        _leftBig.setPosition(sf::Vector2f(_posx + _width - 5, _posy));

    else if(_rightBig.getPosition().x <= _posx -_width)
        _rightBig.setPosition(sf::Vector2f(_posx + _width - 5, _posy));

    else
    {
        _leftBig.move(-_speedBig, 0);
        _rightBig.move(-_speedBig, 0);
    }

    if(_leftLittle.getPosition().x <= _posx -_width)
        _leftLittle.setPosition(sf::Vector2f(_posx + _width -5, _posy));

    else if(_rightLittle.getPosition().x <= _posx -_width)
        _rightLittle.setPosition(sf::Vector2f(_posx + _width -5, _posy));

    else
    {
        _leftLittle.move(-_speedLittle, 0);
        _rightLittle.move(-_speedLittle, 0);
    }
}

bool SlidingBackground::loadTextures(std::string leftBig, std::string rightBig, std::string leftLittle, std::string rightLittle)
{
    if(!_leftTextureBig.loadFromFile(leftBig))
        return false;

    else if(!_rightTextureBig.loadFromFile(rightBig))
        return false;

    else
    {
        _leftBig.setTexture(_leftTextureBig);
        _rightBig.setTexture(_rightTextureBig);
    }

    if(!_leftTextureLittle.loadFromFile(leftLittle))
        return false;

    else if(!_rightTextureLittle.loadFromFile(rightLittle))
        return false;

    else
    {
        _leftLittle.setTexture(_leftTextureLittle);
        _rightLittle.setTexture(_rightTextureLittle);
    }
    return true;
}

void SlidingBackground::draw(sf::RenderWindow *window)
{
    window->draw(_leftBig);
    window->draw(_rightBig);
    window->draw(_leftLittle);
    window->draw(_rightLittle);
}


void SlidingBackground::reset()
{
    _rightBig.setPosition(sf::Vector2f(_posx + _width -5 , _posy));
    _leftBig.setPosition(sf::Vector2f(_posx, _posy));

    _rightLittle.setPosition(sf::Vector2f(_posx + _width - 5 , _posy));
    _leftLittle.setPosition(sf::Vector2f(_posx, _posy));
}
