#include "Coin.h"
#include "Player.h"

Coin::Coin(std::string texture, int ms, int posx, int posy, int width, int height, int nbrsprites)
    : AnimatedSprite(texture, ms, posx, posy, width, height, nbrsprites), _picked(false)
{

}

Coin::Coin(int ms, int posx, int posy, int width, int height)
    : AnimatedSprite(ms, posx, posy, width, height)
{

}


void Coin::moveMagnet()
{
    setPosition(sf::Vector2f(getPosition().x- Player::getPositionX(), getPosition().y - Player::getPositionY()));
}

void Coin::setPicked(bool picked)
{
    _picked = picked;
}

bool Coin::isPicked() const
{
    return _picked;
}

