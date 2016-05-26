#include "Model.h"
#include <iostream>
#include <fstream>
#include "time.h"
using namespace std;


int Model::_current_speed = EASY_SPEED;

//=======================================
// Constructeurs & Destructeur
//=======================================

Model::Model(int w, int h)
    :  _w(w), _h(h), _difficulte(0), _diamonds_loose(0),
      _player(SCREEN_WIDTH/15, SCREEN_HEIGHT-SCREEN_HEIGHT/5, 50, 50, 0, 0, 400, 0),
      _canpop(true), _magnetpicked(false),_paused(false),
      _coin_counter(0, POS_X_COIN_COUNTER, POS_Y_COUNTER),
      _score_counter(0, POS_X_SCORE_COUNTER, POS_Y_COUNTER),
      _diamond_counter(0, POS_X_DIAMOND_COUNTER, POS_Y_COUNTER)

{
    _coin_counter.setTexture(ONE_COIN);
    _diamond_counter.setTexture(ONE_DIAMOND);

    _highscores = vector<pair<string, long>>();
    _highscores.resize(5);
    for(unsigned int i = 0 ; i < 5 ; i++)
    {
        _highscores.push_back(pair<string, long>());
    }

    srand(time(NULL));

    _jump_timer.set_alarm(Moment(0, 0, 0, 11, 0));

    _score_timer.set_alarm(Moment(0, 0, 0, 100, 0));
    _score_timer.start();

    _game_timer.set_alarm(Moment(0, 0, 20, 0, 0));
    _game_timer.start();

    _spawn_timer.set_alarm(Moment(0, 0, 0, 2000 -_difficulte, 0));
    _spawn_timer.start();

    _bonus_timer.set_alarm(Moment(0, 0, 10, 0, 0));
}

Model::~Model()
{ }

//==================ACCESSEURS========================

void Model::setView(View *view)
{ _view = view; }

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
        _jump_timer.start();
        _player.setJumping(true);
        _player.setMvty(-JUMP_INITIAL_SPEED);
    }
}

void Model::setDifficulte(int d)
{ _difficulte = d; }

bool Model::is_paused() const
{ return _paused; }

void Model::set_paused(bool paused)
{ _paused = paused; }

int Model::getCurrentSpeed()
{ return _current_speed; }

int Model::getDiamonds_loose() const
{ return _diamonds_loose; }

void Model::addDiamonds_loose(int diamonds_loose)
{ _diamonds_loose += diamonds_loose; }

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

std::vector<pair<string, long> > *Model::Highscores()
{
    std::vector<pair<string, long> >* ptr = &_highscores;
    return ptr;
}


//====================================================

//==================AUTRES METHODES===================

/*!
 * \brief Model::nextStep
 * calcule la prochaine étape de jeu:
     * le temps de jeu -> calcul de la vitesse des objets
     * déplacement du joueur et saut du joueur
     * traitement des collisions
     * incrémentation du score
     * apparition des obstacles
     * anime tout les objets et supprime ceux qui ne sont plus affichés à l'écran
 */
