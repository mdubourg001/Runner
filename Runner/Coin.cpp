#include "Coin.h"

Coin::Coin(std::string texture, int ms, int posx, int posy, int width, int height, int nbrsprites)
    : AnimatedSprite(texture, ms, posx, posy, width, height, nbrsprites), _picked(false)
{

}

void Coin::move()
{
    setPosition(sf::Vector2f(getPosition().x - _movespeed, getPosition().y));
}

void Coin::setPicked(bool picked)
{
    _picked = picked;
}

bool Coin::isPicked() const
{
    return _picked;
}

