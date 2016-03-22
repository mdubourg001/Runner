#include "Model.h"
#include <iostream>
#include <fstream>
using namespace std;

//=======================================
// Constructeurs
//=======================================
Model::Model(int w, int h)
  :  _w(w), _h(h), _player(SCREEN_WIDTH/15, SCREEN_HEIGHT-SCREEN_HEIGHT/5, 50, 50, 0, 0),
    _cpt(180), _coin_counter(0, SCREEN_WIDTH - 100, SCREEN_HEIGHT - 100, 50, 50)
{
    _coin_counter.setTexture("res/coin.png");
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
    _cpt--;
    movePlayer();
    _player.treatCollisions(_coins);

    if(_player.isJumping())
    {
        _player.jump();
    }

    if(_cpt==0)
    {
        addCoin();
        _cpt = 180;
    }

    for(int i=0 ; i<_coins.size() ; i++) //supprime les pièces qui ne sont plus affichées à l'écran
        if(_coins.at(i)->getPosition().x < 0 || _coins.at(i)->isPicked())
        {
            if(_coins.at(i)->isPicked())
                _coin_counter.increment();
            _coins.erase(_coins.begin() + i );
        }

    for_each(_coins.begin(), _coins.end(), [](Coin* &c){c->move();});
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
        _player.setMvty(-JUMP_HEIGHT);
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

void Model::drawInterface(sf::RenderWindow *w)
{
    _coin_counter.draw(w); //dessin du compteur de pièces
}
