#ifndef ANIMATEDSPRITE_H
#define ANIMATEDSPRITE_H

#include "main.h"
#include <chrono>


class AnimatedSprite : public sf::Sprite
{
protected:
    sf::Texture _texture;
    std::string _texturename;
    sf::IntRect _sourceRect;
    int _nbrsprites;
    int _movespeed;

public:
    AnimatedSprite();
    AnimatedSprite(std::string texture, int ms, int posx, int posy, int width, int height, int nbrsprites);
    ~AnimatedSprite() = 0;

    virtual void move();
    void animate(int value);
    void actualiseSpeed(int speed);

};

#endif // ANIMATEDSPRITE_H
