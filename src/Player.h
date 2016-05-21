#ifndef PLAYER_H
#define PLAYER_H
#include "MovableElement.h"
#include "Coin.h"
#include "Diamond.h"
#include "Bonus.h"
#include "Obstacle.h"

class Player : public MovableElement
{
private:
    bool _jumping;
    bool _invincibility;
    sf::CircleShape _shadow;
    int _health;
    int _shield;

public:
    Player();
    Player(int posx, int posy, int width, int height, int mvtx, int mvty, int health, int shield);

    ~Player();

    bool isJumping() const;
    void setJumping(bool isjumping);
    bool isInvincibility() const;
    void setInvincibility(bool isInvincibility);
    void setPosition(int x, int y);
    int getHealth() const;
    int getShield() const;
    void setHealth(int h);
    void setShield(int s);

    void jump();
    void rotate(sf::Sprite &p);
    void drawShadow(sf::RenderWindow *window);
    void treatCollisions(std::vector<Coin*> coins, std::vector<Diamond*> diamonds, std::vector<Bonus*> bonus, std::vector<Obstacle*> obstacles);
    void looseLife();
    void winLife();
};

#endif // PLAYER_H