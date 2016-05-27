#include "Player.h"

//=======================================
// Constructeurs&Destructeurs
//=======================================


Player::Player(int posx, int posy, int width, int height, int mvtx, int mvty, int health, int shield)
    :MovableElement(posx, posy, width, height, mvtx, mvty), _invincibility(false), _dead(false), _shadow(10), _health(health), _shield(shield), _nb_deaths(0)
{
    _shadow.setScale(2, 1);
    _shadow.setOrigin(sf::Vector2f(10, 10));
    _shadow.setPosition(sf::Vector2f(_posx, SCREEN_HEIGHT-SCREEN_HEIGHT/6));
    _shadow.setFillColor(sf::Color(120, 120, 120, 60));
}


Player::~Player()
{}

//=======================================
// Accesseurs
//=======================================

bool Player::isJumping() const
{ return _jumping; }

void Player::setJumping(bool isjumping)
{ _jumping = isjumping; }

bool Player::isInvincibility() const
{ return _invincibility; }

void Player::setInvincibility(bool isInvincibility)
{ _invincibility = isInvincibility; }

void Player::setPosition(int x, int y)
{
   _posx = x;
   _posy = y;
}

unsigned int Player::getHealth() const
{ return _health; }

unsigned int Player::getShield() const
{ return _shield; }

void Player::setHealth(unsigned int h)
{ _health = h; }

void Player::setShield(unsigned int s)
{ _shield = s; }

bool Player::is_dead() const
{ return _dead; }

void Player::set_dead(bool dead)
{ _dead = dead; }

unsigned int Player::get_nb_deaths() const
{ return _nb_deaths; }

void Player::set_nb_deaths(unsigned int nb)
{ _nb_deaths = nb; }

//=======================================
// Méthodes
//=======================================

/*!
 * \brief Player::jump
 * gère le saut de la balle
 */
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

/*!
 * \brief Player::treatCollisions
 * \param coins
 * \param diamonds
 * \param bonus
 * \param obstacles
 * traite les collisions entre la balle et les objets du jeu
 */