void Model::nextStep()
{
    if(!is_paused() && !_player.is_dead())
    {
        movePlayer();
        _player.treatCollisions(_coins,_diamonds, _bonus, _obstacles);
        if(_player.getHealth() == 0)
            _player.set_dead(true);

        _jump_timer.update();
        _jump_timer.check_time();

        _score_timer.update();
        _score_timer.check_time();

        _game_timer.update();
        _game_timer.check_time();

        _spawn_timer.update();
        _spawn_timer.check_time();

        _bonus_timer.update();
        _bonus_timer.check_time();

        if(_score_timer.is_running() && _score_timer.has_ticked())
        {
            _score_counter.increment();
            _score_timer.reset();
        }

        if(_game_timer.is_running() && _game_timer.has_ticked())
        {
            _game_timer.reset();
            if(_current_speed == EASY_SPEED)
                _current_speed = MEDIUM_SPEED;
            else
                _current_speed = HARD_SPEED;
            actualiseSpeed(_current_speed);
        }

        if(_player.isJumping() && _jump_timer.has_ticked() && _jump_timer.is_running())
        {
            _jump_timer.reset();
            _player.jump();
        }
        else if(!_jump_timer.is_running())
        {
            _jump_timer.stop();
            _jump_timer.reset();
        }

        if((_score_counter.getValue() % 1000) == 0)
        {
            if (2000 - _difficulte >= 500)
                _difficulte += 200;
        }

        if(_bonus_timer.is_running() && _bonus_timer.has_ticked())
        {
            _bonus_timer.stop();
            _bonus_timer.reset();
            _player.setInvincibility(false);
            _magnetpicked = false;
            if(_game_timer.get_time_since_begin().get_sec() >= 40)
                _current_speed = HARD_SPEED;
            else if(_game_timer.get_time_since_begin().get_sec() >= 20)
                _current_speed = MEDIUM_SPEED;
            else
                _current_speed = EASY_SPEED;
        }

        if(_spawn_timer.is_running() && _spawn_timer.has_ticked())
        {
            _spawn_timer.set_alarm(Moment(0, 0, 0, 2000 - _difficulte, 0));
            _spawn_timer.reset();
            _canpop = true;
        }

        if(_canpop)
        {
            if(rand()%40 == 0)
            {
                addCoin();
                _canpop = false;
            }
            else if (rand()%4000 == 1)
            {
                addDiamond();
                _canpop = false;
            }
            else if (rand()%80 == 2 && _bonus.size()<1)
            {
                addBonus();
                _canpop = false;
            }

            else if(rand()%80 == 3)
            {
                addObstacle();
                _canpop = false;
            }
        }

        for(auto c : _coins) //supprime les pièces qui ne sont plus affichées à l'écran
        {
            if(c->isPicked())
            {
                if(c->clock_has_ticked())
                {
                    c->setDestroyed(true);
                }
            }
            if(c->getPosition().x < 0 || c->getDestroyed())
            {
                if(c->isPicked())
                    _coin_counter.increment();
                c->set_ball_detected(false);

                std::vector<Coin*>::iterator it =
                        std::find(_coins.begin(), _coins.end(), c);
                delete *it;
                _coins.erase(it);
            }
            else if(distance(c->getPosition(), _player.getPos()) < DETECTION_RADIUS)
                c->set_ball_detected(true);
        }

        for(auto d : _diamonds)
        {
            if (d->getPosition().x < 0 || d->isPicked())
            {
                if(d->isPicked())
                    _diamond_counter.increment();

                std::vector<Diamond*>::iterator it =
                        std::find(_diamonds.begin(), _diamonds.end(), d);
                delete *it;
                _diamonds.erase(it);
            }
        }

        for(auto o : _obstacles)
        {
            if (o->getPosition().x < -100 || o->isDestroyed())
            {
                std::vector<Obstacle*>::iterator it =
                        std::find(_obstacles.begin(), _obstacles.end(), o);
                delete *it;
                _obstacles.erase(it);
            }
        }

        for(auto b : _bonus)
        {
            if (b->getPosition().x < 0 || b->isPicked())
            {
                if (b->isPicked())
                {
                    _player.setInvincibility(false);
                    switch(bt)
                    {
                    case randombonus:
                        int t;
                        t = (rand()%6);
                        switch(t)
                        {
                        case 0:
                            _magnetpicked = true;
                            _bonus_timer.reset();
                            _bonus_timer.start();
                            break;
                        case 1:
                            _player.winLife();
                            break;
                        case 2:
                            _player.setInvincibility(true);
                            _bonus_timer.reset();
                            _bonus_timer.start();
                            break;
                        case 3:
                            /* BONUS PLUME */
                            break;
                        case 4:
                            _current_speed = HOURGLASS_SPEED;
                            actualiseSpeed(HOURGLASS_SPEED);
                            _bonus_timer.reset();
                            _bonus_timer.start();
                            break;
                        case 5:
                            _coin_counter.hundredincrement();
                            break;
                        }
                        break;
                    case magnet:
                        _magnetpicked = true;
                        _bonus_timer.reset();
                        _bonus_timer.start();
                        break;
                    case shield:
                        _player.winLife();
                        break;
                    case health:
                        _player.winLife();
                        break;
                    case star:
                        _player.setInvincibility(true);
                        _bonus_timer.reset();
                        _bonus_timer.start();
                        break;
                    case feather:
                        /* BONUS PLUME */
                        break;
                    case hourglass:
                        _current_speed = HOURGLASS_SPEED;
                        actualiseSpeed(HOURGLASS_SPEED);
                        _bonus_timer.reset();
                        _bonus_timer.start();
                        break;
                    case redcoin:
                        _coin_counter.hundredincrement();
                        break;
                    default:
                        break;
                    }
                }
                std::vector<Bonus*>::iterator it =
                        std::find(_bonus.begin(), _bonus.end(), b);
                delete *it;
                _bonus.erase(it);
            }
        }

        if(_magnetpicked)
            for(auto c: _coins)
            {
                if(c->get_ball_detected())
                    c->move_magnet(&_player);
                else
                    c->move();
            }
        else
            for_each(_coins.begin(), _coins.end(), [](Coin* &c){c->move();});
        for_each(_diamonds.begin(), _diamonds.end(), [](Diamond* &d){d->move();});
        for_each(_bonus.begin(), _bonus.end(), [](Bonus* &b){b->move();});
        for_each(_obstacles.begin(), _obstacles.end(), [](Obstacle* &o){o->move();});
    }
}


