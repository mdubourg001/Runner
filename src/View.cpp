#include "View.h"
#include "Model.h"
#include "main.h"

#include <fstream>
#include <sstream>
#include <iostream>

using namespace std;


//=======================================
// Constructeur
//=======================================



View::View(int w, int h)
    :  _background(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, 2, 5),
      _w(w),_h(h), _x_player(SCREEN_WIDTH/15), _y_player(SCREEN_HEIGHT-SCREEN_HEIGHT/5),
      cpt1(0), cpt2(0),
      _loaded(false), _asChanged(false),
      _popup_displayed(false), _popup_confirm(false),
      gs(intro), lg(fr), dif(facile), cs(ball),
      _totalCoin(0, SCREEN_WIDTH -130, SCREEN_HEIGHT - 70),
      _totalDiamond(0, SCREEN_WIDTH - 300, SCREEN_HEIGHT-70)
{
    _window = new sf::RenderWindow(sf::VideoMode(w, h, 32), "Runner", sf::Style::Close); //RenderWindow est une classe qui définie une fenêtre qui peut etre utilisée pour faire du dessin 2D
    _window->setFramerateLimit(FRAMERATE_LIMIT); //fixe la limite de fps
    _window->setVerticalSyncEnabled(true);
    _window->setKeyRepeatEnabled(true); //désactive la répétition des touches

    _font.loadFromFile(POLICEMENU);

    if (!_backgroundIntro.loadFromFile(BACKGROUND_INTRO_IMAGE)) //charge le fichier city.png et le place dans la texture background
    {
        std::cerr << "ERROR when loading image file: "
                  << BACKGROUND_INTRO_IMAGE << std::endl;
        exit(EXIT_FAILURE);
    }
    else
    {
        _backgroundIntroSprite.setTexture(_backgroundIntro); //définie la texture background comme texture du sprite de background
        _backgroundIntroSprite.setPosition(sf::Vector2f(0.f,0.f)); //définie la position du sprite de background
    }

    _textPass.setFont(_font);
    _textPass.setColor(sf::Color::Black);
    _textPass.setString("<  PATIENTEZ, CHARGEMENT DU JEU...  >");
    _textPass.setOrigin(_textPass.getLocalBounds().width/2, _textPass.getLocalBounds().height/2);
    _textPass.setPosition(sf::Vector2f(SCREEN_WIDTH/2, SCREEN_HEIGHT-SCREEN_HEIGHT/5));

    _background_timer.set_alarm(Moment(0, 0, 0, 11, 0));
    _background_timer.start();

    _animation_timer.set_alarm(Moment(0, 0, 0, 55, 0));
    _animation_timer.start();

    _revive_timer.set_alarm(Moment(0, 0, 5, 0, 0));
}

