#include "Player.h"

int Player::getWidth() const
{
    return _width;
}

int Player::getHeight() const
{
    return _height;
}

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
    if((_posx-_width/2 >= 0 && _posx+_width/2 <= SCREEN_WIDTH)
            || (_posx-_width/2 < 0 && _mvtx > 0) || (_posx+_width/2 > SCREEN_WIDTH && _mvtx < 0))
    {
        _posx += _mvtx;
    }
    _posy += _mvty;
}

void Player::jump() //non fonctionelle
{
    if(_posy >= SCREEN_HEIGHT-SCREEN_HEIGHT/5)
    {
        setJumping(false);
        setMvty(0);
    }
    else
        setMvty(getMvty()+1);
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

int Player::getMvtx() const
{ return _mvtx; }

int Player::getMvty() const
{ return _mvty; }

int Player::getPosx() const
{ return _posx; }

int Player::getPosy() const
{ return _posy; }

bool Player::isJumping() const
{ return _jumping; }

bool Player::isFalling() const
{ return _falling; }

direction Player::getDirection() const
{ return dir; }



