#ifndef COIN_H
#define COIN_H
#include "main.h"
#include "AnimatedSprite.h"

class Coin : public AnimatedSprite
{
protected:
    int _value;
    bool _picked;
    bool _alpha_on;
    sf::Text _alphatext;
    sf::Font _font;
    unsigned int _alpha_value;

public:
    Coin(std::string texture, int ms, int posx, int posy, int width, int height, int nbrsprites);
    Coin(int ms, int posx, int posy, int width, int height); // constructeur pour les test unitaires
    void move();
    void setPicked(bool picked);
    bool isPicked() const;
    void drawAlpha();
    sf::Text* Alpha();
};

#endif // COIN_H
