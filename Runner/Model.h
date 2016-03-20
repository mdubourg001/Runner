#ifndef _MODEL_
#define _MODEL_
#include "main.h"
#include "Player.h"
#include "AnimatedSprite.h"
#include "Coin.h"

class Model
{
protected:
    int _w, _h;
    Player _player;


public:

        std::vector<Coin> _coins;
    Model(int w, int h);
    ~Model();

    void nextStep();
    Player* getPlayer();
    void getPlayerPosition(int &x, int &y);
    void setPlayerDirection(direction d);
    void movePlayer(direction d);
};
#endif
