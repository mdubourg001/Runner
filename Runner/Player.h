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
    bool _jumping;
    bool _falling;
    direction dir;

public:
    Player();
    ~Player();
    Player(int posx, int posy, int width, int height, int mvtx, int mvty);

    void setMvtx(int mvtx);
    void setMvty(int mvty);
    void setJumping(bool isjumping);

    int getPosx() const;
    int getPosy() const;
    int getMvtx() const;
    int getMvty() const;
    int getWidth() const;
    int getHeight() const;
    bool isJumping() const;
    bool isFalling() const;
    direction getDirection() const;

    void changeDirection(direction d);
    void move();
    void jump();

};

#endif // PLAYER_H
