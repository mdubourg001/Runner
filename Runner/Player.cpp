#include "Player.h"

//=======================================
// Constructeurs&Destructeurs
//=======================================

Player::Player()
{
}

Player::Player(int posx, int posy, int width, int height, int mvtx, int mvty)
    :MovableElement(posx, posy, width, height, mvtx, mvty)
{

}

Player::~Player()
{}

//=======================================
// Accesseurs
//=======================================

void Player::setJumping(bool isjumping)
{ _jumping = isjumping; }

bool Player::isJumping() const
{ return _jumping; }

//=======================================
// Méthodes
//=======================================

void Player::jump()
{
    if(_posy >= SCREEN_HEIGHT-SCREEN_HEIGHT/5)
    {
        setJumping(false);
        setMvty(0);
    }
    else
        setMvty(getMvty()+1);
}



