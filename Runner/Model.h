#ifndef _MODEL_
#define _MODEL_
#include "main.h"
#include "Player.h"
#include "AnimatedSprite.h"
#include "Coin.h"
#include "Counter.h"
#include "Diamond.h"
#include "Bonus.h"

enum BonusType
{
    magnet,
    randombonus,
    shield,
    health,
    star,
    feather,
    hourglass,
    redcoin
};

class Model
{
protected:
    int _w, _h;
    Player _player;
    std::vector<Coin*> _coins;
    std::vector<Diamond*> _diamonds;
    std::vector<Bonus*> _bonus;

    Counter _coin_counter;
    Counter _score_counter;
    Counter _diamond_counter;
    int _framecpt;
    bool _canpop;

    BonusType bt;

    sf::RectangleShape _healthRect;
    sf::RectangleShape _backhealthRect;
    sf::RectangleShape _shellRect;
    sf::Font _font;
    sf::Text _healthText;

public:
    Model(int w, int h);
    ~Model();

    void nextStep();
    Player* getPlayer();
    std::vector<Coin *> *Coins();
    std::vector<Diamond *> *Diamonds();
    std::vector<Bonus *> *Awards();
    void getPlayerPosition(int &x, int &y);
    void setPlayerDirection(direction d);
    void movePlayer();
    void addCoin();
    void addDiamond();
    void addBonus();
    void drawInterface(sf::RenderWindow *w);
    void looseLife();
    void winLife();
};
#endif