void View::load()
{
    _totalCoin.setTexture(ONE_COIN);
    _totalDiamond.setTexture(ONE_DIAMOND);
    _highscores_grid.synchronise(_model->Highscores());


    for(unsigned int i=0;i<14;i++)
        _items.push_back(new Item());

    for(unsigned int i=0;i<_items.size();i++)
    {
        if(cs == ball)
        {
            _items.at(i)->LockOrNot(i);
        }
        else if (cs == back)
        {
            _items.at(i)->LockOrNot(i+6);
        }
    }

    _items.at(0)->setSelected(true);
    _items.at(0)->setChoose(true);


    if (!_background.loadTextures(BACKGROUND_IMAGE_B, BACKGROUND_IMAGE_B, BACKGROUND_IMAGE_L, BACKGROUND_IMAGE_L)) //charge le fichier city.png et le place dans la texture background
    {
        std::cerr << "ERROR when loading image file: "
                  << BACKGROUND_IMAGE_B << "/"
                  << BACKGROUND_IMAGE_L << std::endl;
        exit(EXIT_FAILURE);
    }

    if (!_player.loadFromFile(BALL_IMAGE))
    {
        std::cerr << "Error when loading image file: "
                  << BALL_IMAGE << std::endl;
        exit(EXIT_FAILURE);
    }
    else
    {
        _playerSprite.setTexture(_player);
        _playerSprite.setPosition(sf::Vector2f(_x_player, _y_player));
        _playerSprite.setOrigin(sf::Vector2f(_player.getSize().x/2, _player.getSize().y/2));
        _playerSprite.setRotation(10);
    }

    if (!_playerStar.loadFromFile(BALL_STAR_IMAGE))
    {
        std::cerr << "Error when loading image file: "
                  << BALL_IMAGE << std::endl;
        exit(EXIT_FAILURE);
    }

    if (!_backgroundMenu.loadFromFile(BACKGROUND_MENU_IMAGE)) //charge le fichier city.png et le place dans la texture background
    {
        std::cerr << "ERROR when loading image file: "
                  << BACKGROUND_MENU_IMAGE << std::endl;
        exit(EXIT_FAILURE);
    }
    else
    {
        _backgroundMenuSprite.setTexture(_backgroundMenu); //définie la texture background comme texture du sprite de background
        _backgroundMenuSprite.setPosition(sf::Vector2f(0.f,0.f)); //définie la position du sprite de background
    }

    //============BOUTONS DU MENU=============================================//

    _settings_button.first.initialise(PURPLECUBE_L, PURPLECUBE_L, "PARAMETRES",
                                      POLICEMENU, sf::Color::Black, 100,(SCREEN_HEIGHT/2)-100);
    _settings_button.second.initialise(PURPLECUBE_B, PURPLECUBE_B, "PARAMETRES",
                                       POLICEMENU, sf::Color::Black, 75,(SCREEN_HEIGHT/2)-115);

    _highscores_button.first.initialise(YELLOWCUBE_L, YELLOWCUBE_L, "TOP SCORES",
                                        POLICEMENU, sf::Color::Black, 350,(SCREEN_HEIGHT/2)-100);
    _highscores_button.second.initialise(YELLOWCUBE_B, YELLOWCUBE_B, "TOP SCORES",
                                         POLICEMENU, sf::Color::Black, 335,(SCREEN_HEIGHT/2)-115);

    _game_button.first.initialise(GREENCUBE_L, GREENCUBE_L, "JOUER",
                                  POLICEMENU, sf::Color::Black, 600,(SCREEN_HEIGHT/2)-100);
    _game_button.second.initialise(GREENCUBE_B, GREENCUBE_B, "JOUER",
                                   POLICEMENU, sf::Color::Black, 575,(SCREEN_HEIGHT/2)-115);

    _shop_button.first.initialise(BLUECUBE_L, BLUECUBE_L, "BOUTIQUE",
                                  POLICEMENU, sf::Color::Black, 850,(SCREEN_HEIGHT/2)-100);
    _shop_button.second.initialise(BLUECUBE_B, BLUECUBE_B, "BOUTIQUE",
                                   POLICEMENU, sf::Color::Black, 835,(SCREEN_HEIGHT/2)-115);

    _exit_button.first.initialise(REDCUBE_L, REDCUBE_L, "QUITTER",
                                  POLICEMENU, sf::Color::Black, 1100,(SCREEN_HEIGHT/2)-100);
    _exit_button.second.initialise(REDCUBE_B, REDCUBE_B, "QUITTER",
                                   POLICEMENU, sf::Color::Black, 1075,(SCREEN_HEIGHT/2)-115);

    //========================================================================//
    //============BOUTONS DES SETTINGS========================================//

    _french_button.first.initialise(BLUECUBE_L, BLUECUBE_L, "FRANCAIS",
                                    POLICEMENU, sf::Color::Black, 575,(SCREEN_HEIGHT/4)-100);
    _french_button.second.initialise(BLUECUBE_B, BLUECUBE_B, "FRANCAIS",
                                     POLICEMENU, sf::Color::Black, 575,(SCREEN_HEIGHT/4)-100);

    _english_button.first.initialise(REDCUBE_L, REDCUBE_L, "ANGLAIS",
                                     POLICEMENU, sf::Color::Black, 825, (SCREEN_HEIGHT/4)-100);
    _english_button.second.initialise(REDCUBE_B, REDCUBE_B, "ANGLAIS",
                                      POLICEMENU, sf::Color::Black, 825, (SCREEN_HEIGHT/4)-100);

    _easy_button.first.initialise(GREENCUBE_L, GREENCUBE_L, "FACILE",
                                  POLICEMENU, sf::Color::Black, 575,(3*(SCREEN_HEIGHT/4))-100);
    _easy_button.second.initialise(GREENCUBE_B, GREENCUBE_B, "FACILE",
                                   POLICEMENU, sf::Color::Black, 575,(3*(SCREEN_HEIGHT/4))-100);

    _medium_button.first.initialise(YELLOWCUBE_L, YELLOWCUBE_L, "MOYEN",
                                    POLICEMENU, sf::Color::Black, 825,(3*(SCREEN_HEIGHT/4))-100);
    _medium_button.second.initialise(YELLOWCUBE_B, YELLOWCUBE_B, "MOYEN",
                                     POLICEMENU, sf::Color::Black, 825,(3*(SCREEN_HEIGHT/4))-100);

    _hard_button.first.initialise(PURPLECUBE_L, PURPLECUBE_L, "DIFFICILE",
                                  POLICEMENU, sf::Color::Black, 1075,(3*(SCREEN_HEIGHT/4))-100);
    _hard_button.second.initialise(PURPLECUBE_B, PURPLECUBE_B, "DIFFICILE",
                                   POLICEMENU, sf::Color::Black, 1075,(3*(SCREEN_HEIGHT/4))-100);

    //========================================================================//
    //============BOUTONS DU SHOP=============================================//

    for(unsigned int i=0;i<_items.size();i++)
    {
        if(_items.at(i)->isLock())
        {
            _buy_button.initialise(ONE_COIN, ONE_COIN, "ACHETER",
                                   POLICEMENU, sf::Color::Black, 500, (SCREEN_HEIGHT/4)+475);
        }
        else if(!_items.at(i)->isLock())
        {
            _select_button.initialise(GREENCUBE, REDCUBE, "SELECTIONNER",
                                      POLICEMENU, sf::Color::Black, 500, (SCREEN_HEIGHT/4)+475);
        }
    }

    //========================================================================//



    if (!_backgroundSettings.loadFromFile(BACKGROUND_SETTINGS)) //charge le fichier city.png et le place dans la texture background
    {
        std::cerr << "ERROR when loading image file: "
                  << BACKGROUND_MENU_IMAGE << std::endl;
        exit(EXIT_FAILURE);
    }
    else
    {
        _backgroundSettingsSprite.setTexture(_backgroundSettings); //définie la texture background comme texture du sprite de background
        _backgroundSettingsSprite.setPosition(sf::Vector2f(0.f,0.f)); //définie la position du sprite de background
    }


    _textBall.setFont(_font);
    _textBall.setColor(sf::Color::Blue);
    _textBall.setString("Ball : ");
    _textBall.setPosition(10,10);

    _textBack.setFont(_font);
    _textBack.setColor(sf::Color::Blue);
    _textBack.setString("Background : ");
    _textBack.setPosition((SCREEN_WIDTH/2)+10,10);

    _text_pause.setFont(_font);
    _text_pause.setColor(sf::Color::Black);
    _text_pause.setString("PAUSE (P)");
    _text_pause.setCharacterSize(150);
    _text_pause.setPosition(SCREEN_WIDTH/2 - SCREEN_WIDTH/5, SCREEN_HEIGHT/2 - SCREEN_HEIGHT/5);

    _healthRect.setSize(sf::Vector2f(400,50));
    _healthRect.setPosition(225,710);
    _healthRect.setFillColor(sf::Color(100,255,100,255));


    _backhealthRect.setSize(sf::Vector2f(400,50));
    _backhealthRect.setPosition(225,710);
    _backhealthRect.setFillColor(sf::Color(255,100,100,255));
    _backhealthRect.setOutlineThickness(3);
    _backhealthRect.setOutlineColor(sf::Color::Black);

    _shieldRect.setSize(sf::Vector2f(-50,50));
    _shieldRect.setPosition(625,710);
    _shieldRect.setFillColor(sf::Color(170,170,170,255));

    _healthText.setFont(_font);
    _healthText.setColor(sf::Color::Black);
    _healthText.setString("SANTE");
    _healthText.setCharacterSize(60);
    _healthText.setPosition(10,690);


    _rectBall.setSize(sf::Vector2f(SCREEN_WIDTH/2,50));
    _rectBall.setFillColor(sf::Color(100,100,100,255));
    _rectBall.setOutlineThickness(3);
    _rectBall.setOutlineColor(sf::Color::Black);

    _rectBack.setSize(sf::Vector2f(SCREEN_WIDTH/2,50));
    _rectBack.setPosition(SCREEN_WIDTH/2,0);
    _rectBack.setFillColor(sf::Color(150,150,150,255));
    _rectBack.setOutlineThickness(3);
    _rectBack.setOutlineColor(sf::Color::Black);

    _rectScreen.setSize(sf::Vector2f(SCREEN_WIDTH-SCREEN_WIDTH/6,SCREEN_HEIGHT-56));
    _rectScreen.setPosition((SCREEN_WIDTH/6)-3,53);
    _rectScreen.setFillColor(sf::Color(255,127,36,255));
    _rectScreen.setOutlineThickness(3);
    _rectScreen.setOutlineColor(sf::Color::Black);


    for(unsigned int i=0;i<_items.size();i++)
    {
        _items.at(i)->setPosition(3,53 + 51*i);
        _items.at(i)->setOutlineThickness(3);
        _items.at(i)->setOutlineColor(sf::Color::Black);
        _items.at(i)->setSize(sf::Vector2f(SCREEN_WIDTH/6,50));
        _items.at(i)->setName("");
        this->synchroniseShopBack();
    }

    _loaded = true;
    _textPass.setString("<  APPUYEZ SUR ESPACE POUR COMMENCER  >");

    _popup = new Popup("TEST", "TEST", "TEST");
    _popup->setOrigin(_popup->getSize().x/2, _popup->getSize().y/2);
    _popup->setPosition(SCREEN_WIDTH/2, SCREEN_HEIGHT/2);

    this->recup();
}

