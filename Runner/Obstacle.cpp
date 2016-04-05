#include "Obstacle.h"

Obstacle::Obstacle()
{}

Obstacle::Obstacle(int category, int color)
    : _movespeed {5}, _category{category}, _color{color}, _destroyed{false}
{
    setPosition(sf::Vector2f(SCREEN_WIDTH + 10, SCREEN_HEIGHT-SCREEN_HEIGHT/5));

    switch(_category)
    {
        case 1:
            break;

        case 2:
            break;

        case 3:
            break;

        default:
            exit(EXIT_FAILURE);
            std::cerr << "Cette catégorie d'obstacle n'existe pas" << std::endl;
    }

    switch (_color)
    {
        case 1: //rouge
            if(!_texture.loadFromFile("res/redcube.png"))
            {
                exit(EXIT_FAILURE);
                std::cerr << "Erreur lors du chargement du sprite du cube" + _color << std::endl;
            }
            break;
        case 2: //vert
            if(!_texture.loadFromFile("res/greencube.png"))
            {
                exit(EXIT_FAILURE);
                std::cerr << "Erreur lors du chargement du sprite du cube" + _color << std::endl;
            }
            break;
        case 3: //yellow
            if(!_texture.loadFromFile("res/yellowcube.png"))
            {
                exit(EXIT_FAILURE);
                std::cerr << "Erreur lors du chargement du sprite du cube" + _color << std::endl;
            }
            break;
        case 4: //violet
            if(!_texture.loadFromFile("res/purplecube.png"))
            {
                exit(EXIT_FAILURE);
                std::cerr << "Erreur lors du chargement du sprite du cube" + _color << std::endl;
            }
            break;
        case 5: //bleu
            if(!_texture.loadFromFile("res/bluecube.png"))
            {
                exit(EXIT_FAILURE);
                std::cerr << "Erreur lors du chargement du sprite du cube" + _color << std::endl;
            }
            break;
        default:
            exit(EXIT_FAILURE);
            std::cerr << "Cette couleur d'obstacle n'existe pas" << std::endl;
            break;
    }

    setTexture(_texture);
}

void Obstacle::move()
{
    setPosition(sf::Vector2f(getPosition().x - _movespeed, getPosition().y));
}

void Obstacle::setDestroyed(bool destroyed)
{
    _destroyed = destroyed;
}

bool Obstacle::isDestroyed() const
{
    return _destroyed;
}

