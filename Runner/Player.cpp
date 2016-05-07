#include "Player.h"

//=======================================
// Constructeurs&Destructeurs
//=======================================


Player::Player(int posx, int posy, int width, int height, int mvtx, int mvty, int health, int shield)
    :MovableElement(posx, posy, width, height, mvtx, mvty), _shadow(10), _health(health), _shield(shield)
{
    _shadow.setScale(2, 1);
    _shadow.setOrigin(sf::Vector2f(10, 10));
    _shadow.setPosition(sf::Vector2f(_posx, SCREEN_HEIGHT-SCREEN_HEIGHT/6));
    _shadow.setFillColor(sf::Color(120, 120, 120, 60));
}

Player::Player(int posx, int posy, int width, int height, int mvtx, int mvty)
    :MovableElement(posx, posy, width, height, mvtx, mvty)
{

}

Player::Player(int health, int shield)
    : _health{health}, _shield{shield}
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

void Player::treatCollisions(std::vector<Coin *> coins, std::vector<Diamond *> diamonds, std::vector<Bonus *> bonus, std::vector<Obstacle *> obstacles)
{
    for(int i=0 ; i<coins.size() ; i++) //collision entre la balle et les pièces
        if((_posx - 25 <= coins.at(i)->getPosition().x + 25 && _posx - 25 >= coins.at(i)->getPosition().x -25
                && _posy - 25 <= coins.at(i)->getPosition().y + 25 && _posy - 25 >= coins.at(i)->getPosition().y -25)
                || (_posx + 25 >= coins.at(i)->getPosition().x - 25 && _posx + 25 <= coins.at(i)->getPosition().x + 25
                && _posy + 25 >= coins.at(i)->getPosition().y - 25 && _posy + 25 <= coins.at(i)->getPosition().y + 25))
            coins.at(i)->setPicked(true);

    for(int i=0 ; i<diamonds.size() ; i++) //collision entre la balle et les diamants
        if((_posx - 25 <= diamonds.at(i)->getPosition().x + 25 && _posx - 25 >= diamonds.at(i)->getPosition().x -25
                && _posy - 25 <= diamonds.at(i)->getPosition().y + 25 && _posy - 25 >= diamonds.at(i)->getPosition().y -25)
                || (_posx + 25 >= diamonds.at(i)->getPosition().x - 25 && _posx + 25 <= diamonds.at(i)->getPosition().x + 25
                && _posy + 25 >= diamonds.at(i)->getPosition().y - 25 && _posy + 25 <= diamonds.at(i)->getPosition().y + 25))
            diamonds.at(i)->setPicked(true);

    for(int i=0 ; i<bonus.size() ; i++) //collision entre la balle et les bonus
        if((_posx - 25 <= bonus.at(i)->getPosition().x + 25 && _posx - 25 >= bonus.at(i)->getPosition().x -25
                && _posy - 25 <= bonus.at(i)->getPosition().y + 25 && _posy - 25 >= bonus.at(i)->getPosition().y -25)
                || (_posx + 25 >= bonus.at(i)->getPosition().x - 25 && _posx + 25 <= bonus.at(i)->getPosition().x + 25
                && _posy + 25 >= bonus.at(i)->getPosition().y - 25 && _posy + 25 <= bonus.at(i)->getPosition().y + 25))
            bonus.at(i)->setPicked(true);


    for(int i=0 ; i<obstacles.size() ; i++) //collision entre la balle et les obstacles

        if((_posx - 25 <= obstacles.at(i)->getPosition().x + 25 && _posx - 25 >= obstacles.at(i)->getPosition().x -25
                && _posy - 25 <= obstacles.at(i)->getPosition().y + 25 && _posy - 25 >= obstacles.at(i)->getPosition().y -25)
                || (_posx + 25 >= obstacles.at(i)->getPosition().x - 25 && _posx + 25 <= obstacles.at(i)->getPosition().x + 25
                && _posy + 25 >= obstacles.at(i)->getPosition().y - 25 && _posy + 25 <= obstacles.at(i)->getPosition().y + 25))
        {
            obstacles.at(i)->setDestroyed(true);
            looseLife();
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

int Player::getHealth() const
{
    return _health;
}
int Player::getShield() const
{
    return _shield;
}
void Player::setHealth(int h)
{
    _health = h;
}

void Player::setShield(int s)
{
    _shield = s;
}


void Player::looseLife()
{
    if(_shield>0)
        _shield-=80;
    else
        _health-=80;
}


void Player::winLife()
{
    if(_health<400)
        _health+=80;
    else if (_shield<400)
        _shield+=80;
}
