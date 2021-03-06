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
    bool _dead;
    sf::CircleShape _shadow;
    unsigned int _health;
    unsigned int _shield;
    unsigned int _nb_deaths;

public:
    Player();
    Player(int posx, int posy, int width, int height, int mvtx, int mvty, int health, int shield);

    ~Player();

    bool isJumping() const;
    void setJumping(bool isjumping);
    bool isInvincibility() const;
    void setInvincibility(bool isInvincibility);
    void setPosition(int x, int y);
    unsigned int getHealth() const;
    unsigned int getShield() const;
    void setHealth(unsigned int h);
    void setShield(unsigned int s);
    bool is_dead() const;
    void set_dead(bool dead);
    unsigned int get_nb_deaths() const;
    void set_nb_deaths(unsigned int nb);

    void jump();
    void treatCollisions(std::vector<Coin*> coins, std::vector<Diamond*> diamonds,
                         std::vector<Bonus*> bonus, std::vector<Obstacle*> obstacles);
    void rotate(sf::Sprite &p);
    void drawShadow(sf::RenderWindow *window);
    void looseLife();
    void winLife();
    void revive();
    void die();
};

#endif // PLAYER_H
