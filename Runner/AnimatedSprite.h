#ifndef ANIMATEDSPRITE_H
#define ANIMATEDSPRITE_H
#include "main.h"


class AnimatedSprite : public sf::Sprite
{
protected:
    sf::Texture _texture;
    sf::IntRect _sourceRect;

public:
    AnimatedSprite(std::string texture);

    void move();
};

#endif // ANIMATEDSPRITE_H
