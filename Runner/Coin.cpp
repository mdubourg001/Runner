#include "Coin.h"
#include "Player.h"
#include "math.h"

//=======================CONSTRUCTEUR=============================

Coin::Coin(std::string texture, int ms, int posx, int posy, int width, int height, int nbrsprites)
    : AnimatedSprite(texture, ms, posx, posy, width, height, nbrsprites)
    ,_picked(false), _ball_detect(false)
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

bool Coin::get_ball_detected() const
{
    return _ball_detect;
}

void Coin::set_ball_detected(bool detected)
{
    _ball_detect = detected;
}

//================================================================
//=======================AUTRES METHODES==========================

void Coin::move_magnet(Player* player)
{
    _movespeed = 13;
    sf::Vector2f player_pos(player->getPosx(), player->getPosy());
    sf::Vector2f direction(player_pos.x  - this->getPosition().x,
                           player_pos.y  - this->getPosition().y);
    int x_movespeed = (direction.x * _movespeed)
            / (abs(direction.x) + abs(direction.y));
    int y_movespeed = (direction.y * _movespeed)
            / (abs(direction.x) + abs(direction.y));
    this->setPosition(sf::Vector2f(this->getPosition().x + x_movespeed
                                   ,this->getPosition().y + y_movespeed));
}

//================================================================