/*!
 * \brief Model::movePlayer
 */
void Model::movePlayer()
{
    _player.move();
}


/*!
 * \brief Model::addCoin
 * ajoute une pièce au vector de pièces
 */
void Model::addCoin()
{
    _coins.push_back(new Coin(COIN, _current_speed, SCREEN_WIDTH + 10, SCREEN_HEIGHT-SCREEN_HEIGHT/2.5, 50, 50, 8));
}


/*!
 * \brief Model::addDiamond
 * ajoute un diamant au vector de diamants
 */
void Model::addDiamond()
{
    _diamonds.push_back(new Diamond(DIAMOND, _current_speed, SCREEN_WIDTH + 10, SCREEN_HEIGHT-SCREEN_HEIGHT/2.5, 50, 50, 5));
}


/*!
 * \brief Model::addBonus
 * ajoute un bonus au vecteur de bonus
 */
void Model::addBonus()
{
    switch(rand()%8)
    {
    case 1:
        _bonus.push_back(new Bonus(MAGNET, _current_speed, SCREEN_WIDTH + 10, SCREEN_HEIGHT-SCREEN_HEIGHT/2.5, 50, 50, 7));
        bt = magnet;
        break;
    case 2:
        _bonus.push_back(new Bonus(RANDOMBONUS, _current_speed, SCREEN_WIDTH + 10, SCREEN_HEIGHT-SCREEN_HEIGHT/2.5, 50, 50, 14));
        bt = randombonus;
        break;
    case 3:
        _bonus.push_back(new Bonus(HOURGLASS, _current_speed, SCREEN_WIDTH + 10, SCREEN_HEIGHT-SCREEN_HEIGHT/2.5, 50, 50, 8));
        bt = hourglass;
        break;
    case 4:
        if(_player.getHealth() < 400)
        {
            _bonus.push_back(new Bonus(HEART, _current_speed, SCREEN_WIDTH + 10, SCREEN_HEIGHT-SCREEN_HEIGHT/2.5, 50, 50, 7));
            bt = health;
        }
        else
        {
            _bonus.push_back(new Bonus(SHIELD, _current_speed, SCREEN_WIDTH + 10, SCREEN_HEIGHT-SCREEN_HEIGHT/2.5, 50, 50, 0));
            bt = shield;
        }
        break;
    case 5:
        _bonus.push_back(new Bonus(STAR, _current_speed, SCREEN_WIDTH + 10, SCREEN_HEIGHT-SCREEN_HEIGHT/2.5, 50, 50, 6));
        bt = star;
        break;
    case 6:
        _bonus.push_back(new Bonus(FEATHER, _current_speed, SCREEN_WIDTH + 10, SCREEN_HEIGHT-SCREEN_HEIGHT/2.5, 50, 50, 0));
        bt = feather;
        break;
    case 7:
        _bonus.push_back(new Bonus(REDCOIN, _current_speed, SCREEN_WIDTH + 10, SCREEN_HEIGHT-SCREEN_HEIGHT/2.5, 50, 50, 0));
        bt = redcoin;
        break;
    }
}


