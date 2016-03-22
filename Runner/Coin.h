#ifndef COIN_H
#define COIN_H
#include "main.h"
#include "AnimatedSprite.h"


class Coin : public AnimatedSprite
{
protected:
    int _value;
    bool _picked;

public:
    Coin(std::string texture, int ms, int posx, int posy, int width, int height, int nbrsprites);
    void move();
    void setPicked(bool picked);
    bool isPicked() const;
};

#endif // COIN_H
