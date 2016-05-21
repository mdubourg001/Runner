#ifndef OBSTACLE_H
#define OBSTACLE_H
#include "main.h"
#include "AnimatedSprite.h"
#include "Cube.h"
#include "ctime"


class Obstacle : public sf::Sprite
{
protected:
    int _category; //attribut qui indique de combien de cubes est composé l'obstacle, {1, 2, 3, 4}
    sf::RectangleShape _hitbox;
    bool _destroyed;
    int _movespeed;

    std::vector<Cube*> _cubes;

public:
    Obstacle();
    Obstacle(int category, int ms);

    void setDestroyed(bool destroyed);
    sf::Vector2f getPos() const;
    sf::Vector2f getSize() const;
    bool isDestroyed() const;

    void move();
    void draw(sf::RenderWindow* w);
    void actualiseSpeed(int speed);
};

#endif // OBSTACLE_H
