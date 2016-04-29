#ifndef BONUS_H
#define BONUS_H
#include "main.h"
#include "AnimatedSprite.h"


class Bonus : public AnimatedSprite
{
protected:
    bool _picked; //booléen qui indique si le bonus a été ramassé

public:
    Bonus(std::string texture, int ms, int posx, int posy, int width, int height, int nbrsprites);
    void setPicked(bool picked);
    bool isPicked() const;

};

#endif // BONUS_H
