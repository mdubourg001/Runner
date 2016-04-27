#ifndef COIN_H
#define COIN_H
#include "main.h"
#include "AnimatedSprite.h"

class Coin : public AnimatedSprite
{
protected:
    bool _picked; //booléen qui indique si la pièce a été ramassée

public:
    Coin(std::string texture, int ms, int posx, int posy, int width, int height, int nbrsprites);
    Coin(int ms, int posx, int posy, int width, int height); // constructeur pour les test unitaires
    void moveMagnet(); //déplace les pièces lorsque le bonus 'aimant' est actif
    void setPicked(bool picked);
    bool isPicked() const;
};

#endif // COIN_H
