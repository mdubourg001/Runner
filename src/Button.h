#ifndef BUTTON_H
#define BUTTON_H

#include "main.h"
#include <iostream>
#include <SFML/Graphics.hpp>


class Button : sf::Sprite
{
protected:
    sf::Texture _texture;
    sf::Texture _texture_hover;
    sf::Text _text;
    sf::Font _font;
    sf::Color _textcolor;
    bool _selected;
    bool _isbig;

public:
    Button();
    void initialise(std::string texture, std::string texture_hover, std::string text,
                    std::string font, sf::Color color,  int posx, int posy);

    sf::Vector2f getPos() const;
    sf::FloatRect get_bounds() const;
    bool isSelected() const;
    void setSelected(bool selected);
    sf::Color getColor() const;
    void setColor(sf::Color color);
    void setLittleTexture();
    void setBigTexture();
    std::string getString() const;
    void setString(std::string string);
    sf::FloatRect get_size() const;

    void draw(sf::RenderWindow *w);

};

#endif // BUTTON_H
