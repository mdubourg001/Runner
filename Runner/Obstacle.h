#ifndef OBSTACLE_H
#define OBSTACLE_H
#include "main.h"
#include "AnimatedSprite.h"
#include "Cube.h"
#include "ctime"


class Obstacle : public sf::Sprite
{
protected:
    int _category; //attribut qui indique de combien de cubes est composé l'obstacle, {1, 2, 3}
    static int _movespeed;
    bool _destroyed;
    std::vector<Cube*> _cubes;

public:
    Obstacle();
    Obstacle(int category);

    void move();
    void setDestroyed(bool destroyed);
    bool isDestroyed() const;
    void draw(sf::RenderWindow* w);
};

#endif // OBSTACLE_H
