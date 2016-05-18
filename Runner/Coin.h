#ifndef COIN_H
#define COIN_H
#include "main.h"
#include "AnimatedSprite.h"

class Coin : public AnimatedSprite
{
protected:
    int _value;
    bool _picked;

    sf::Text _alphatext;
    sf::Font _font;


public:
    Coin(std::string texture, int ms, int posx, int posy, int width, int height, int nbrsprites);
    ~Coin() override;

    void setPicked(bool picked);
    bool isPicked() const;
    void move_magnet(float player_x, float player_y);
};

#endif // COIN_H
