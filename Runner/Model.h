#ifndef _MODEL_
#define _MODEL_
#include "main.h"
#include "Player.h"

class Model {
private:
    int _w, _h;
    Player _player;

public:

    Model(int w, int h);
    ~Model();

    void nextStep();
    void getPlayerPosition(int &x, int &y);
    void setPlayerDirection(bool left);
    void movePlayer();
};
#endif
