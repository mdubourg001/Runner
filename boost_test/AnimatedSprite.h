#ifndef ANIMATEDSPRITE_H
#define ANIMATEDSPRITE_H
#include "main.h"


class AnimatedSprite : public sf::Sprite
{
protected:
    sf::Texture _texture;
    std::string _texturename; //path de la texture
    sf::IntRect _sourceRect; //rectangle de lecture du sprite
    int _nbrsprites; //nombre de décalage à réaliser pour animer le sprite
    int _movespeed; //vitesse de déplacement selon l'axe x

public:
    AnimatedSprite();
    AnimatedSprite(std::string texture, int ms, int posx, int posy, int width, int height, int nbrsprites);
    AnimatedSprite(int ms, int posx, int posy, int width, int height); //constructeur servant aux tests unitaires

    void move();
    void animate(int value);

};

#endif // ANIMATEDSPRITE_H
