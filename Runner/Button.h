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
    sf::Color _textcolor;
    bool _selected;
    bool _isbig;

public:
    Button();
    void initialise(std::string texture, std::string texture_hover, std::string text,
                    std::string font, sf::Color color,  int posx, int posy);
    bool isSelected() const;
    void setSelected(bool selected);
    bool getIsbig() const;
    void setIsbig(bool isbig);
    void setLittleTexture();
    void setBigTexture();
    std::string getString() const;
    void setString(std::string string);
    sf::Color getColor() const;
    void setColor(sf::Color color);
    void draw(sf::RenderWindow *w);
    sf::Vector2f getPos() const;
};

#endif // BUTTON_H
