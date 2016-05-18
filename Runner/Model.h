#ifndef _MODEL_
#define _MODEL_
#include "main.h"
#include "Player.h"
#include "AnimatedSprite.h"
#include "Coin.h"
#include "Counter.h"
#include "Diamond.h"
#include "Bonus.h"
#include "Obstacle.h"

#include <chrono>
#include <ctime>

enum BonusType
{
    no,
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
    std::vector<Obstacle*> _obstacles;

    Counter _coin_counter;
    Counter _score_counter;
    Counter _diamond_counter;
    bool _canpop;
    bool _magnetpicked;
    int _magnetcpt;
    int _difficulte;

    BonusType bt;

    std::chrono::time_point<std::chrono::system_clock> _start, _end;
    std::chrono::time_point<std::chrono::system_clock> _gamestart, _timecheck;
    std::chrono::time_point<std::chrono::system_clock> _bonusstart, _bonuscheck;
    std::chrono::time_point<std::chrono::system_clock> _scorestart, _scorecheck;


    static int _current_speed;

public:
    Model(int w, int h);
    ~Model();

    void nextStep();
    Player* getPlayer();
    Counter* getCounterScore();
    Counter* getCounterCoin();
    Counter* getCounterDiamond();
    void getPlayerPosition(int &x, int &y);
    void setPlayerDirection(direction d);
    void setDifficulte(int d);

    static int getCurrentSpeed();

    std::vector<Coin *> *Coins();
    std::vector<Diamond *> *Diamonds();
    std::vector<Bonus *> *Awards();
    std::vector<Obstacle*>* Obstacles();

    void movePlayer();
    void addCoin();
    void addDiamond();
    void addBonus();
    void addObstacle();
    void drawInterface(sf::RenderWindow *w);
    void saveScore();
    void saveCoin();
    void saveDiamond();
    void save();
    void reset();
    void actualiseSpeed(int speed);
};
#endif
