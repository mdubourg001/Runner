#ifndef DIAMOND_H
#define DIAMOND_H
#include "main.h"
#include "AnimatedSprite.h"


class Diamond : public AnimatedSprite
{
protected:
    int _value;
    bool _picked;

public:
    Diamond(std::string texture, int ms, int posx, int posy, int width, int height, int nbrsprites);
    ~Diamond() override;

    void setPicked(bool picked);
    bool isPicked() const;
};

#endif // DIAMOND_H
