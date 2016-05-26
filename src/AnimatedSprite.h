#ifndef ANIMATEDSPRITE_H
#define ANIMATEDSPRITE_H

#include "main.h"
#include <chrono>
#include <iostream>

class Player;

class AnimatedSprite : public sf::Sprite
{
protected:
    sf::Texture _texture;
    std::string _texturename;
    sf::IntRect _sourceRect;
    int _movespeed;
    int _nbrsprites;

public:
    AnimatedSprite();
    AnimatedSprite(std::string texture, int ms, int posx, int posy, int width, int height, int nbrsprites);
    ~AnimatedSprite() = 0;

    void actualiseSpeed(int speed);

    virtual void move();
    void animate(int value);

};

#endif // ANIMATEDSPRITE_H
