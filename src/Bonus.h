#ifndef BONUS_H
#define BONUS_H

#include "main.h"
#include "AnimatedSprite.h"


class Bonus : public AnimatedSprite
{
protected:
    bool _picked;

public:
    Bonus(std::string texture, int ms, int posx, int posy, int width, int height, int nbrsprites);
    ~Bonus() override;

    void setPicked(bool picked);
    bool isPicked() const;
};

#endif // BONUS_H
