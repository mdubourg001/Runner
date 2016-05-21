#include "Coin.h"
#include "Player.h"
#include "math.h"

//=======================CONSTRUCTEUR=============================

Coin::Coin(std::string texture, int ms, int posx, int posy, int width, int height, int nbrsprites)
    : AnimatedSprite(texture, ms, posx, posy, width, height, nbrsprites)
    ,_alpha_opacity(255),_picked(false), _destroyed(false), _ball_detect(false)
{
    _font.loadFromFile(POLICE);
    _alphatext.setFont(_font);
    _alphatext.setString("+1");
    _alphatext.setCharacterSize(35);
    _alphatext.setOrigin(_alphatext.getLocalBounds().width/2
                         ,_alphatext.getLocalBounds().height/2);
    _alphatext.setPosition(this->getPosition().x + this->getLocalBounds().width
                           ,this->getPosition().y + this->getLocalBounds().height);
    _alphatext.setColor(sf::Color(255, 255, 255, _alpha_opacity));

    _alpha_clock.set_alarm(Moment(0, 0, 0, 500, 0));
}

Coin::~Coin()
{ }

//================================================================
//=========================ACCESSEURS=============================

void Coin::setPicked(bool picked)
{
    _picked = picked;
    _alpha_clock.start();
}

bool Coin::isPicked() const
{
    return _picked;
}

void Coin::setDestroyed(bool destroyed)
{
    _destroyed = destroyed;
}

bool Coin::getDestroyed() const
{
    return _destroyed;
}

bool Coin::get_ball_detected() const
{
    return _ball_detect;
}

void Coin::set_ball_detected(bool detected)
{
    _ball_detect = detected;
}

bool Coin::clock_has_ticked() const
{
    return _alpha_clock.has_ticked();
}

//================================================================
//=======================AUTRES METHODES==========================

/*!
 * \brief Coin::move_magnet
 * \param player
 * fait bouger la pièce en direction du joueur(aimant)
 */
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

/*!
 * \brief Coin::draw_alpha
 * \param w
 *  dessine le '+1' lorsque la pièce est ramassée
 */
void Coin::draw_alpha(sf::RenderWindow *w)
{
    _alpha_opacity -= 2;
    _alpha_clock.update();
    _alpha_clock.check_time();
    _alphatext.setPosition(this->getPosition().x + this->getLocalBounds().width
                           ,_alphatext.getPosition().y - 5);
    _alphatext.setColor(sf::Color(255, 255, 255, _alpha_opacity));
    w->draw(_alphatext);
}

//================================================================