void View::loadNextShop()
{
    if(cs == ball)
    {
        if( _items.at(0)->isChoose())
        {
            _ball_choose = "ball_one";
            _asChanged = true;

            if (!_player.loadFromFile(BALL_IMAGE))
            {
                std::cerr << "Error when loading image file: "
                          << BALL_IMAGE << std::endl;
                exit(EXIT_FAILURE);
            }
        }
        if( _items.at(1)->isChoose())
        {
            _ball_choose = "ball_two";
            _asChanged = true;

            if (!_player.loadFromFile(BALL_TWO_IMAGE))
            {
                std::cerr << "Error when loading image file: "
                          << BALL_TWO_IMAGE << std::endl;
                exit(EXIT_FAILURE);
            }
        }
        if( _items.at(2)->isChoose())
        {
            _ball_choose = "ball_three";
            _asChanged = true;

            if (!_player.loadFromFile(BALL_THREE_IMAGE))
            {
                std::cerr << "Error when loading image file: "
                          << BALL_THREE_IMAGE << std::endl;
                exit(EXIT_FAILURE);
            }
        }
        if( _items.at(3)->isChoose())
        {
            _ball_choose = "ball_four";
            _asChanged = true;

            if (!_player.loadFromFile(BALL_FOUR_IMAGE))
            {
                std::cerr << "Error when loading image file: "
                          << BALL_FOUR_IMAGE << std::endl;
                exit(EXIT_FAILURE);
            }
        }
        if( _items.at(4)->isChoose())
        {
            _ball_choose = "ball_five";
            _asChanged = true;

            if (!_player.loadFromFile(BALL_FIVE_IMAGE))
            {
                std::cerr << "Error when loading image file: "
                          << BALL_FIVE_IMAGE << std::endl;
                exit(EXIT_FAILURE);
            }
        }
        if ( _items.at(5)->isChoose())
        {
            _ball_choose = "ball_six";
            _asChanged = true;

            if (!_player.loadFromFile(BALL_SIX_IMAGE))
            {
                std::cerr << "Error when loading image file: "
                          << BALL_SIX_IMAGE << std::endl;
                exit(EXIT_FAILURE);
            }
        }
    }
    else if (cs == back)
    {
        if( _items.at(0)->isChoose())
        {
            _back_choose = "background_one";
            _asChanged = true;

            if (!_background.loadTextures(BACKGROUND_IMAGE_B, BACKGROUND_IMAGE_B, BACKGROUND_IMAGE_L, BACKGROUND_IMAGE_L)) //charge le fichier city.png et le place dans la texture background
            {
                std::cerr << "ERROR when loading image file: "
                          << BACKGROUND_IMAGE_B << "/"
                          << BACKGROUND_IMAGE_L << std::endl;
                exit(EXIT_FAILURE);
            }
        }
        if( _items.at(1)->isChoose())
        {
            _back_choose = "background_two";
            _asChanged = true;

            if (!_background.loadTextures(BACKGROUND_TWO_IMAGE_B, BACKGROUND_TWO_IMAGE_B, BACKGROUND_TWO_IMAGE_L, BACKGROUND_TWO_IMAGE_L)) //charge le fichier city.png et le place dans la texture background
            {
                std::cerr << "ERROR when loading image file: "
                          << BACKGROUND_TWO_IMAGE_B << "/"
                          << BACKGROUND_TWO_IMAGE_L << std::endl;
                exit(EXIT_FAILURE);
            }
        }
        if(_items.at(2)->isChoose())
        {
            _back_choose = "background_three";
            _asChanged = true;

            if (!_background.loadTextures(BACKGROUND_THREE_IMAGE_B, BACKGROUND_THREE_IMAGE_B, BACKGROUND_THREE_IMAGE_L, BACKGROUND_THREE_IMAGE_L)) //charge le fichier city.png et le place dans la texture background
            {
                std::cerr << "ERROR when loading image file: "
                          << BACKGROUND_THREE_IMAGE_B << "/"
                          << BACKGROUND_THREE_IMAGE_L << std::endl;
                exit(EXIT_FAILURE);
            }
        }
    }
}

//=======================================
// Destructeur
//=======================================
View::~View() //destructeur de la classe View
{
    if(_window!= NULL)
        delete _window;
}

//=======================================
// Accesseurs
//=======================================

void View::setModel(Model * model) //setter qui permet de modifier le modele associé à la vue
{ _model = model; }

difficulte View::getDiff() const
{ return dif; }

gamestates View::getGs() const
{ return gs; }

choixShop View::getCs() const
{ return cs; }

bool View::getLoaded() const
{ return _loaded; }

sf::Texture View::getPlayer() const
{ return _player; }

void View::setPlayer(const sf::Texture &player)
{ _player = player; }

string View::getBall_choose() const
{ return _ball_choose; }

void View::setBall_choose(const string &ball_choose)
{ _ball_choose = ball_choose; }

string View::getBack_choose() const
{ return _back_choose; }

void View::setBack_choose(const string &back_choose)
{ _back_choose = back_choose; }

bool View::getAsChanged() const
{ return _asChanged; }

void View::setAsChanged(bool asChanged)
{ _asChanged = asChanged; }

bool View::get_popup_displayed() const
{ return _popup_displayed; }

void View::set_popup_displayed(bool popup_displayed)
{ _popup_displayed = popup_displayed; }

string View::get_player_name() const
{
    return _popup->get_temp_name();
}

