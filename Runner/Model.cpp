#include "Model.h"
#include <iostream>
#include <fstream>
#include "time.h"
using namespace std;

//----------!!!!!!!!!!!!!!!!!!!!
int i =0;
int randoume =0;
//-----------!!!!!!!!!!!!!!!!!!!

int Model::_current_speed = EASY_SPEED;

//=======================================
// Constructeurs
//=======================================
Model::Model(int w, int h)
    :  _w(w), _h(h), _player(SCREEN_WIDTH/15, SCREEN_HEIGHT-SCREEN_HEIGHT/5, 50, 50, 0, 0, 400, 0), _canpop(true), _magnetpicked(false), _magnetcpt(-1), _difficulte(0),
      _coin_counter(0, SCREEN_WIDTH -130, SCREEN_HEIGHT - 70, 50, 50),
      _score_counter(0, SCREEN_WIDTH - 500, SCREEN_HEIGHT-70, 50, 50),
      _diamond_counter(0, SCREEN_WIDTH - 300, SCREEN_HEIGHT-70, 50, 50)
{
    _coin_counter.setTexture("res/coin.png");
    _diamond_counter.setTexture("res/diamond.png");
    srand(time(NULL));


    _start = std::chrono::system_clock::now();
    _gamestart = std::chrono::system_clock::now();
}
//=======================================
// Destructeurs
//=======================================
Model::~Model(){}

//=======================================
// Calcul la prochaine étape
//=======================================
void Model::nextStep()
{
    _end = std::chrono::system_clock::now();
    _timecheck = std::chrono::system_clock::now();

    int timelapse = std::chrono::duration_cast<std::chrono::milliseconds>
            (_end-_start).count();
    int gametime = std::chrono::duration_cast<std::chrono::seconds>
            (_timecheck-_gamestart).count();

    if(gametime%20 == 0) //augmentation de la vitesse des objets en fonction du temps
    {
        _current_speed = MEDIUM_SPEED;
        actualiseSpeed(_current_speed);
    }
    else if(gametime%40 == 0)
    {
        _current_speed = HARD_SPEED;
        actualiseSpeed(_current_speed);
    }


    _score_counter.increment();

    movePlayer();
    _player.treatCollisions(_coins,_diamonds, _bonus, _obstacles);

    if(_player.isJumping())
    {
        _player.jump();
    }


    if((_score_counter.getValue() % 1000) == 0)

    {
        if (2000 - _difficulte >= 500)
            _difficulte += 200;
    }

    if(timelapse >= (2000-_difficulte))
    {
        _canpop = true;
        _start = std::chrono::system_clock::now();
    }

    if(_canpop)
    {
        randoume = rand();

        if(randoume%40 == 0)
        {
            addCoin();
            _canpop = false;
        }
        else if (randoume%4000 == 1)
        {
            addDiamond();
            _canpop = false;
        }
        else if (randoume%80 == 2 && _bonus.size()<1)
        {
            addBonus();
            _canpop = false;
        }

        else if(randoume%80 == 3)
        {
            addObstacle();
            _canpop = false;
        }
    }

    for(auto c : _coins) //supprime les pièces qui ne sont plus affichées à l'écran
    {
        if(c->getPosition().x < 0 || c->isPicked())
        {
            if(c->isPicked())
            {
                _coin_counter.increment();
                //c->drawAlpha();
            }

            std::vector<Coin*>::iterator it =
                    std::find(_coins.begin(), _coins.end(), c);
            _coins.erase(it);
        }
    }

    for(auto d : _diamonds)
    {
        if (d->getPosition().x < 0 || d->isPicked())
        {
            if(d->isPicked())
                _diamond_counter.increment();

            std::vector<Diamond*>::iterator it =
                    std::find(_diamonds.begin(), _diamonds.end(), d);
            _diamonds.erase(it);
        }
    }

    for(auto o : _obstacles)
    {
        if (o->getPosition().x < -100 || o->isDestroyed())
        {
            std::vector<Obstacle*>::iterator it =
                    std::find(_obstacles.begin(), _obstacles.end(), o);
            _obstacles.erase(it);
        }
    }

    for(auto b : _bonus)
    {
        if (b->getPosition().x < 0 || b->isPicked())
        {
            switch(bt)
            {
            case magnet:
                break;
            case randombonus:
                break;
            case shield:
                _player.winLife();
                break;
            case health:
                _player.winLife();
                break;
            case star:
                _player.setInvincibility(true);
                break;
            case feather:
                break;
            case hourglass:
                break;
            case redcoin:
                _coin_counter.hundredincrement();
                break;
            }
            std::vector<Bonus*>::iterator it =
                    std::find(_bonus.begin(), _bonus.end(), b);
            _bonus.erase(it);
        }
    }

    for_each(_coins.begin(), _coins.end(), [](Coin* &c){c->move();});
    for_each(_diamonds.begin(), _diamonds.end(), [](Diamond* &d){d->move();});
    for_each(_bonus.begin(), _bonus.end(), [](Bonus* &b){b->move();});
    for_each(_obstacles.begin(), _obstacles.end(), [](Obstacle* &o){o->move();});


}

