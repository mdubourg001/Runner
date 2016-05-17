#include "Coin.h"
#include "Player.h"

//=======================CONSTRUCTEUR=============================

Coin::Coin(std::string texture, int ms, int posx, int posy, int width, int height, int nbrsprites)
    : AnimatedSprite(texture, ms, posx, posy, width, height, nbrsprites), _picked(false)
{
    _font.loadFromFile(POLICEMENU);
}

Coin::~Coin()
{ }

//================================================================
//=========================ACCESSEURS=============================

void Coin::setPicked(bool picked)
{
    _picked = picked;
}

bool Coin::isPicked() const
{
    return _picked;
}

//================================================================