void View::synchronise()
{
    _background_timer.update();
    _background_timer.check_time();

    _animation_timer.update();
    _animation_timer.check_time();

    //===SYNCHRO PLAYER===//

    _playerSprite.setPosition(sf::Vector2f(_model->getPlayer()->getPosx(), _model->getPlayer()->getPosy()));

    //====================//
    //===SYNCHRO BACKGROUND===//

    if(_background_timer.is_running() && _background_timer.has_ticked() && !_model->is_paused())
    {
        _background_timer.reset();
        _background.move();
    }

    //=======================//
    //===SYNCHRO PIECES ET DIAMANTS===//

    if(_animation_timer.is_running() && _animation_timer.has_ticked())
    {
        _animation_timer.reset();
        for_each(_model->Coins()->begin(), _model->Coins()->end(), [](Coin* &c){c->animate(50);});
        for_each(_model->Diamonds()->begin(), _model->Diamonds()->end(), [](Diamond* &d){d->animate(50);});
        for_each(_model->Awards()->begin(), _model->Awards()->end(), [](Bonus* &b){b->animate(50);});
    }

    if(!_model->getPlayer()->isJumping())
        _model->getPlayer()->rotate(_playerSprite);

    //===============================//

    //===================//

    _healthRect.setSize(sf::Vector2f(_model->getPlayer()->getHealth(),_healthRect.getSize().y));
    _shieldRect.setSize(sf::Vector2f(-_model->getPlayer()->getShield(),_shieldRect.getSize().y));

    if(_model->getPlayer()->getHealth() == 0 && !get_popup_displayed())
    {
        _revive_timer.start();
        _model->getPlayer()->die();
        set_popup_displayed(true);
    }

    if(_model->getPlayer()->isInvincibility() == true)
    {

        if(cpt1 >= 10 && cpt2 >= 10)
        {
            cpt1=0;
            cpt2=0;
        }
        if(cpt1 < 10)
        {
            _playerSprite.setTexture(_player);
            cpt1++;
        }
        else if(cpt2 < 10)
        {
            _playerSprite.setTexture(_playerStar);
            cpt2++;
        }

    }
    else
        _playerSprite.setTexture(_player);

    if(_model->is_paused()) // quand le jeu est en mis en pause
    {
        _popup->set_size_timebar(0);
        if(!_popup_confirm)
        {
            _popup->initialise("JEU EN PAUSE", "OK", "QUITTER");
            if(_popup->answered())
            {
                if(!_popup->getanswer())
                {
                    _popup_confirm = true;
                    _popup->reset();

                }
                else
                {
                    _model->set_paused(false);
                    set_popup_displayed(false);
                    _popup->reset();
                }
            }
        }
        else if(_popup_confirm)
        {
            _popup->initialise("VOULEZ VOUS VRAIMENT QUITTER?", "OUI", "NON");
            if(_popup->answered())
            {
                if(_popup->getanswer())
                {
                    gs = menu;
                    _popup_confirm = false;
                    _model->reset();
                    _model->set_paused(false);
                    set_popup_displayed(false);
                    _popup->reset();
                }
                else
                {
                    _popup_confirm = false;
                    _popup->reset();
                }
            }
        }
    }

    else if(_model->getPlayer()->is_dead()) //quand le joueur meurs
    {
        _revive_timer.update();
        _revive_timer.check_time();
        if(!_popup_confirm && !_popup->get_read_text())
        {
            _popup->set_size_timebar(250 - _revive_timer.get_time_since_begin().to_microseconds()/20000);
            _popup->initialise("VOULEZ VOUS REVIVRE POUR "
                               + std::to_string((int)pow(2, _model->getPlayer()->get_nb_deaths()-1)) + " DIAMANT?", "OUI", "NON");
            if(_revive_timer.is_running() && _revive_timer.has_ticked()) //si le temps de réponse est écoulé
            {
                _model->getPlayer()->set_dead(false);
                this->recup();
                _popup->reset();
                _popup->set_read_text(true);
                _popup->initialise("SAISISSEZ VOTRE NOM: _ _ _ _ _ _", "VALIDER", "QUITTER");
                _revive_timer.stop();
                _revive_timer.reset();
                _revive_timer.set_alarm(Moment(0, 0, 5, 0, 0));
            }

            else if(_popup->answered())
            {
                if(_popup->getanswer()) //si la réponse est positive
                {
                    _popup_confirm = true;
                    _popup->reset();
                    _revive_timer.stop();
                    _revive_timer.reset();
                    _revive_timer.set_alarm(Moment(0, 0, 3, 0, 999));
                    _revive_timer.start(); //reinitialisation de _begin
                }
                else //sinon si elle est négative
                {
                    _model->getPlayer()->set_dead(false);
                    this->recup();
                    _popup->reset();
                    _popup->set_read_text(true);
                    _popup->initialise("SAISISSEZ VOTRE NOM: _ _ _ _ _ _", "VALIDER", "QUITTER");
                    _revive_timer.stop();
                    _revive_timer.reset();
                    _revive_timer.set_alarm(Moment(0, 0, 5, 0, 0));
                }
            }
        }
        else if(_popup_confirm && !_popup->get_read_text()) //affichage du deuxième popup
        {
            if(_totalDiamond.getValue() >= (int)pow(2, _model->getPlayer()->get_nb_deaths()-1)) //si le joueur possède assez de diamants
            {
                _model->getPlayer()->revive();
                _model->Obstacles()->clear();
                _popup->initialise("REPRISE DANS " + std::to_string(2 - _revive_timer.get_time_since_begin().get_sec() + 1), "PREPAREZ", "VOUS");
                if(_revive_timer.is_running() && _revive_timer.has_ticked())
                {
                    set_popup_displayed(false);
                    _popup->reset();
                    _popup_confirm = false;
                    _model->getPlayer()->set_dead(false);
                    _model->setPlayerDirection(none);
                    _revive_timer.stop();
                    _revive_timer.reset();
                    _revive_timer.set_alarm(Moment(0, 0, 5, 0, 0));
                    _totalDiamond.setValue(_totalDiamond.getValue() - (int)pow(2, _model->getPlayer()->get_nb_deaths()-1));
                    _model->addDiamonds_loose((int)pow(2, _model->getPlayer()->get_nb_deaths()-1));
                }
            }
            else //sinon si il n'en a pas assez
            {
                _popup->initialise("VOUS N'AVEZ PAS ASSEZ DE DIAMANTS\n"
                                   "                DOMMAGE.");
                if(_popup->answered())
                {
                    gs = menu;
                    _model->getPlayer()->set_dead(false);
                    this->recup();
                    _popup->reset();
                    _popup_confirm = false;
                    _popup->set_read_text(true);
                    _popup->initialise("SAISISSEZ VOTRE NOM: _ _ _ _ _ _", "VALIDER", "QUITTER");
                    _revive_timer.stop();
                    _revive_timer.reset();
                    _revive_timer.set_alarm(Moment(0, 0, 5, 0, 0));
                }
            }
        }
        else if(_popup->get_read_text())
        {
            if(_popup->answered())
            {
                if(_popup->getanswer())
                {
                    _model->save();
                }
                gs = menu;
                _model->save();
                _model->reset();
                this->recup();
                _popup->reset();
                _popup_confirm = false;
                _popup->set_read_text(false);
                set_popup_displayed(false);
                _revive_timer.stop();
                _revive_timer.reset();
                _revive_timer.set_alarm(Moment(0, 0, 5, 0, 0));
            }
        }
    }
}


