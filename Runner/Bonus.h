#ifndef BONUS_H
#define BONUS_H
#include "main.h"
#include "AnimatedSprite.h"


class Bonus : public AnimatedSprite
{
protected:
    int _value;
    bool _picked;

public:
    Bonus(std::string texture, int ms, int posx, int posy, int width, int height, int nbrsprites);
    void move();
    void setPicked(bool picked);
    bool isPicked() const;

};

#endif // BONUS_H
