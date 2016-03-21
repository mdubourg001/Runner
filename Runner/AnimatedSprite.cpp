#include "AnimatedSprite.h"

AnimatedSprite::AnimatedSprite(std::string texture, int ms, int posx, int posy)
    : _movespeed {ms}
{
    if(!_texture.loadFromFile(texture))
    {
        std::cerr << "ERROR WHEN LOADING IMAGE FILE: " << texture << std::endl;
        exit(EXIT_FAILURE);
    }

    setPosition(sf::Vector2f(posx, posy));
    setTexture(_texture);
    setOrigin(sf::Vector2f(_texture.getSize().x/2, _texture.getSize().y/2));
}


void AnimatedSprite::move()
{
    setPosition(sf::Vector2f(getPosition().x - _movespeed, getPosition().y));
}