/*!
 * \brief Model::addObstacle
 * ajoute un obstacle au vecteur d'obstacle
 */
void Model::addObstacle()
{
    _obstacles.push_back(new Obstacle(rand()%4+1, _current_speed));
}


/*!
 * \brief Model::drawInterface
 * \param w
 * dessine les compteurs de pièces/diamants/score
 */
void Model::drawInterface(sf::RenderWindow *w)
{
    _coin_counter.draw(w); //dessin du compteur de pièces
    _score_counter.draw(w); //dessin du compteur de score
    _diamond_counter.draw(w); //dessin du compteur de diamants
}


/*!
 * \brief Model::saveScore
 * sauvegarde le score dans le fichier de highscores
 */
void Model::saveScore()
{
    vector<pair<string, long>> temp_scores(5);
    bool asChanged = false;
    unsigned int it = 0;
    string temp;
    ifstream readHS(FICHIER_SCORE, ios::in);
    if(readHS)
    {
        while(getline(readHS, temp) && it < NBR_SCORES)
        {
            temp_scores.at(it).first = temp.substr(0, temp.find(" ")); //on récupère le pseudo du joueur
            temp_scores.at(it).second = atol(temp.substr(temp.find(" "), temp.length()-1).c_str()); //et son score
            it++;
        }
        readHS.close();
    }
    else
        cerr << "IMPOSSIBLE D'OUVRIR " << FICHIER_SCORE << endl;

    for(unsigned int i=0; i<NBR_SCORES && !asChanged;i++)
    {
        if(temp_scores.at(i).second < _score_counter.getValue())
        {
            asChanged = true;

            for(unsigned int j=4;j>i-1;j--)
                temp_scores.at(j) = temp_scores.at(j-1);
            temp_scores.at(i) = make_pair((_view->get_player_name().empty() ? "noname" : _view->get_player_name())
                                          , _score_counter.getValue());
            _score_counter.setValue(0);
        }
    }
    if(asChanged)
    {
        _highscores = temp_scores;
        ofstream writeHS(FICHIER_SCORE, ios::out);
        if(writeHS)
        {
            for(unsigned int i=0; i<NBR_SCORES; i++)
                writeHS << _highscores.at(i).first + " " + to_string(_highscores.at(i).second) << endl;
            writeHS.close();
        }
        else
        {
            cerr << "ouverture en écriture impossible";
            exit(EXIT_FAILURE);
        }
    }
}


/*!
 * \brief Model::saveCoin
 * sauvegarde les pièces dans le fichier de pièces
 */
void Model::saveCoin()
{
    int total = 0;
    ifstream readCoins(FICHIER_COIN, ios::in);
    if(readCoins)
    {
        readCoins >> total;
        readCoins.close();
    }
    else
    {
        cerr << "ouverture en lecture impossible";
        exit(EXIT_FAILURE);
    }
    if(_coin_counter.getValue() > 0)
    {
        ofstream writeCoins(FICHIER_COIN, ios::out);
        if(writeCoins)
        {
            total += _coin_counter.getValue();
            writeCoins << to_string(total);
            writeCoins.close();
        }
        else
        {
            cerr << "ouverture en écriture impossible";
            exit(EXIT_FAILURE);
        }
    }
}


/*!
 * \brief Model::saveDiamond
 * sauvegarde les diamants dans le fichier de diamants
 */
