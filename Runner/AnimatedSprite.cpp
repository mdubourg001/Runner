#include "AnimatedSprite.h"
#include <iostream>

AnimatedSprite::AnimatedSprite()
{

}

AnimatedSprite::AnimatedSprite(std::string texture, int ms,
                               int posx, int posy, int width, int height, int nbrsprites)
    : _movespeed {ms}, _nbrsprites(nbrsprites)
{
    _sourceRect.width = width;
    _sourceRect.height = height;
    _sourceRect.left = _sourceRect.top = 0;
    _texturename = texture;

    if(!_texture.loadFromFile(texture, _sourceRect))
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

void AnimatedSprite::animate(int value)
{
    if(_sourceRect.left  >= _nbrsprites*value)
        _sourceRect.left = 0;

    else
    {
        _sourceRect.left += value;
        _texture.loadFromFile(_texturename, _sourceRect);
    }
}

