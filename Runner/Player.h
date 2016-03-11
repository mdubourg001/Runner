#ifndef PLAYER_H
#define PLAYER_H
#include "main.h"

class Player
{
private:
    int _posx;
    int _posy;
    int _width;
    int _height;
    int _mvtx;
    int _mvty;
    direction dir;

public:
    Player();
    ~Player();
    Player(int posx, int posy, int width, int height, int mvtx, int mvty);

    void move();
    void setMvtx(int mvtx);
    void setMvty(int mvty);

    direction getDirection();
    void changeDirection(direction d);
    const int getPosx();
    const int getPosy();
};

#endif // PLAYER_H