#include "Model.h"
#include <iostream>
#include <fstream>
#include "time.h"
using namespace std;

//=======================================
// Constructeurs
//=======================================
Model::Model(int w, int h)
  :  _w(w), _h(h), _player(SCREEN_WIDTH/15, SCREEN_HEIGHT-SCREEN_HEIGHT/5, 50, 50, 0, 0), _canpop(true), _magnetpicked(false), _magnetcpt(-1),
    _framecpt(FRAMERATE_LIMIT), _coin_counter(0, SCREEN_WIDTH -130, SCREEN_HEIGHT - 70, 50, 50),
    _score_counter(0, SCREEN_WIDTH - 500, SCREEN_HEIGHT-70, 50, 50),
    _diamond_counter(0, SCREEN_WIDTH - 300, SCREEN_HEIGHT-70, 50, 50)
{
    _coin_counter.setTexture("res/coin.png");
    _diamond_counter.setTexture("res/diamond.png");
    srand(time(NULL));

    _font.loadFromFile(POLICE);

    _healthText.setFont(_font);
    _healthText.setColor(sf::Color::Black);
    _healthText.setString("SANTE :");
    _healthText.setCharacterSize(60);
    _healthText.setPosition(10,690);

    _healthRect.setSize(sf::Vector2f(400,50));
    _healthRect.setPosition(200,710);
    _healthRect.setFillColor(sf::Color(100,255,100,255));


    _backhealthRect.setSize(sf::Vector2f(400,50));
    _backhealthRect.setPosition(200,710);
    _backhealthRect.setFillColor(sf::Color(255,100,100,255));
    _backhealthRect.setOutlineThickness(3);
    _backhealthRect.setOutlineColor(sf::Color::Black);

    _shellRect.setSize(sf::Vector2f(-50,50));
    _shellRect.setPosition(600,710);
    _shellRect.setFillColor(sf::Color(170,170,170,255));
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
    _framecpt--;
    movePlayer();
    _player.treatCollisions(_coins,_diamonds, _bonus);

    if(_player.isJumping())
    {
        _player.jump();
    }

    if(_framecpt == 0)
        _canpop = true;

    if(_canpop)
    {
        if(rand()%40 == 0)
        {
            addCoin();
            _canpop = false;
            _framecpt = 15;
        }
        else if (rand()%4000 == 0)
        {
            addDiamond();
            _canpop = false;
            _framecpt = 15;
        }
        else if (rand()%400 == 0 && _bonus.size()<1)
        {
            addBonus();
            _canpop = false;
            _framecpt = 15;
        }
    }

    for(int i=0 ; i<_coins.size() ; i++) //supprime les pièces qui ne sont plus affichées à l'écran
    {
        if(_coins.at(i)->getPosition().x < 0 || _coins.at(i)->isPicked())
        {
            if(_coins.at(i)->isPicked())
                _coin_counter.increment();
            _coins.erase(_coins.begin() + i );
        }

    }
    for(int i=0; i<_diamonds.size();i++)
    {
        if (_diamonds.at(i)->getPosition().x < 0 || _diamonds.at(i)->isPicked())
        {
            if(_diamonds.at(i)->isPicked())
                _diamond_counter.increment();
            _diamonds.erase(_diamonds.begin() + i);
        }
    }
    for(int i=0; i<_bonus.size();i++)
    {
        if (_bonus.at(i)->getPosition().x < 0 || _bonus.at(i)->isPicked())
        {
            if(_bonus.at(i)->isPicked())
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
                    winLife();
                    break;
                case health:
                    winLife();
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
            _bonus.erase(_bonus.begin() + i);
        }
    }

    if(bt==magnet && _magnetpicked == true)
        for_each(_coins.begin(), _coins.end(), [](Coin* &c){c->moveMagnet();});
    else
        for_each(_coins.begin(), _coins.end(), [](Coin* &c){c->move();});

    if(_magnetcpt==2000)
    {
        _magnetpicked = false;
        _magnetcpt = -1;
    }
    else if (_magnetcpt>-1)
    {
        _magnetcpt++;
        cout << _magnetcpt << endl;
    }

    for_each(_diamonds.begin(), _diamonds.end(), [](Diamond* &d){d->move();});
    for_each(_bonus.begin(), _bonus.end(), [](Bonus* &b){b->move();});

    looseLife();
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

void Model::addDiamond()
{
    _diamonds.push_back(new Diamond("res/diamond.png", 5, SCREEN_WIDTH + 10, SCREEN_HEIGHT-SCREEN_HEIGHT/2.5, 50, 50, 0));
}

void Model::addBonus()
{
    switch(rand()%9)
    {
    case 1:
        _bonus.push_back(new Bonus("res/aimant.png", 5, SCREEN_WIDTH + 10, SCREEN_HEIGHT-SCREEN_HEIGHT/2.5, 50, 50, 0));
        bt = magnet;
        break;
    case 2:
        _bonus.push_back(new Bonus("res/aleatoire.png", 5, SCREEN_WIDTH + 10, SCREEN_HEIGHT-SCREEN_HEIGHT/2.5, 50, 50, 0));
        bt = randombonus;
        break;
    case 3:
        _bonus.push_back(new Bonus("res/sablier.png", 5, SCREEN_WIDTH + 10, SCREEN_HEIGHT-SCREEN_HEIGHT/2.5, 50, 50, 0));
        bt = hourglass;
        break;
    case 4:
        if(_healthRect.getSize().x < 400)
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
        _bonus.push_back(new Bonus("res/etoile.png", 5, SCREEN_WIDTH + 10, SCREEN_HEIGHT-SCREEN_HEIGHT/2.5, 50, 50, 0));
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

void Model::drawInterface(sf::RenderWindow *w)
{
    _coin_counter.draw(w); //dessin du compteur de pièces
    _score_counter.draw(w); //dessin du compteur de score
    _diamond_counter.draw(w); //dessin du compteur de diamants
    w->draw(_backhealthRect); //dessin du fond de vie (rouge)
    w->draw(_healthRect); // dessin de la vie (vert)
    w->draw(_healthText); // dessin du texte de la vie
    w->draw(_shellRect); // dessin du bouclier
}

void Model::looseLife()
{
    if(_shellRect.getSize().x<0)
        _shellRect.setSize(sf::Vector2f(_shellRect.getSize().x+1,_shellRect.getSize().y));
    else if(_healthRect.getSize().x>0)
        _healthRect.setSize(sf::Vector2f(_healthRect.getSize().x-1,_healthRect.getSize().y));
}

void Model::winLife()
{
    if(_healthRect.getSize().x<400)
        _healthRect.setSize(sf::Vector2f(_healthRect.getSize().x+50,_healthRect.getSize().y));
    else if (_shellRect.getSize().x>-400)
        _shellRect.setSize(sf::Vector2f(_shellRect.getSize().x-50,_shellRect.getSize().y));
}
