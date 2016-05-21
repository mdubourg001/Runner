#include "AnimatedSprite.h"
#include <iostream>

//=======================CONSTRUCTEUR==========================

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
    setOrigin(sf::Vector2f(_texture.getSize().x/2, _texture.getSize().y/2));;
}

AnimatedSprite::~AnimatedSprite()
{ }

//===============================================================
//============AUTRES METHODES====================================


void AnimatedSprite::move()
    //déplace le sprite de _movespeed vers la gauche
{
    setPosition(sf::Vector2f(getPosition().x - _movespeed, getPosition().y));
}


void AnimatedSprite::animate(int value)
    //gère l'animation du sprite en fonction du nombre de sprites dont il est composé
    //déplace le rectangle de lecture et actualise la texture
{
    if(_sourceRect.left  >= (_nbrsprites-1)*value)
        _sourceRect.left = _sourceRect.top =  0;

    else
    {
        _sourceRect.left += value;
        _texture.loadFromFile(_texturename, _sourceRect);
    }
}


void AnimatedSprite::actualiseSpeed(int speed)
    //actualise la _movespeed du sprite lorsque le jeu s'accélère
{
    _movespeed = speed;
}

//================================================================
