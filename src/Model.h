#ifndef _MODEL_
#define _MODEL_
#include "main.h"
#include "Player.h"
#include "View.h"
#include "AnimatedSprite.h"
#include "Coin.h"
#include "Counter.h"
#include "Diamond.h"
#include "Bonus.h"
#include "Obstacle.h"
#include "utils.h"
#include "clock.h"

#include <chrono>
#include <ctime>
#include <math.h>

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

class View;

class Model
{
protected:
    int _w, _h;
    int _difficulte;
    static int _current_speed;
    int _diamonds_loose;

    Player _player;
    View* _view;

    bool _canpop;
    bool _magnetpicked;
    bool _paused;

    std::vector<Coin*> _coins;
    std::vector<Diamond*> _diamonds;
    std::vector<Bonus*> _bonus;
    std::vector<Obstacle*> _obstacles;

    Counter _coin_counter;
    Counter _score_counter;
    Counter _diamond_counter;

    BonusType bt;

    Clock _jump_timer;
    Clock _score_timer;
    Clock _game_timer;
    Clock _spawn_timer;
    Clock _bonus_timer;

public:
    Model(int w, int h);
    ~Model();


    void setView(View *view);
    Player* getPlayer();
    Counter* getCounterScore();
    Counter* getCounterCoin();
    Counter* getCounterDiamond();
    void setPlayerDirection(direction d);
    void setDifficulte(int d);
    bool is_paused() const;
    void set_paused(bool paused);
    static int getCurrentSpeed();
    int getDiamonds_loose() const;
    void addDiamonds_loose(int diamonds_loose);

    std::vector<Coin *> *Coins();
    std::vector<Diamond *> *Diamonds();
    std::vector<Bonus *> *Awards();
    std::vector<Obstacle*>* Obstacles();

    void nextStep();

    void movePlayer();

    void addCoin();
    void addDiamond();
    void addBonus();
    void addObstacle();

    void drawInterface(sf::RenderWindow *w);

    void saveScore();
    void saveCoin();
    void saveDiamond();
    void saveChoose();
    void save();

    void reset();

    void actualiseSpeed(int speed);

    bool looseMoney(int value, string type);

};
#endif
