#include "Coin.h"
#include "Player.h"

Coin::Coin(std::string texture, int ms, int posx, int posy, int width, int height, int nbrsprites)
    : AnimatedSprite(texture, ms, posx, posy, width, height, nbrsprites), _picked(false), _alpha_value(100)
{
    _font.loadFromFile(POLICEMENU);
    _alphatext.setFont(_font);
    _alphatext.setString("+ 1");
    _alphatext.setColor(sf::Color(155, 155, 155, _alpha_value));
    _alphatext.setCharacterSize(25);
    _alphatext.setOrigin(sf::Vector2f(0, 25));
    _alphatext.setPosition(sf::Vector2f(this->getPosition().x + 40, this->getPosition().y +40));
}

Coin::Coin(int ms, int posx, int posy, int width, int height)
    : AnimatedSprite(ms, posx, posy, width, height)
{

}

void Coin::move()
{
    setPosition(sf::Vector2f(getPosition().x - _movespeed, getPosition().y));
}

void Coin::moveMagnet()
{   
    setPosition(sf::Vector2f(getPosition().x- Player::getPositionX(), getPosition().y - Player::getPositionY()));
}

void Coin::setPicked(bool picked)
{
    _picked = picked;

    if(picked)
        _alpha_on = true;
}

bool Coin::isPicked() const
{
    return _picked;
}

//void Coin::drawAlpha()
//{
//    for(int i=0 ; i<100 ; i++)
//    {
//        _alpha_value--;
//        _alphatext.setColor(sf::Color(155, 155, 155, _alpha_value));
//    }
//}

//sf::Text* Coin::Alpha()
//{
//    sf::Text* ptr = &_alphatext;
//    return ptr;
//}



