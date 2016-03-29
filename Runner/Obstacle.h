#ifndef OBSTACLE_H
#define OBSTACLE_H
#include "main.h"
#include "AnimatedSprite.h"


class Obstacle : public sf::Sprite
{
protected:
    int _category; //attribut qui indique de combien de cubes est composé l'obstacle, {1, 2, 3}
    int _color; //attribut qui défini la couleur de l'obstacle {orange, purple, green, red, blue}
    int _movespeed;
    bool _destroyed;
    sf::Texture _texture;

public:
    Obstacle();
    Obstacle(int category, int color);

    void move();
    void setDestroyed(bool destroyed);
    bool isDestroyed() const;
};

#endif // OBSTACLE_H
