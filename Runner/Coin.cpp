#include "Coin.h"
#include "Player.h"
#include "math.h"

//=======================CONSTRUCTEUR=============================

Coin::Coin(std::string texture, int ms, int posx, int posy, int width, int height, int nbrsprites)
    : AnimatedSprite(texture, ms, posx, posy, width, height, nbrsprites), _picked(false)
{
    _font.loadFromFile(POLICEMENU);
}

Coin::~Coin()
{ }

//================================================================
//=========================ACCESSEURS=============================

void Coin::setPicked(bool picked)
{
    _picked = picked;
}

bool Coin::isPicked() const
{
    return _picked;
}

//================================================================
//=======================AUTRES METHODES==========================

void Coin::move_magnet(float player_x, float player_y)
{
    _movespeed = 10;
    float pi = 3.14;
    sf::Vector2f player_pos(player_x, player_y);
    sf::Vector2f direction(player_pos.x - this->getPosition().x,
                           player_pos.y - this->getPosition().y);
    float angle = (float)atan(abs(direction.x)/abs(direction.y)) * 180.0 / pi + 90;

    if(player_pos.x >= this->getPosition().x)
        angle *= -180;
    int x_movespeed = (direction.x * _movespeed)
            / (abs(direction.x + abs(direction.y)));
    int y_movespeed = (direction.y * _movespeed)
            / (abs(direction.x + abs(direction.y)));
    this->setPosition(sf::Vector2f(this->getPosition().x + x_movespeed
                                   ,this->getPosition().y + y_movespeed));
}

//================================================================


