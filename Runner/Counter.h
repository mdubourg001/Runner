#ifndef COUNTER_H
#define COUNTER_H
#include "main.h"


class Counter
{
protected:
    int _value;
    sf::Sprite _sprite;
    sf::Texture _texture;
    sf::Text _text;
    sf::Font _font;

public:
    Counter();
    Counter(int value, int posx, int posy, int width, int height);
    int getValue() const;
    void setValue(int value);
    void setTexture(std::string filename);
    void initSprite(int w, int h, int posx, int posy);
    void increment();
    void decrement();
    void draw(sf::RenderWindow *w);
};

#endif // COUNTER_H
