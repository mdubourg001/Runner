#ifndef COIN_H
#define COIN_H
#include "main.h"
#include "AnimatedSprite.h"
#include "clock.h"

class Coin : public AnimatedSprite
{
protected:
    int _alpha_opacity;

    bool _picked;
    bool _destroyed;
    bool _ball_detect; // pour gérer le bonus aimant

    sf::Text _alphatext; // pour déssiner le +1 en rammasant une piece
    sf::Font _font;

    Clock _alpha_clock;

public:
    Coin(std::string texture, int ms, int posx, int posy, int width, int height, int nbrsprites);
    ~Coin() override;

    bool isPicked() const;
    void setPicked(bool picked);
    void setDestroyed(bool destroyed);
    bool getDestroyed() const;
    void set_ball_detected(bool detected);
    bool get_ball_detected() const;
    bool clock_has_ticked() const;

    void move_magnet(Player* player);
    void draw_alpha(sf::RenderWindow *w);
};

#endif // COIN_H