void View::synchroniseShop()
{
    for(auto i : _items)
    {
        if(i->isSelected())
            i->setFillColor(sf::Color(150,175,175,255));
        else
            i->setFillColor(sf::Color(200,200,200,255));
    }


    if(cs == ball)
    {
        if(lg == fr)
        {
            if(!_items.at(0)->getLoaded()) _items.at(0)->initialiseBall(BALL_IMAGE, "Smiley", 0, "none");
            if(!_items.at(1)->getLoaded()) _items.at(1)->initialiseBall(BALL_TWO_IMAGE, "Bleue clair", 100, "coins");
            if(!_items.at(2)->getLoaded()) _items.at(2)->initialiseBall(BALL_THREE_IMAGE, "Rouge et Noir", 200, "coins");
            if(!_items.at(3)->getLoaded()) _items.at(3)->initialiseBall(BALL_FOUR_IMAGE, "Bleu fonce", 500, "coins");
            if(!_items.at(4)->getLoaded()) _items.at(4)->initialiseBall(BALL_FIVE_IMAGE, "Rouge et Blanc", 2, "diamonds");
            if(!_items.at(5)->getLoaded()) _items.at(5)->initialiseBall(BALL_SIX_IMAGE, "Verte", 5, "diamonds");
        }
        else if (lg == ang)
        {
            if(!_items.at(0)->getLoaded()) _items.at(0)->initialiseBall(BALL_IMAGE, "Smiley", 0, "none");
            if(!_items.at(1)->getLoaded()) _items.at(1)->initialiseBall(BALL_TWO_IMAGE, "Light blue", 100, "coins");
            if(!_items.at(2)->getLoaded()) _items.at(2)->initialiseBall(BALL_THREE_IMAGE, "Red and Black", 200, "coins");
            if(!_items.at(3)->getLoaded()) _items.at(3)->initialiseBall(BALL_FOUR_IMAGE, "Dark blue", 500, "coins");
            if(!_items.at(4)->getLoaded()) _items.at(4)->initialiseBall(BALL_FIVE_IMAGE, "Red and White", 2, "diamonds");
            if(!_items.at(5)->getLoaded()) _items.at(5)->initialiseBall(BALL_SIX_IMAGE, "Green", 5, "diamonds");
        }
    }
}

void View::synchroniseShopBack()
{
    for(auto i : _items)
        i->setName("");

    if(cs == ball)
    {
        for(unsigned int i=0; i<6; i++)
        {
            _items.at(i)->LockOrNot(i);
        }
    }
    else if(cs == back)
    {
        for(unsigned int i=0; i<3; i++)
        {
            _items.at(i)->LockOrNot(i+6);
        }

        if (lg == fr)
        {
            _items.at(0)->initialiseBackground(BACKGROUND_IMAGE_PREVIEW_B, BACKGROUND_IMAGE_PREVIEW_L, "Ville", 0, "none");
            _items.at(1)->initialiseBackground(BACKGROUND_TWO_IMAGE_PREVIEW_B, BACKGROUND_TWO_IMAGE_PREVIEW_L, "Ville ancienne", 1000, "coins");
        }
        else if (lg == ang)
        {
            _items.at(0)->initialiseBackground(BACKGROUND_IMAGE_PREVIEW_B, BACKGROUND_IMAGE_PREVIEW_L, "City", 0, "none");
            _items.at(1)->initialiseBackground(BACKGROUND_TWO_IMAGE_PREVIEW_B, BACKGROUND_TWO_IMAGE_PREVIEW_L, "City Oldschool", 1000, "coins");
        }
        _items.at(2)->initialiseBackground(BACKGROUND_THREE_IMAGE_PREVIEW_B, BACKGROUND_THREE_IMAGE_PREVIEW_L, "DuckHunt", 3, "diamonds");
    }
}

void View::recupBest()
{
    unsigned int it = 0;
    string temp;
    ifstream readHS(FICHIER_SCORE, ios::in);
    if(readHS)
    {
        while(getline(readHS, temp) && it < 5)
        {
            _model->Highscores()->at(it).first = temp.substr(0, temp.find(" ")); //on récupère le pseudo du joueur
            _model->Highscores()->at(it).second = atol(temp.substr(temp.find(" "), temp.length()-1).c_str()); //et son score
            it++;
        }
        readHS.close();
    }
    _highscores_grid.synchronise(_model->Highscores());
}

void View::recupCoins()
{
    ifstream readCoins (FICHIER_COIN, ios::in);
    string line = "";
    if(readCoins.fail())
    {
        cerr << "ouverture en lecture impossible" << endl;
        exit(EXIT_FAILURE);
    }
    getline(readCoins, line);
    _totalCoin.setValue(atoi(line.c_str()));
    readCoins.close();
}

void View::recupDiamonds()
{
    ifstream readDiamonds (FICHIER_DIAMOND, ios::in);
    string line = "";
    if(readDiamonds.fail())
    {
        cerr << "ouverture en lecture impossible" << endl;
        exit(EXIT_FAILURE);
    }
    getline(readDiamonds, line);
    _totalDiamond.setValue(atoi(line.c_str()));
    readDiamonds.close();
}

