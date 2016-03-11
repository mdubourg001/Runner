#include "Model.h"
#include <iostream>
#include <fstream>
using namespace std;

//=======================================
// Constructeurs
//=======================================
Model::Model(int w, int h)
  :  _w(w), _h(h), _player(SCREEN_WIDTH/15, SCREEN_HEIGHT-SCREEN_HEIGHT/5, 50, 50, 0, 0)
{

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
    movePlayer(_player.getDirection());

//    if(_player.isJumping())
//        _player.jump();
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
        _player.setMvtx(-10);
    }

    else if(d == r)
    {
        _player.changeDirection(r);
        _player.setMvtx(10);
    }

    else if(d == up)
    {
        ;
//        _player.setJumping(true);
//        _player.setMvty(-10);
    }

    else
        ;
}

void Model::movePlayer(direction d)
{
    _player.move();
}