void Model::saveDiamond()
{
    int total = 0;
    ifstream readDiamonds(FICHIER_DIAMOND, ios::in);
    if(readDiamonds)
    {
        readDiamonds >> total;
        readDiamonds.close();
    }
    else
    {
        cerr << "ouverture en lecture impossible";
        exit(EXIT_FAILURE);
    }
    if(_diamond_counter.getValue() > 0 || _diamonds_loose > 0)
    {
        ofstream writeDiamonds(FICHIER_DIAMOND, ios::out);
        if(writeDiamonds)
        {
            total += _diamond_counter.getValue();
            total -= _diamonds_loose;
            writeDiamonds << to_string(total);
            writeDiamonds.close();
        }
        else
        {
            cerr << "ouverture en écriture impossible";
            exit(EXIT_FAILURE);
        }
    }
}

void Model::saveChoose()
{
    ofstream writeChoose (FICHIER_CHOOSE, ios::in);
    if(writeChoose)
    {
        if(_view->getAsChanged())
        {
            writeChoose << _view->getBall_choose() << endl;
            writeChoose << _view->getBack_choose() << endl;
        }
    }
    else
    {
        cerr << "ouverture en écriture impossible";
        exit(EXIT_FAILURE);
    }
}

/*!
 * \brief Model::save
 * sauvegarde le jeu
 */
void Model::save()
{
    this->saveScore();
    this->saveCoin();
    this->saveDiamond();
    this->saveChoose();
}


/*!
 * \brief Model::reset
 * reset le model à 0
 */
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
    _player.setHealth(BALL_LIFE);
    _player.setShield(0);
    _player.set_dead(false);
    _player.set_nb_deaths(0);
    this->setPlayerDirection(none);
    _current_speed = EASY_SPEED;
    _magnetpicked = false;
    _score_timer.reset();
    _diamonds_loose = 0;
}

void Model::reset_highscores()
{
    ofstream writeHS(FICHIER_SCORE, ios::out);
    if(writeHS)
    {
        for(unsigned int i=0; i<NBR_SCORES; i++)
            writeHS << "NOONE" << " " << to_string(0) << endl;
        writeHS.close();
    }
    else
    {
        cerr << "ouverture en écriture impossible";
        exit(EXIT_FAILURE);
    }
}


/*!
 * \brief Model::actualiseSpeed
 * \param speed
 * actualise la vitesse des objets du jeu
 */
void Model::actualiseSpeed(int speed)
{
    for(auto c : _coins) {c->actualiseSpeed(speed) ;}
    for(auto d : _diamonds) {d->actualiseSpeed(speed) ;}
    for(auto b : _bonus) {b->actualiseSpeed(speed) ;}
    for(auto o : _obstacles) {o->actualiseSpeed(speed) ;}
}

bool Model::looseMoney(int value, string type)
{
    if(type == "coins")
    {
        int totalCoins;
        ifstream readTotalCoins(FICHIER_COIN, ios::in);
        if(readTotalCoins)
        {
            readTotalCoins >> totalCoins;
            readTotalCoins.close();
        }
        else
        {
            cerr << "ouverture en lecture impossible";
            exit(EXIT_FAILURE);
        }
        if(value <= totalCoins)
        {
            ofstream writeCoins(FICHIER_COIN, ios::out);
            if(writeCoins)
            {
                totalCoins -= value;
                writeCoins << totalCoins;
                writeCoins.close();
            }
            else
            {
                cerr << "ouverture en lecture impossible";
                exit(EXIT_FAILURE);
            }
            return true;
        }

    }
    else if (type == "diamonds")
    {
        int totalDiamonds;
        ifstream readTotalDiamonds(FICHIER_DIAMOND, ios::in);
        if(readTotalDiamonds)
        {
            readTotalDiamonds >> totalDiamonds;
            readTotalDiamonds.close();
        }
        else
        {
            cerr << "ouverture en lecture impossible";
            exit(EXIT_FAILURE);
        }
        if(value <= totalDiamonds)
        {
            ofstream writeDiamonds(FICHIER_DIAMOND, ios::out);
            if(writeDiamonds)
            {
                totalDiamonds -= value;
                writeDiamonds << totalDiamonds;
                writeDiamonds.close();
            }
            else
            {
                cerr << "ouverture en lecture impossible";
                exit(EXIT_FAILURE);
            }
            return true;
        }

    }
    return false;
}
