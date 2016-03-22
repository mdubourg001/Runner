#ifndef ANIMATEDSPRITE_H
#define ANIMATEDSPRITE_H
#include "main.h"


class AnimatedSprite : public sf::Sprite
{
protected:
    sf::Texture _texture;
    sf::IntRect _sourceRect;
    int _nbrsprites;
    int _movespeed;

public:
    AnimatedSprite(std::string texture, int ms, int posx, int posy, int width, int height, int nbrsprites);

    void move();
    void animate(int value);

};

#endif // ANIMATEDSPRITE_H