void View::recupChoose()
{
    ifstream readChoose (FICHIER_CHOOSE, ios::in);
    string line = "";
    if(readChoose.fail())
    {
        cerr << "ouverture en lecture impossible" << endl;
        exit(EXIT_FAILURE);
    }
    getline(readChoose, line);
    if(line == "ball_one")
    {
        _player.loadFromFile(BALL_IMAGE);
        _ball_choose = "ball_one";
    }
    else if (line == "ball_four")
    {
        _player.loadFromFile(BALL_FOUR_IMAGE);
        _ball_choose = "ball_four";
    }
    else if (line == "ball_five")
    {
        _player.loadFromFile(BALL_FIVE_IMAGE);
        _ball_choose = "ball_five";
    }
    else if (line == "ball_six")
    {
        _player.loadFromFile(BALL_SIX_IMAGE);
        _ball_choose = "ball_six";
    }

    getline(readChoose, line);
    if(line == "background_one")
    {
        _background.loadTextures(BACKGROUND_IMAGE_B, BACKGROUND_IMAGE_B, BACKGROUND_IMAGE_L, BACKGROUND_IMAGE_L);
        _back_choose = "background_one";
    }
    else if(line == "background_two")
        {
        _background.loadTextures(BACKGROUND_TWO_IMAGE_B, BACKGROUND_TWO_IMAGE_B, BACKGROUND_TWO_IMAGE_L, BACKGROUND_TWO_IMAGE_L);
        _back_choose = "background_two";
        }
    else if(line == "background_three")
        {
        _background.loadTextures(BACKGROUND_THREE_IMAGE_B, BACKGROUND_THREE_IMAGE_B, BACKGROUND_THREE_IMAGE_L, BACKGROUND_THREE_IMAGE_L);
            _back_choose = "background_three";
        }
    else if (line == "ball_two")
    {
        _player.loadFromFile(BALL_TWO_IMAGE);
        _ball_choose = "ball_two";
    }
    else if (line == "ball_three")
    {
        _player.loadFromFile(BALL_THREE_IMAGE);
        _ball_choose = "ball_two";
    }
    else if (line == "ball_four")
    {
        _player.loadFromFile(BALL_FOUR_IMAGE);
        _ball_choose = "ball_four";
    }
    else if (line == "ball_five")
    {
        _player.loadFromFile(BALL_FIVE_IMAGE);
        _ball_choose = "ball_five";
    }
    else if (line == "ball_six")
    {
        _player.loadFromFile(BALL_SIX_IMAGE);
        _ball_choose = "ball_six";
    }

    getline(readChoose, line);
    if(line == "background_one")
    {
        _background.loadTextures(BACKGROUND_IMAGE_B, BACKGROUND_IMAGE_B, BACKGROUND_IMAGE_L, BACKGROUND_IMAGE_L);
        _back_choose = "background_one";
    }
    else if(line == "background_two")
    {
        _background.loadTextures(BACKGROUND_TWO_IMAGE_B, BACKGROUND_TWO_IMAGE_B, BACKGROUND_TWO_IMAGE_L, BACKGROUND_TWO_IMAGE_L);
        _back_choose = "background_two";
    }
    else if(line == "background_three")
    {
        _background.loadTextures(BACKGROUND_THREE_IMAGE_B, BACKGROUND_THREE_IMAGE_B, BACKGROUND_THREE_IMAGE_L, BACKGROUND_THREE_IMAGE_L);
        _back_choose = "background_three";
    }
}

void View::recup()
{
    this->recupBest();
    this->recupCoins();
    this->recupDiamonds();
    this->recupChoose();
}

//=======================================
// Fonction de dessin
//======================================
void View::draw()
{
    _window->clear();

    //dessin du background

    _background.draw(_window);

    //--------------------

    //dessin des pièces

    for(auto c : *_model->Coins())
    {
        if(!c->isPicked())
            _window->draw(*c);
        else if(c->isPicked() && !c->clock_has_ticked())
            c->draw_alpha(_window);
    }

    //--------------------

    //dessin des diamants

    for(auto d : *_model->Diamonds())
        _window->draw(*d);

    //--------------------

    //dessin des bonus

    for(auto a : *_model->Awards())
        _window->draw(*a);

    //--------------------

    //dessin de la balle

    _model->getPlayer()->drawShadow(_window);
    _window->draw(_playerSprite);

    //--------------------

    //dessin des obstacles

    for(auto o : *_model->Obstacles())
        o->draw(_window);

    //--------------------

    _window->draw(_healthText);

    _model->drawInterface(_window);
    _window->draw(_backhealthRect); //dessin du fond de vie (rouge)
    _window->draw(_healthRect); // dessin de la vie (vert)
    _window->draw(_shieldRect); // dessin du bouclier

    if(get_popup_displayed())
    {
        _popup->draw(_window);
    }

    _window->display();
}

void View::drawIntro()
{
    _window->clear();

    _window->draw(_backgroundIntroSprite);
    _window->draw(_textPass);

    _window->display();

}

void View::drawMenu()
{
    _window->clear();

    _window->draw(_backgroundMenuSprite);

    if(_settings_button.second.isSelected())
        _settings_button.second.draw(_window);
    else
        _settings_button.first.draw(_window);

    if(_highscores_button.second.isSelected())
        _highscores_button.second.draw(_window);
    else
        _highscores_button.first.draw(_window);

    if(_game_button.second.isSelected())
        _game_button.second.draw(_window);
    else
        _game_button.first.draw(_window);

    if(_shop_button.second.isSelected())
        _shop_button.second.draw(_window);
    else
        _shop_button.first.draw(_window);

    if(_exit_button.second.isSelected())
        _exit_button.second.draw(_window);
    else
        _exit_button.first.draw(_window);

    _totalCoin.draw(_window);
    _totalDiamond.draw(_window);

    _window->display();
}

void View::drawSettings()
{
    _window->clear();

    _window->draw(_backgroundSettingsSprite);

    if(lg == fr)
        _french_button.second.draw(_window);

    else
        _french_button.first.draw(_window);


    if(lg == ang)
        _english_button.second.draw(_window);

    else
        _english_button.first.draw(_window);


    if(dif == facile)
        _easy_button.second.draw(_window);

    else
        _easy_button.first.draw(_window);


    if(dif == moyen)
        _medium_button.second.draw(_window);

    else
        _medium_button.first.draw(_window);


    if(dif == difficile)
        _hard_button.second.draw(_window);

    else
        _hard_button.first.draw(_window);


    _window->display();
}

void View::drawShop()
{
    _window->clear(sf::Color::White);

    for(auto i : _items)
        if(i->isSelected())
            i->drawPreview(_window);

    for(auto i : _items)
    {
        _window->draw(*i);
        i->drawText(_window);
    }

    if(_buy_button.isSelected())
    {
        _buy_button.setBigTexture();
        _buy_button.setColor(sf::Color::Red);
    }
    else
    {
        _buy_button.setLittleTexture();
        _buy_button.setColor(sf::Color::Black);
    }

    if(_select_button.isSelected())
    {
        _select_button.setBigTexture();
        _select_button.setColor(sf::Color::Red);
    }
    else
    {
        _select_button.setLittleTexture();
        _select_button.setColor(sf::Color::Black);
    }

    _buy_button.draw(_window);
    _select_button.draw(_window);

    _window->draw(_rectBall);
    _window->draw(_rectBack);
    _window->draw(_textBall);
    _window->draw(_textBack);

    //--------------------
    //--------------------

    _totalCoin.draw(_window);
    _totalDiamond.draw(_window);

    _window->display();
}

void View::drawHighscores()
{
    _window->clear();

    _window->draw(_backgroundMenuSprite);

    _highscores_grid.draw(_window);

    _window->display();
}

