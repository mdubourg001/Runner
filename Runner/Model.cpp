#include "Model.h"
#include <iostream>
#include <fstream>
#include "time.h"
using namespace std;

//=======================================
// Constructeurs
//=======================================
Model::Model(int w, int h)
  :  _w(w), _h(h), _player(SCREEN_WIDTH/15, SCREEN_HEIGHT-SCREEN_HEIGHT/5, 50, 50, 0, 0, 400, 0), _canpop(true), _magnetpicked(false), _magnetcpt(-1),
     _coin_counter(0, SCREEN_WIDTH -130, SCREEN_HEIGHT - 70, 50, 50),
    _score_counter(0, SCREEN_WIDTH - 500, SCREEN_HEIGHT-70, 50, 50),
    _diamond_counter(0, SCREEN_WIDTH - 300, SCREEN_HEIGHT-70, 50, 50)
{
    _coin_counter.setTexture("res/coin.png");
    _diamond_counter.setTexture("res/diamond.png");
    srand(time(NULL));


    _start = std::chrono::system_clock::now();
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
    int timelapse = std::chrono::duration_cast<std::chrono::milliseconds>
            (_end-_start).count();

    _score_counter.increment();

    movePlayer();
    _player.treatCollisions(_coins,_diamonds, _bonus, _obstacles);

    if(_player.isJumping())
    {
        _player.jump();
    }

    if(timelapse >= 800)
    {
        _canpop = true;
        _start = std::chrono::system_clock::now();
    }

    if(_canpop)
    {
        if(rand()%40 == 0)
        {
            addCoin();
            _canpop = false;
        }
        else if (rand()%4000 == 0)
        {
            addDiamond();
            _canpop = false;
        }
        else if (rand()%400 == 0 && _bonus.size()<1)
        {
            addBonus();
            _canpop = false;
        }

        else if(rand()%80 == 0)
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
            if(b->isPicked())
            {
                switch(bt)
                {
                case magnet:
                    _magnetpicked = true;
                    _magnetcpt = 0;
                    break;
                case randombonus:
                    _magnetcpt = 2000;
                    break;
                case shield:                    
                    _player.winLife();
                    break;
                case health:
                    _player.winLife();
                    break;
                case star:
                    _magnetcpt = 2000;
                    break;
                case feather:
                    _magnetcpt = 2000;
                    break;
                case hourglass:
                    _magnetcpt = 2000;
                    break;
                case redcoin:
                    _coin_counter.hundredincrement();
                    break;
                }
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
    _coins.push_back(new Coin("res/coinsprite.png", 5, SCREEN_WIDTH + 10, SCREEN_HEIGHT-SCREEN_HEIGHT/2.5, 47, 50, 8));
}

void Model::addDiamond()
{
    _diamonds.push_back(new Diamond("res/diamondsprite.png", 5, SCREEN_WIDTH + 10, SCREEN_HEIGHT-SCREEN_HEIGHT/2.5, 50, 50, 5));
}

void Model::addBonus()
{
    switch(rand()%9)
    {
    case 1:
        _bonus.push_back(new Bonus("res/aimant.png", 5, SCREEN_WIDTH + 10, SCREEN_HEIGHT-SCREEN_HEIGHT/2.5, 50, 50, 7));
        bt = magnet;
        break;
    case 2:
        _bonus.push_back(new Bonus("res/aleatoire.png", 5, SCREEN_WIDTH + 10, SCREEN_HEIGHT-SCREEN_HEIGHT/2.5, 50, 50, 14));
        bt = randombonus;
        break;
    case 3:
        _bonus.push_back(new Bonus("res/sablier.png", 5, SCREEN_WIDTH + 10, SCREEN_HEIGHT-SCREEN_HEIGHT/2.5, 50, 50, 8));
        bt = hourglass;
        break;
    case 4:
        if(_player.getHealth() < 400)
        {
            _bonus.push_back(new Bonus("res/sante.png", 5, SCREEN_WIDTH + 10, SCREEN_HEIGHT-SCREEN_HEIGHT/2.5, 50, 50, 0));
            bt = health;
        }
        else
        {
            _bonus.push_back(new Bonus("res/bouclier.png", 5, SCREEN_WIDTH + 10, SCREEN_HEIGHT-SCREEN_HEIGHT/2.5, 50, 50, 0));
            bt = shield;
        }
        break;
    case 5:
        _bonus.push_back(new Bonus("res/etoile.png", 5, SCREEN_WIDTH + 10, SCREEN_HEIGHT-SCREEN_HEIGHT/2.5, 50, 50, 6));
        bt = star;
        break;
    case 6:
        _bonus.push_back(new Bonus("res/plume.png", 5, SCREEN_WIDTH + 10, SCREEN_HEIGHT-SCREEN_HEIGHT/2.5, 50, 50, 0));
        bt = feather;
        break;
    case 7:
        _bonus.push_back(new Bonus("res/redcoin.png", 5, SCREEN_WIDTH + 10, SCREEN_HEIGHT-SCREEN_HEIGHT/2.5, 50, 50, 0));
        bt = redcoin;
        break;
    case 8:
        //teleportation ou lance ball
        break;
    }

}

void Model::addObstacle()
{
    _obstacles.push_back(new Obstacle(rand()%3+1));
}

void Model::drawInterface(sf::RenderWindow *w)
{
    _coin_counter.draw(w); //dessin du compteur de pièces
    _score_counter.draw(w); //dessin du compteur de score
    _diamond_counter.draw(w); //dessin du compteur de diamants
}

/*void Model::saveScore()
{
    int best=0; // peut etre faire des attributs de classes pour pouvoir gérer plus facilement lorsqu'on veut afficher le best score ou bien le nombre de pieces dans le menu
    fstream fichierScore;
    fichierScore.open("scores.txt", ios::in );
    if( fichierScore.fail() )
    {
        cerr << "ouverture en lecture impossible" << endl;
        exit(EXIT_FAILURE);
    }
    fichierScore >> best;
    fichierScore.close();

    if(_score_counter > best)
    {
        fichierScore.open("scores.txt", ios::out);
        fichierScore << to_string(_score_counter);
        fichierScore.close();
    }
}

void Model::saveCoin()
{
    int total=0;
    fstream fichierCoins;
    fichierCoins.open("coins.txt", ios::in );
    if( fichierCoin.fail() )
    {
        cerr << "ouverture en lecture impossible" << endl;
        exit(EXIT_FAILURE);
    }
    fichierCoins >> total;
    total += _coin_counter;
    fichierCoins.close();

    fichierCoins.open("coins.txt", ios::out);
    fichierCoins << total;
    fichierCoins.close();
}

void Model::saveDiamond()
{
    int total=0;
    fstream fichierDiamonds;
    fichierDiamonds.open("diamonds.txt", ios::in );
    if( fichierDiamonds.fail() )
    {
        cerr << "ouverture en lecture impossible" << endl;
        exit(EXIT_FAILURE);
    }
    fichierDiamonds >> total;
    total += _diamond_counter;
    fichierDiamonds.close();

    fichierDiamonds.open("diamonds.txt", ios::out);
    fichierDiamonds << total;
    fichierDiamonds.close();
}*/
