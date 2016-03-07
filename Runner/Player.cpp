#include "Player.h"

Player::Player()
{
}

Player::Player(int posx, int posy, int width, int height, int mvtx, int mvty)
    :_posx(posx), _posy(posy), _width(width), _height(height), _mvtx(mvtx), _mvty(mvty)
{

}

Player::~Player()
{

}

void Player::move()
{
    _posx += _mvtx;
    _posy += _mvty;
}

void Player::setMvtx(int mvtx)
{
    _mvtx = mvtx;
}

void Player::setMvty(int mvty)
{
    _mvty = mvty;
}

const int Player::getPosx()
{
    return _posx;
}

const int Player::getPosy()
{
    return _posy;
}