void Player::treatCollisions(std::vector<Coin *> coins, std::vector<Diamond *> diamonds, std::vector<Bonus *> bonus, std::vector<Obstacle *> obstacles)
{
    for(unsigned int i=0 ; i<coins.size() ; i++) //collision entre la balle et les pièces
        if((_posx - BALL_WIDTH/2 <= coins.at(i)->getPosition().x + BALL_WIDTH/2 && _posx - BALL_WIDTH/2 >= coins.at(i)->getPosition().x - BALL_WIDTH/2
                && _posy - BALL_WIDTH/2 <= coins.at(i)->getPosition().y + BALL_WIDTH/2 && _posy - BALL_WIDTH/2 >= coins.at(i)->getPosition().y - BALL_WIDTH/2)
                || (_posx + BALL_WIDTH/2 >= coins.at(i)->getPosition().x - BALL_WIDTH/2 && _posx + BALL_WIDTH/2 <= coins.at(i)->getPosition().x + BALL_WIDTH/2
                && _posy + BALL_WIDTH/2 >= coins.at(i)->getPosition().y - BALL_WIDTH/2 && _posy + BALL_WIDTH/2 <= coins.at(i)->getPosition().y + BALL_WIDTH/2))
            coins.at(i)->setPicked(true);

    for(unsigned int i=0 ; i<diamonds.size() ; i++) //collision entre la balle et les diamants
        if((_posx - BALL_WIDTH/2 <= diamonds.at(i)->getPosition().x + BALL_WIDTH/2 && _posx - BALL_WIDTH/2 >= diamonds.at(i)->getPosition().x - BALL_WIDTH/2
                && _posy - BALL_WIDTH/2 <= diamonds.at(i)->getPosition().y + BALL_WIDTH/2 && _posy - BALL_WIDTH/2 >= diamonds.at(i)->getPosition().y - BALL_WIDTH/2)
                || (_posx + BALL_WIDTH/2 >= diamonds.at(i)->getPosition().x - BALL_WIDTH/2 && _posx + BALL_WIDTH/2 <= diamonds.at(i)->getPosition().x + BALL_WIDTH/2
                && _posy + BALL_WIDTH/2 >= diamonds.at(i)->getPosition().y - BALL_WIDTH/2 && _posy + BALL_WIDTH/2 <= diamonds.at(i)->getPosition().y + BALL_WIDTH/2))
            diamonds.at(i)->setPicked(true);

    for(unsigned int i=0 ; i<bonus.size() ; i++) //collision entre la balle et les bonus
        if((_posx - BALL_WIDTH/2 <= bonus.at(i)->getPosition().x + BALL_WIDTH/2 && _posx - BALL_WIDTH/2 >= bonus.at(i)->getPosition().x - BALL_WIDTH/2
                && _posy - BALL_WIDTH/2 <= bonus.at(i)->getPosition().y + BALL_WIDTH/2 && _posy - BALL_WIDTH/2 >= bonus.at(i)->getPosition().y - BALL_WIDTH/2)
                || (_posx + BALL_WIDTH/2 >= bonus.at(i)->getPosition().x - BALL_WIDTH/2 && _posx + BALL_WIDTH/2 <= bonus.at(i)->getPosition().x + BALL_WIDTH/2
                && _posy + BALL_WIDTH/2 >= bonus.at(i)->getPosition().y - BALL_WIDTH/2 && _posy + BALL_WIDTH/2 <= bonus.at(i)->getPosition().y + BALL_WIDTH/2))
            bonus.at(i)->setPicked(true);

    for(unsigned int i=0 ; i<obstacles.size() ; i++) //collision entre la balle et les obstacles
        if(((_posx - BALL_WIDTH/2 <= obstacles.at(i)->getPos().x + BALL_WIDTH/2 && _posx - BALL_WIDTH/2 >= obstacles.at(i)->getPos().x - BALL_WIDTH/2
                && _posy - BALL_WIDTH/2 <= obstacles.at(i)->getPos().y && _posy - BALL_WIDTH/2 >= obstacles.at(i)->getPos().y - obstacles.at(i)->getSize().y)
                || (_posx + BALL_WIDTH/2 >= obstacles.at(i)->getPos().x - BALL_WIDTH/2 && _posx + BALL_WIDTH/2 <= obstacles.at(i)->getPos().x + BALL_WIDTH/2
                && _posy + BALL_WIDTH/2 >= obstacles.at(i)->getPos().y - obstacles.at(i)->getSize().y && _posy + BALL_WIDTH/2 <= obstacles.at(i)->getPos().y + BALL_WIDTH/2))
                && _invincibility == false)
        {
            obstacles.at(i)->setDestroyed(true);
            looseLife();
        }
}

/*!
 * \brief Player::rotate
 * \param p
 * gère la rotation de la balle
 */
void Player::rotate(sf::Sprite &p)
{
    if(dir == none)
        p.rotate(10);

    else if(dir == l)
        p.rotate(-15);

    else if(dir == r)
        p.rotate(15);
}


/*!
 * \brief Player::drawShadow
 * \param window
 * dessine l'ombre de la balle au sol
 */
void Player::drawShadow(sf::RenderWindow* window)
{
    _shadow.setOrigin(_shadow.getLocalBounds().width/2
                      , _shadow.getLocalBounds().height/2);
    _shadow.setPosition(sf::Vector2f(_posx, SCREEN_HEIGHT-SCREEN_HEIGHT/6));
    window->draw(_shadow);
}

/*!
 * \brief Player::looseLife
 * fait perdre 80 pv au joueur
 */
void Player::looseLife()
{
    if(_shield > 0)
        _shield -= BALL_WIN_AND_LOOZ_LIFE;
    else if(_health > 0)
        _health -= BALL_WIN_AND_LOOZ_LIFE;
}

/*!
 * \brief Player::winLife
 * octroie 80 pv au joueur
 */
void Player::winLife()
{
    if(_health < BALL_LIFE)
        _health += BALL_WIN_AND_LOOZ_LIFE;
    else if (_shield < BALL_LIFE)
        _shield += BALL_WIN_AND_LOOZ_LIFE;
}
/*!
 * \brief Player::revive
 * remet les points de vie du joueur
 */
void Player::revive()
{
    _health = BALL_LIFE;
}
/*!
 * \brief Player::die
 * compteur le nombre de fois que le joueur est mort
 * afin d'augmenter ensuite le prix d'une résurrection
 */
void Player::die()
{
    _nb_deaths++;
}
