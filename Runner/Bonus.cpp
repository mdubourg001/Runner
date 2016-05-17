#include "Bonus.h"

//========================CONSTRUCTEUR================================

Bonus::Bonus(std::string texture, int ms, int posx, int posy, int width, int height, int nbrsprites)
    : AnimatedSprite(texture, ms, posx, posy, width, height, nbrsprites), _picked(false)
{ }

Bonus::~Bonus()
{ }

//====================================================================
//======================ACCESSEURS====================================

void Bonus::setPicked(bool picked)
{
    _picked = picked;
}

bool Bonus::isPicked() const
{
    return _picked;
}

//====================================================================


