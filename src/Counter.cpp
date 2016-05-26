#include "Counter.h"
#include <iostream>

//============================CONTRUCTEURS===============================

Counter::Counter()
    : _value {0}
{
    if(!_font.loadFromFile(POLICE))
    {
        std::cerr << "ERROR WHEN LOADING FILE : " << POLICE << std::endl;
        exit(EXIT_FAILURE);
    }

    _text.setFont(_font);
    _text.setColor(sf::Color::Black);
    _text.setPosition(sf::Vector2f(_sprite.getPosition().x + 20, _sprite.getPosition().y));
}

Counter::Counter(int value, int posx, int posy)
    : _value {value}
{
    if(!_font.loadFromFile(POLICE))
    {
        std::cerr << "ERROR WHEN LOADING FILE : " << POLICE << std::endl;
        exit(EXIT_FAILURE);
    }

    _sprite.setPosition(sf::Vector2f(posx, posy));
    _text.setFont(_font);
    _text.setColor(sf::Color::Black);
    _text.setPosition(sf::Vector2f(_sprite.getPosition().x + 60, _sprite.getPosition().y));
}

//==========================================================================

//===============================ACCESSEURS=================================

int Counter::getValue() const
{ return _value; }

void Counter::setValue(int value)
{
    _value = value;
}

void Counter::setTexture(std::string filename)
{
    if(!_texture.loadFromFile(filename))
    {
        std::cerr << "ERROR WHEN LOADING FILE : " << filename << std::endl;
        exit(EXIT_FAILURE);
    }

    _sprite.setTexture(_texture);
}

//==========================================================================

//=========================AUTRES METHODES==================================

/*!
 * \brief Counter::increment
 * incrémente le compteur de 1
 */
void Counter::increment()
{
    _value++;
}

/*!
 * \brief Counter::hundredincrement
 * incrémente le compteur de 100
 */
void Counter::hundredincrement()
{
    _value+=100;
}

/*!
 * \brief Counter::draw
 * \param w
 * met a jour le texte du compteur et le dessine
 */
void Counter::draw(sf::RenderWindow *w)
{
    _text.setString(std::to_string(_value));;
    w->draw(_sprite);
    w->draw(_text);
}

//==========================================================================
