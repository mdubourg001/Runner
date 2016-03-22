#ifndef COIN_H
#define COIN_H
#include "main.h"
#include "AnimatedSprite.h"


class Coin : public AnimatedSprite
{
protected:
    int _value;

public:
    Coin(std::string texture, int ms, int posx, int posy, int width, int height, int nbrsprites);
};

#endif // COIN_H
