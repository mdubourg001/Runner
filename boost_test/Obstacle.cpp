#include "Obstacle.h"
#include <iostream>


int Obstacle::_movespeed = 5;

Obstacle::Obstacle()
{}

Obstacle::Obstacle(int category)
    : _category{category}, _destroyed{false}
{
    srand(time(NULL));

    switch(_category)
    {
    case 1:
        _cubes.push_back(new Cube(rand()%5 + 1, 1));
        break;

    case 2:
        _cubes.push_back(new Cube(rand()%5 + 1, 1));
        _cubes.push_back(new Cube(rand()%5 + 1, 2));
        break;

    case 3:
        _cubes.push_back(new Cube(rand()%5 + 1, 1));
        _cubes.push_back(new Cube(rand()%5 + 1, 2));
        _cubes.push_back(new Cube(rand()%5 + 1, 3));
        break;

    default:
        exit(EXIT_FAILURE);
        std::cerr << "Cette catégorie d'obstacle n'existe pas" << std::endl;
    }
}

void Obstacle::move()
{
    for(int i=0 ; i<_cubes.size() ; i++)
    {
        _cubes.at(i)->move(_movespeed);
    }
}

void Obstacle::setDestroyed(bool destroyed)
{
    _destroyed = destroyed;
}

bool Obstacle::isDestroyed() const
{
    return _destroyed;
}

void Obstacle::draw(sf::RenderWindow *w)
{
    for(int i=0 ; i<_cubes.size() ; i++)
    {
        _cubes.at(i)->draw(w);
    }
}

