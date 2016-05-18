#ifndef COIN_H
#define COIN_H
#include "main.h"
#include "AnimatedSprite.h"

class Coin : public AnimatedSprite
{
protected:
    int _value;
    bool _picked;
    bool _ball_detect;

    sf::Text _alphatext;
    sf::Font _font;

public:
    Coin(std::string texture, int ms, int posx, int posy, int width, int height, int nbrsprites);
    ~Coin() override;

    void setPicked(bool picked);
    void set_ball_detected(bool detected);
    bool get_ball_detected() const;

    bool isPicked() const;
    void move_magnet(Player* player);
};

#endif // COIN_H