//=======================================
// Traitement des evenements
//=======================================
bool View::treatEvents()
{
    bool result = false;

    if(_window->isOpen())
    {
        result = true;

        sf::Event event;
        int x;
        int y;


        if(!get_popup_displayed())
        {
            while (_window->pollEvent(event)) //tant qu'un évenement est détécté
            {
                if (event.type == sf::Event::Closed || ((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::Escape) && gs == intro)) //si on clique sur la croix de fermeture
                {
                    _window->close(); //la fenetre est fermée
                    result = false;

                }
                else if ((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::Escape) && gs!= menu && gs!=intro && gs!= game)
                {
                    gs = menu;
                    _model->save();
                    this->recup();
                    _model->reset();
                }
                else if ((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::Escape) && gs== menu)
                {
                    gs = intro;
                }
                else if((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::Escape) && gs == settings)
                {
                    gs = menu;
                }
                else if((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::Escape) && gs == highscores)
                {
                    gs = menu;
                }

                else if (event.type == sf::Event::KeyPressed)
                {
                    if((event.key.code == sf::Keyboard::Up || event.key.code == sf::Keyboard::Space) && !_model->getPlayer()->isJumping() && gs==game)
                        _model->setPlayerDirection(up);

                    if(event.key.code == sf::Keyboard::Left && gs==game)
                        _model->setPlayerDirection(l);

                    if(event.key.code == sf::Keyboard::Right && gs==game)
                        _model->setPlayerDirection(r);

                    if((event.key.code == sf::Keyboard::P || event.key.code == sf::Keyboard::Escape) && gs == game)
                    {
                        set_popup_displayed(true);
                        _model->set_paused(true);
                    }

                    if((event.key.code == sf::Keyboard::Space) && gs==intro && this->getLoaded())
                        gs = menu;


                    else if(event.key.code == sf::Keyboard::Right && gs==shop)
                    {
                        if(_rectBall.getFillColor() == sf::Color(100,100,100,255))
                        {
                            _rectBall.setFillColor(sf::Color(150,150,150,255));
                            _rectBack.setFillColor(sf::Color(100,100,100,255));
                            cs = back;
                        }
                        else
                        {
                            _rectBall.setFillColor(sf::Color(100,100,100,255));
                            _rectBack.setFillColor(sf::Color(150,150,150,255));
                            cs = ball;
                        }
                        for(auto i : _items)
                        {
                            i->setSelected(false);
                            i->setLoaded(false);
                        }
                        _items.at(0)->setSelected(true);
                        this->synchroniseShopBack();
                    }
                    else if(event.key.code == sf::Keyboard::Left && gs==shop)
                    {
                        if(_rectBall.getFillColor() == sf::Color(100,100,100,255))
                        {
                            _rectBall.setFillColor(sf::Color(150,150,150,255));
                            _rectBack.setFillColor(sf::Color(100,100,100,255));
                            cs = back;
                        }
                        else
                        {
                            _rectBall.setFillColor(sf::Color(100,100,100,255));
                            _rectBack.setFillColor(sf::Color(150,150,150,255));
                            cs = ball;
                        }
                        for(auto i : _items)
                        {
                            i->setSelected(false);
                            i->setLoaded(false);
                        }
                        _items.at(0)->setSelected(true);
                        this->synchroniseShopBack();
                    }

                    else if (event.key.code == sf::Keyboard::Down && gs==shop)
                    {
                        for(unsigned int i=0;i<_items.size();i++)
                        {
                            if(_items.at(i)->isSelected() && i != 13)
                            {
                                _items.at(i)->setSelected(false);
                                _items.at(i)->reset();
                                _items.at(i+1)->setSelected(true);
                                if(cs == ball)
                                    _items.at(i+1)->getPreview()->setBackgroundTexture(BACKGROUND_IMAGE_PREVIEW_B, BACKGROUND_IMAGE_PREVIEW_L);
                                else
                                    _items.at(i+1)->getPreview()->setBallTexture(BALL_IMAGE);
                                break;
                            }
                        }
                    }

                    else if (event.key.code == sf::Keyboard::Up && gs==shop)
                    {
                        for(unsigned int i=0;i<_items.size();i++)
                        {
                            if(_items.at(i)->isSelected() && i != 0)
                            {
                                _items.at(i)->setSelected(false);
                                _items.at(i)->reset();
                                _items.at(i-1)->setSelected(true);
                                if(cs == ball)
                                    _items.at(i-1)->getPreview()->setBackgroundTexture(BACKGROUND_IMAGE_PREVIEW_B, BACKGROUND_IMAGE_PREVIEW_L);
                                else
                                    _items.at(i-1)->getPreview()->setBallTexture(BALL_IMAGE);
                                break;
                            }
                        }
                    }
                }

                else if(event.type == sf::Event::KeyReleased)
                {
                    if(event.key.code != sf::Keyboard::Up
                            && event.key.code != sf::Keyboard::Space)
                        _model->setPlayerDirection(none);
                }

                else if (event.type == sf::Event::MouseButtonPressed && gs == menu)
                {
                    x = event.mouseButton.x;
                    y = event.mouseButton.y;

                    if(x>=80 && x<=270 && y>=300 && y<=485)
                        gs = settings;
                    else if(x>=340 && x<=520 && y>=300 && y<=485)
                        gs = highscores;
                    else if(x>=575 && x<=770 && y>=300 && y<=485)
                        gs = game;
                    else if(x>=835 && x<=1025 && y>=300 && y<=485)
                        gs = shop;
                    else if (x>=1085 && x<=1275 && y>=300 && y<=485)
                    {
                        _window->close();
                        result = false;
                    }
                }
                else if (event.type == sf::Event::MouseButtonPressed && gs == shop)
                {
                    x = event.mouseButton.x;
                    y = event.mouseButton.y;

                    if(x>= 460 && x<=585 && y>=670 && y<=740)
                    {
                        for(unsigned int i=0;i<_items.size();i++)
                        {
                            if(_items.at(i)->isChoose())
                            {
                                _items.at(i)->setChoose(false);
                                break;
                            }
                        }
                        for(unsigned int i=0; i<_items.size();i++)
                        {
                            if(_items.at(i)->isSelected())
                            {
                                if(_items.at(i)->isLock())
                                {
                                    if(cs == ball)
                                    {
                                        if(_model->looseMoney(_items.at(i)->getValue(), _items.at(i)->getType()) == true)
                                        {
                                            _items.at(i)->unLock(i);
                                            _items.at(i)->setChoose(true);
                                        }
                                        this->recup();
                                        _items.at(i)->LockOrNot(i);
                                        break;
                                    }
                                    else if(cs == back)
                                    {
                                        if(_model->looseMoney(_items.at(i)->getValue(), _items.at(i)->getType()) == true)
                                        {
                                            _items.at(i)->unLock(i+6);
                                            _items.at(i)->setChoose(true);
                                        }
                                        this->recup();
                                        _items.at(i)->LockOrNot(i+6);
                                        break;
                                    }
                                }
                                else
                                {
                                    _items.at(i)->setChoose(true);
                                    break;
                                }
                                break;
                            }
                        }
                        this->loadNextShop();
                    }

                }
                else if (event.type == sf::Event::MouseButtonPressed && gs == settings)
                {
                    x = event.mouseButton.x;
                    y = event.mouseButton.y;

                    if(x>=570 && x<=770 && y>=100 && y<=295)
                    {
                        lg = fr;
                        toFrench();
                    }
                    else if(x>=830 && x<=1030 && y>=100 && y<=295)
                    {
                        lg = ang;
                        toEnglish();
                    }
                    else if(x>=570 && x<=770 && y>=495 && y<=670)
                    {
                        dif = facile;
                        _model->setDifficulte(0);
                    }
                    else if(x>=830 && x<=1030 && y>=495 && y<=670)
                    {
                        dif = moyen;
                        _model->setDifficulte(1000);
                    }
                    else if (x>=1080 && x<=1270 && y>=495 && y<=670)
                    {
                        dif = difficile;
                        _model->setDifficulte(1300);
                    }
                }
                else if(event.type == sf::Event::MouseButtonPressed && gs == highscores)
                {
                    x = event.mouseButton.x;
                    y = event.mouseButton.y;

                    if(x<_highscores_grid.get_button_pos().x + _highscores_grid.get_button_bounds().width
                            && x>_highscores_grid.get_button_pos().x
                            && y<_highscores_grid.get_button_pos().y + _highscores_grid.get_button_bounds().height
                            && y>_highscores_grid.get_button_pos().y)
                    {
                        _highscores_grid.reset();
                        _model->reset_highscores();
                    }
                }
                else if (event.type == sf::Event::MouseMoved && gs == menu)
                {
                    int xM = event.mouseMove.x;
                    int yM = event.mouseMove.y;

                    if(xM>=80 && xM<=270 && yM>=300 && yM<=485)
                        _settings_button.second.setSelected(true);
                    else
                        _settings_button.second.setSelected(false);

                    if(xM>=340 && xM<=520 && yM>=300 && yM<=485)
                        _highscores_button.second.setSelected(true);
                    else
                        _highscores_button.second.setSelected(false);

                    if(xM>=575 && xM<=770 && yM>=300 && yM<=485)
                        _game_button.second.setSelected(true);
                    else
                        _game_button.second.setSelected(false);

                    if(xM>=835 && xM<=1025 && yM>=300 && yM<=485)
                        _shop_button.second.setSelected(true);
                    else
                        _shop_button.second.setSelected(false);

                    if(xM>=1085 && xM<=1275 && yM>=300 && yM<=485)
                        _exit_button.second.setSelected(true);
                    else
                        _exit_button.second.setSelected(false);
                }
                else if (event.type == sf::Event::MouseMoved && gs == shop)
                {
                    int xM = event.mouseMove.x;
                    int yM = event.mouseMove.y;

                    if(xM>= 460 && xM<=585 && yM>=670 && yM<=740)
                    {
                        _buy_button.setSelected(true);
                        _select_button.setSelected(true);
                    }
                    else
                    {
                        _buy_button.setSelected(false);
                        _select_button.setSelected(false);
                    }

                }
            }
        }

        else if(get_popup_displayed())
        {
            _popup->treat_events(_window, event);
        }
    }
    return result;
}

