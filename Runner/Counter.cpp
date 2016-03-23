#include "Counter.h"

Counter::Counter()
    : _value {0}
{
    if(!_font.loadFromFile("res/slapstick.ttf"))
    {
        std::cerr << "ERROR WHEN LOADING FILE : " << "res/slapstick.ttf" << std::endl;
        exit(EXIT_FAILURE);
    }

    _text.setFont(_font);
    _text.setColor(sf::Color::Black);
    _text.setPosition(sf::Vector2f(_sprite.getPosition().x + 20, _sprite.getPosition().y));
}

Counter::Counter(int value, int posx, int posy, int width, int height)
    : _value {value}
{
    if(!_font.loadFromFile("res/slapstick.ttf"))
    {
        std::cerr << "ERROR WHEN LOADING FILE : " << "res/slapstick.ttf" << std::endl;
        exit(EXIT_FAILURE);
    }

    _sprite.setPosition(sf::Vector2f(posx, posy));
    _text.setFont(_font);
    _text.setColor(sf::Color::Black);
    _text.setPosition(sf::Vector2f(_sprite.getPosition().x + 90, _sprite.getPosition().y));
}


int Counter::getValue() const
{
    return _value;
}

void Counter::setValue(int value)
{
    _value = value;
}

void Counter::increment()
{
    _value++;
}

void Counter::decrement()
{
    _value--;
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

void Counter::draw(sf::RenderWindow *w)
{
    _text.setString(std::to_string(_value));;
    w->draw(_sprite);
    w->draw(_text);
}