//=======================================
// Autres méthodes
//=======================================
void Model::getPlayerPosition(int &x, int &y)
{
    x = _player.getPosx();
    y = _player.getPosy();
}

Player* Model::getPlayer()
{
    Player* ptr = &_player;
    return ptr;
}
Counter* Model::getCounterScore()
{
    Counter* ctr = &_score_counter;
    return ctr;
}

Counter* Model::getCounterCoin()
{
    Counter* ctr = &_coin_counter;
    return ctr;
}

Counter* Model::getCounterDiamond()
{
    Counter* ctr = &_diamond_counter;
    return ctr;
}

std::vector<Coin*>* Model::Coins()
{
    std::vector<Coin*>* ptr = &_coins;
    return ptr;
}

std::vector<Diamond*>* Model::Diamonds()
{
    std::vector<Diamond*>* ptr = &_diamonds;
    return ptr;
}

std::vector<Bonus*>* Model::Awards()
{
    std::vector<Bonus*>* ptr = &_bonus;
    return ptr;
}

std::vector<Obstacle*>* Model::Obstacles()
{
    std::vector<Obstacle*>* ptr = &_obstacles;
    return ptr;
}

void Model::setDifficulte(int d)
{
    _difficulte = d;
}

void Model::setPlayerDirection(direction d)
{
    if(d == none)
    {
        _player.changeDirection(none);
        _player.setMvtx(0);
    }

    else if(d == l)
    {
        _player.changeDirection(l);
        if(!_player.isJumping())
            _player.setMvtx(-10);
        else
            _player.setMvtx(-2);
    }

    else if(d == r)
    {
        _player.changeDirection(r);
        if(!_player.isJumping())
            _player.setMvtx(10);
        else
            _player.setMvtx(2);
    }

    else if(d == up)
    {
        _player.setJumping(true);
        _player.setMvty(-JUMP_INITIAL_SPEED);
    }
}

void Model::movePlayer()
{
    _player.move();
}

void Model::addCoin()
{
    _coins.push_back(new Coin("res/coinsprite.png", _current_speed, SCREEN_WIDTH + 10, SCREEN_HEIGHT-SCREEN_HEIGHT/2.5, 50, 50, 8));
}

void Model::addDiamond()
{
    _diamonds.push_back(new Diamond("res/diamondsprite.png", _current_speed, SCREEN_WIDTH + 10, SCREEN_HEIGHT-SCREEN_HEIGHT/2.5, 50, 50, 5));
}

