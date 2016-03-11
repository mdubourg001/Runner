#include "Player.h"

Player::Player()
{
}

Player::Player(int posx, int posy, int width, int height, int mvtx, int mvty)
    :_posx(posx), _posy(posy), _width(width), _height(height), _mvtx(mvtx), _mvty(mvty), _jumping(false), dir(r)
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

void Player::jump() //non fonctionelle
{
    if(_posy > SCREEN_HEIGHT-SCREEN_HEIGHT/5)
    {
        if(_posy >= 300)
        {
            _mvty = 10;
        }

        else if(_posy <= SCREEN_HEIGHT-SCREEN_HEIGHT/5)
        {
            _jumping = false;
            _mvty = 0;
        }
    }
}


//=======================================
// Accesseurs
//=======================================
void Player::setJumping(bool isjumping)
{ _jumping = isjumping; }

void Player::setMvtx(int mvtx)
{ _mvtx = mvtx; }

void Player::setMvty(int mvty)
{ _mvty = mvty; }

void Player::changeDirection(direction d)
{ dir = d; }

const int Player::getMvtx()
{ return _mvtx; }

const int Player::getMvty()
{ return _mvty; }

const int Player::getPosx()
{ return _posx; }

const int Player::getPosy()
{ return _posy; }

const bool Player::isJumping()
{ return _jumping; }

const bool Player::isFalling()
{ return _falling; }

direction Player::getDirection()
{ return dir; }



