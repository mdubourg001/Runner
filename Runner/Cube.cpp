#include "Cube.h"

Cube::Cube()
{}

Cube::Cube(int color, int stage)
    : _color {color} //1->red 2->blue 3->green 4->yellow 5->purple
{
    setOrigin(25, 25);

    switch (_color)
    {
    case 1:
        if(!_texture.loadFromFile("res/redcube.png"))
        {
            std::cerr << "Erreur lors du chargement de redcube.png";
            exit(EXIT_FAILURE);
        }
        break;
    case 2:
        if(!_texture.loadFromFile("res/bluecube.png"))
        {
            std::cerr << "Erreur lors du chargement de bluecube.png";
            exit(EXIT_FAILURE);
        }
        break;
    case 3:
        if(!_texture.loadFromFile("res/greencube.png"))
        {
            std::cerr << "Erreur lors du chargement de greencube.png";
            exit(EXIT_FAILURE);
        }
        break;
    case 4:
        if(!_texture.loadFromFile("res/yellowcube.png"))
        {
            std::cerr << "Erreur lors du chargement de yellowcube.png";
            exit(EXIT_FAILURE);
        }
        break;
    case 5:
        if(!_texture.loadFromFile("res/purplecube.png"))
        {
            std::cerr << "Erreur lors du chargement de purplecube.png";
            exit(EXIT_FAILURE);
        }
        break;
    default:
        break;
    }

    setTexture(_texture);

    switch(stage)
    {
    case 1:
        setPosition(sf::Vector2f(SCREEN_WIDTH + 100, SCREEN_HEIGHT - SCREEN_HEIGHT/4 + 40));
        break;
    case 2:
        setPosition(sf::Vector2f(SCREEN_WIDTH + 100, SCREEN_HEIGHT - SCREEN_HEIGHT/4));
        break;
    case 3:
        setPosition(sf::Vector2f(SCREEN_WIDTH + 100, SCREEN_HEIGHT - SCREEN_HEIGHT/4 - 40));
        break;
    case 4:
        setPosition(sf::Vector2f(SCREEN_WIDTH + 100, SCREEN_HEIGHT - SCREEN_HEIGHT/4 - 80));
    default:
        break;
    }
}

void Cube::setColor(int color)
{
    _color = color;

    switch (_color)
    {
    case 1:
        if(!_texture.loadFromFile("res/redcube.png"))
        {
            std::cerr << "Erreur lors du chargement de redcube.png";
            exit(EXIT_FAILURE);
        }
        break;
    case 2:
        if(!_texture.loadFromFile("res/bluecube.png"))
        {
            std::cerr << "Erreur lors du chargement de bluecube.png";
            exit(EXIT_FAILURE);
        }
        break;
    case 3:
        if(!_texture.loadFromFile("res/greencube.png"))
        {
            std::cerr << "Erreur lors du chargement de greencube.png";
            exit(EXIT_FAILURE);
        }
        break;
    case 4:
        if(!_texture.loadFromFile("res/yellowcube.png"))
        {
            std::cerr << "Erreur lors du chargement de yellowcube.png";
            exit(EXIT_FAILURE);
        }
        break;
    case 5:
        if(!_texture.loadFromFile("res/purplecube.png"))
        {
            std::cerr << "Erreur lors du chargement de purplecube.png";
            exit(EXIT_FAILURE);
        }
        break;
    default:
        break;
    }
}

void Cube::draw(sf::RenderWindow *w)
{
    w->draw(*this);
}

void Cube::move(int movespeed)
{
    setPosition(getPosition().x - movespeed, getPosition().y);
}

sf::Vector2f Cube::getPos() const
{
    return getPosition();
}

sf::Vector2f Cube::getOri() const
{
    return getOrigin();
}

