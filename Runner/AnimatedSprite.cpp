#include "AnimatedSprite.h"

AnimatedSprite::AnimatedSprite(std::string texture)
{
    if(!_texture.loadFromFile(texture))
    {
        std::cerr << "ERROR WHEN LOADING IMAGE FILE: " << texture << std::endl;
        exit(EXIT_FAILURE);
    }

    setTexture(_texture);
    setOrigin(sf::Vector2f(_texture.getSize().x/2, _texture.getSize().y/2));
}


void AnimatedSprite::move()
{

}
