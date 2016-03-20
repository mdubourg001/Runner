#ifndef COIN_H
#define COIN_H
#include "main.h"
#include "AnimatedSprite.h"


class Coin : public AnimatedSprite
{
protected:
    int _value;

public:
    Coin(std::string texture);
};

#endif // COIN_H
