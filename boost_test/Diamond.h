#ifndef DIAMOND_H
#define DIAMOND_H
#include "main.h"
#include "AnimatedSprite.h"


class Diamond : public AnimatedSprite
{
protected:
    bool _picked; //booléen qui indique si le diamant a été ramassé

public:
    Diamond(std::string texture, int ms, int posx, int posy, int width, int height, int nbrsprites);
    void setPicked(bool picked);
    bool isPicked() const;
};

#endif // DIAMOND_H
