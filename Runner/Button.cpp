#include "Button.h"
#include "main.h"



Button::Button()
{

}

void Button::initialise(std::string texture, std::string texture_hover,
                        std::string text, std::string font, sf::Color color,
                        int posx, int posy)
{
    this->setPosition(sf::Vector2f(posx, posy));

    _textcolor = color;
    _selected = false;

    _text.setString(text);
    _text.setColor(_textcolor);

    if(!_font.loadFromFile(font))
    {
        std::cerr << "ERROR when loading image file: "
                  << POLICEMENU << std::endl;
        exit(EXIT_FAILURE);
    }
    else
        _text.setFont(_font);

    if (!_texture_hover.loadFromFile(texture_hover))
    {
        std::cerr << "ERROR when loading image file: "
                  << texture_hover << std::endl;
        exit(EXIT_FAILURE);
    }
    else
    {
        _texture_hover.setSmooth(true);
        this->setTexture(_texture_hover);
    }

    if (!_texture.loadFromFile(texture))
    {
        std::cerr << "ERROR when loading image file: "
                  << texture << std::endl;
        exit(EXIT_FAILURE);
    }
    else
    {
        _texture.setSmooth(true);
        this->setTexture(_texture);
    }

    this->scale(0.83, 0.83);
    _text.setPosition(this->getPosition().x, this->getPosition().y + 160);
}

sf::Vector2f Button::getPos() const
{ return this->getPosition(); }

bool Button::isSelected() const
{ return _selected; }

void Button::setSelected(bool selected)
{
    _selected = selected;
}

sf::Color Button::getColor() const
{ return _textcolor; }

void Button::setColor(sf::Color color)
{
    _textcolor = color;
    _text.setColor(_textcolor);
}

void Button::setLittleTexture()
{
    this->setTexture(_texture);
}

void Button::setBigTexture()
{
    this->setTexture(_texture_hover);
}

std::string Button::getString() const
{ return _text.getString(); }

void Button::setString(std::string string)
{ _text.setString(string); }

void Button::draw(sf::RenderWindow *w)
{
    w->draw(*this);
    w->draw(_text);
}

