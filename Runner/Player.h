#ifndef PLAYER_H
#define PLAYER_H
#include "MovableElement.h"

class Player : public MovableElement
{
private:
    bool _jumping;
    sf::CircleShape _shadow;

public:
    Player();
    Player(int posx, int posy, int width, int height, int mvtx, int mvty);
    ~Player();

    bool isJumping() const;
    void setJumping(bool isjumping);
    void jump();
    void rotate(sf::Sprite &p);
    void drawShadow(sf::RenderWindow *window);
};

#endif // PLAYER_H
