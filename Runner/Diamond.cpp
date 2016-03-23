#include "Diamond.h"

Diamond::Diamond(std::string texture, int ms, int posx, int posy, int width, int height, int nbrsprites)
    : AnimatedSprite(texture, ms, posx, posy, width, height, nbrsprites), _picked(false)
{

}

void Diamond::move()
{
    setPosition(sf::Vector2f(getPosition().x - _movespeed, getPosition().y));
}

void Diamond::setPicked(bool picked)
{
    _picked = picked;
}

bool Diamond::isPicked() const
{
    return _picked;
}

