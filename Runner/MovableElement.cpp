#include "MovableElement.h"

//=======================================
// Constructeurs&Destructeurs
//=======================================

MovableElement::MovableElement()
{

}

MovableElement::MovableElement(int posx, int posy, int width, int height, int mvtx, int mvty)
    :_posx(posx), _posy(posy), _width(width), _height(height), _mvtx(mvtx), _mvty(mvty), dir(r)
{
}

MovableElement::~MovableElement()
{}

//=======================================
// Accesseurs
//=======================================

void MovableElement::setMvtx(int mvtx)
{ _mvtx = mvtx; }

void MovableElement::setMvty(int mvty)
{ _mvty = mvty; }

void MovableElement::changeDirection(direction d)
{ dir = d; }

int MovableElement::getMvtx() const
{ return _mvtx; }

int MovableElement::getMvty() const
{ return _mvty; }

sf::Vector2f MovableElement::getPos() const
{ return sf::Vector2f(getPosx(), getPosy()); }

int MovableElement::getPosx() const
{ return _posx; }

int MovableElement::getPosy() const
{ return _posy; }

int MovableElement::getWidth() const
{ return _width; }

int MovableElement::getHeight() const
{ return _height; }

direction MovableElement::getDirection() const
{ return dir; }

//=======================================
// Méthodes
//=======================================

void MovableElement::move()
{
    if((_posx-_width/2 >= 0 && _posx+_width/2 <= SCREEN_WIDTH)
            || (_posx-_width/2 < 0 && _mvtx > 0) || (_posx+_width/2 > SCREEN_WIDTH && _mvtx < 0))
    {
        _posx += _mvtx;
    }
    _posy += _mvty;
}
