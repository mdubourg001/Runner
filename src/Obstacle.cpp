#include "Obstacle.h"
#include "Model.h"
#include <iostream>

Obstacle::Obstacle()
{}

Obstacle::Obstacle(int category, int ms)
    : _category{category}, _destroyed{false}, _movespeed{ms}
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
    case 4:
        _cubes.push_back(new Cube(rand()%5 + 1, 1));
        _cubes.push_back(new Cube(rand()%5 + 1, 2));
        _cubes.push_back(new Cube(rand()%5 + 1, 3));
        _cubes.push_back(new Cube(rand()%5 + 1, 4));
        break;

    default:
        exit(EXIT_FAILURE);
        std::cerr << "Cette catégorie d'obstacle n'existe pas" << std::endl;
    }

    _hitbox.setSize(sf::Vector2f(50, category*50));
    _hitbox.setOrigin(25, _hitbox.getSize().y );
    _hitbox.setPosition(sf::Vector2f(_cubes.at(0)->getPos().x, _cubes.at(0)->getPos().y + 25));
}


/*!
 * \brief Obstacle::move
 * déplace l'obstacle de _movespeed;
 */
void Obstacle::move()
{
    for(unsigned int i=0 ; i<_cubes.size() ; i++)
    {
        _cubes.at(i)->move(_movespeed);
    }

    _hitbox.setPosition(_cubes.at(0)->getPos());
}

void Obstacle::setDestroyed(bool destroyed)
{
    _destroyed = destroyed;
}

bool Obstacle::isDestroyed() const
{
    return _destroyed;
}

/*!
 * \brief Obstacle::draw
 * \param w
 * dessine l'obstacle (dessine tout les cubes de l'obstacle)
 */
void Obstacle::draw(sf::RenderWindow *w)
{
    for(unsigned int i=0 ; i<_cubes.size() ; i++)
    {
        _cubes.at(i)->draw(w);
    }
}

sf::Vector2f Obstacle::getPos() const
{
    return _hitbox.getPosition();
}

sf::Vector2f Obstacle::getSize() const
{
    return _hitbox.getSize();
}


/*!
 * \brief Obstacle::actualiseSpeed
 * \param speed
 * actualise la vitesse des obstacles
 */
void Obstacle::actualiseSpeed(int speed)
{
    _movespeed = speed;
}