void Model::addBonus()
{
    switch(rand()%9)
    {
    case 1:
        _bonus.push_back(new Bonus("res/aimant.png", _current_speed, SCREEN_WIDTH + 10, SCREEN_HEIGHT-SCREEN_HEIGHT/2.5, 50, 50, 7));
        bt = magnet;
        break;
    case 2:
        _bonus.push_back(new Bonus("res/aleatoire.png", _current_speed, SCREEN_WIDTH + 10, SCREEN_HEIGHT-SCREEN_HEIGHT/2.5, 50, 50, 14));
        bt = randombonus;
        break;
    case 3:
        _bonus.push_back(new Bonus("res/sablier.png", _current_speed, SCREEN_WIDTH + 10, SCREEN_HEIGHT-SCREEN_HEIGHT/2.5, 50, 50, 8));
        bt = hourglass;
        break;
    case 4:
        if(_player.getHealth() < 400)
        {
            _bonus.push_back(new Bonus("res/heart.png", _current_speed, SCREEN_WIDTH + 10, SCREEN_HEIGHT-SCREEN_HEIGHT/2.5, 50, 50, 7));
            bt = health;
        }
        else
        {
            _bonus.push_back(new Bonus("res/bouclier.png", _current_speed, SCREEN_WIDTH + 10, SCREEN_HEIGHT-SCREEN_HEIGHT/2.5, 50, 50, 0));
            bt = shield;
        }
        break;
    case 5:
        _bonus.push_back(new Bonus("res/etoile.png", _current_speed, SCREEN_WIDTH + 10, SCREEN_HEIGHT-SCREEN_HEIGHT/2.5, 50, 50, 6));
        bt = star;
        break;
    case 6:
        _bonus.push_back(new Bonus("res/plume.png", _current_speed, SCREEN_WIDTH + 10, SCREEN_HEIGHT-SCREEN_HEIGHT/2.5, 50, 50, 0));
        bt = feather;
        break;
    case 7:
        _bonus.push_back(new Bonus("res/redcoin.png", _current_speed, SCREEN_WIDTH + 10, SCREEN_HEIGHT-SCREEN_HEIGHT/2.5, 50, 50, 0));
        bt = redcoin;
        break;
    case 8:
        //teleportation ou lance ball
        break;
    }

}

void Model::addObstacle()
{
    _obstacles.push_back(new Obstacle(rand()%4+1, _current_speed));
}

void Model::drawInterface(sf::RenderWindow *w)
{
    _coin_counter.draw(w); //dessin du compteur de pièces
    _score_counter.draw(w); //dessin du compteur de score
    _diamond_counter.draw(w); //dessin du compteur de diamants
}

void Model::saveScore()
{
    int best=0; // peut etre faire des attributs de classes pour pouvoir gérer plus facilement lorsqu'on veut afficher le best score ou bien le nombre de pieces dans le menu
    fstream fichierScore;
    fichierScore.open(FICHIER_SCORE, ios::in );
    if( fichierScore.fail() )
    {
        cerr << "ouverture en lecture impossible" << endl;
        exit(EXIT_FAILURE);
    }
    fichierScore >> best;
    fichierScore.close();

    if(_score_counter.getValue() > best)
    {
        fichierScore.open(FICHIER_SCORE, ios::out);
        fichierScore << to_string(_score_counter.getValue());
        fichierScore.close();
    }
}

void Model::saveCoin()
{
    int total=0;
    fstream fichierCoins;
    fichierCoins.open(FICHIER_COIN, ios::in );
    if( fichierCoins.fail() )
    {
        cerr << "ouverture en lecture impossible" << endl;
        exit(EXIT_FAILURE);
    }
    fichierCoins >> total;
    total += _coin_counter.getValue();
    fichierCoins.close();

    fichierCoins.open(FICHIER_COIN, ios::out);
    fichierCoins << to_string(total);
    fichierCoins.close();
}

void Model::saveDiamond()
{
    int total=0;
    fstream fichierDiamonds;
    fichierDiamonds.open(FICHIER_DIAMOND, ios::in );
    if( fichierDiamonds.fail() )
    {
        cerr << "ouverture en lecture impossible" << endl;
        exit(EXIT_FAILURE);
    }
    fichierDiamonds >> total;
    total += _diamond_counter.getValue();
    fichierDiamonds.close();

    fichierDiamonds.open(FICHIER_DIAMOND, ios::out);
    fichierDiamonds << to_string(total);
    fichierDiamonds.close();
}

void Model::save()
{
    this->saveScore();
    this->saveCoin();
    this->saveDiamond();
}

void Model::reset()
{
    _coin_counter.setValue(0);
    _diamond_counter.setValue(0);
    _score_counter.setValue(0);
    _player.setPosition(SCREEN_WIDTH/15, SCREEN_HEIGHT-SCREEN_HEIGHT/5);
    _coins.clear();
    _obstacles.clear();
    _diamonds.clear();
    _bonus.clear();
    _player.setHealth(400);
    _player.setShield(0);
    _current_speed = EASY_SPEED;
}

void Model::actualiseSpeed(int speed)
{
    for(auto c : _coins) {c->actualiseSpeed(speed) ;}
    for(auto d : _diamonds) {d->actualiseSpeed(speed) ;}
    for(auto b : _bonus) {b->actualiseSpeed(speed) ;}
    for(auto o : _obstacles) {o->actualiseSpeed(speed) ;}
}

int Model::getCurrentSpeed()
{
    return _current_speed;
}
