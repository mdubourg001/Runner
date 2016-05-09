#ifndef BUTTON_H
#define BUTTON_H

#include <iostream>
#include <SFML/Graphics.hpp>


class Button : sf::Sprite
{
protected:
    sf::Texture _texture;
    sf::Texture _texture_hover;
    sf::Text _text;
    sf::Font _font;

public:
    Button(std::string texture, std::string texture_hover, std::string text,
           sf::Color color, int posx, int posy);
};

#endif // BUTTON_H