void View::toEnglish()
{
    ifstream readEnglish(FICHIER_ENGLISH, ios::in);
    string line = "";
    if(readEnglish)
    {
        getline(readEnglish,line);
        _french_button.first.setString(line);
        _french_button.second.setString(line);
        getline(readEnglish,line);
        _english_button.first.setString(line);
        _english_button.second.setString(line);
        getline(readEnglish,line);
        _hard_button.first.setString(line);
        _hard_button.second.setString(line);
        getline(readEnglish,line);
        _easy_button.first.setString(line);
        _easy_button.second.setString(line);
        getline(readEnglish,line);
        _medium_button.first.setString(line);
        _medium_button.second.setString(line);
        getline(readEnglish,line);
        _settings_button.first.setString(line);
        _settings_button.second.setString(line);
        getline(readEnglish,line);
        _highscores_button.first.setString(line);
        _highscores_button.second.setString(line);
        getline(readEnglish,line);
        _game_button.first.setString(line);
        _game_button.second.setString(line);
        getline(readEnglish,line);
        _shop_button.first.setString(line);
        _shop_button.second.setString(line);
        getline(readEnglish,line);
        _exit_button.first.setString(line);
        _exit_button.second.setString(line);
        getline(readEnglish,line);
        _healthText.setString(line);
        getline(readEnglish,line);
        _textPass.setString("< " + line + " >");
        getline(readEnglish,line);
        _textBall.setString(line);
        getline(readEnglish,line);
        _textBack.setString(line);
        getline(readEnglish,line);
        _buy_button.setString(line);
        getline(readEnglish,line);
        _select_button.setString(line);

        readEnglish.close();
    }
    else
    {
        cerr << "ouverture en lecture impossible";
        exit(EXIT_FAILURE);
    }
}

void View::toFrench()
{
    ifstream readFrench(FICHIER_FRENCH, ios::in);
    string line = "";
    if(readFrench)
    {
        getline(readFrench,line);
        _french_button.first.setString(line);
        _french_button.second.setString(line);
        getline(readFrench,line);
        _english_button.first.setString(line);
        _english_button.second.setString(line);
        getline(readFrench,line);
        _hard_button.first.setString(line);
        _hard_button.second.setString(line);
        getline(readFrench,line);
        _easy_button.first.setString(line);
        _easy_button.second.setString(line);
        getline(readFrench,line);
        _medium_button.first.setString(line);
        _medium_button.second.setString(line);
        getline(readFrench,line);
        _settings_button.first.setString(line);
        _settings_button.second.setString(line);
        getline(readFrench,line);
        _highscores_button.first.setString(line);
        _highscores_button.second.setString(line);
        getline(readFrench,line);
        _game_button.first.setString(line);
        _game_button.second.setString(line);
        getline(readFrench,line);
        _shop_button.first.setString(line);
        _shop_button.second.setString(line);
        getline(readFrench,line);
        _exit_button.first.setString(line);
        _exit_button.second.setString(line);
        getline(readFrench,line);
        _healthText.setString(line);
        getline(readFrench,line);
        _textPass.setString("< " + line + " >");
        getline(readFrench,line);
        _textBall.setString(line);
        getline(readFrench,line);
        _textBack.setString(line);
        getline(readFrench,line);
        _buy_button.setString(line);
        getline(readFrench,line);
        _select_button.setString(line);

        readFrench.close();
    }
    else
    {
        cerr << "ouverture en lecture impossible";
        exit(EXIT_FAILURE);
    }
}
