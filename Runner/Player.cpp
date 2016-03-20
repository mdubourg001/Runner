#include "Player.h"

//=======================================
// Constructeurs&Destructeurs
//=======================================

Player::Player()
{
}

Player::Player(int posx, int posy, int width, int height, int mvtx, int mvty)
    :MovableElement(posx, posy, width, height, mvtx, mvty), _shadow(10)
{
    _shadow.setScale(2, 1);
    _shadow.setOrigin(sf::Vector2f(10, 10));
    _shadow.setPosition(sf::Vector2f(_posx, SCREEN_HEIGHT-SCREEN_HEIGHT/6));
    _shadow.setFillColor(sf::Color(120, 120, 120, 40));
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
        _shadow.setRadius(10);
    }
    else
    {
        setMvty(getMvty()+1);
        if(_mvty > 0)
            _shadow.setRadius((45 - _mvty)/2);
        else
            _shadow.setRadius((45 - (-_mvty))/2);
    }
}

void Player::rotate(sf::Sprite &p)
{
    if(dir == none)
        p.rotate(10);

    else if(dir == l)
        p.rotate(-15);

    else if(dir == r)
        p.rotate(15);
}

void Player::drawShadow(sf::RenderWindow* window)
{
    _shadow.setPosition(sf::Vector2f(_posx, SCREEN_HEIGHT-SCREEN_HEIGHT/6));
    window->draw(_shadow);
}



