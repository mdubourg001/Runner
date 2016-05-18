#include "View.h"
#include "Model.h"
#include "main.h"

#include <fstream>
#include <sstream>
#include <iostream>

using namespace std;
//using namespace sf;

int cpt1=0;
int cpt2=0;

//=======================================
// Constructeur
//=======================================
View::View(int w, int h)
    : _w(w),_h(h), _x_player(SCREEN_WIDTH/15), _y_player(SCREEN_HEIGHT-SCREEN_HEIGHT/5), _background(0, 0 , SCREEN_WIDTH, SCREEN_HEIGHT, 2, 5),
      _cpt(160) ,gs(intro), lg(fr), dif(facile), cs(ball),
      _totalCoin(0, SCREEN_WIDTH -130, SCREEN_HEIGHT - 70, 50, 50),
      _totalDiamond(0, SCREEN_WIDTH - 300, SCREEN_HEIGHT-70, 50, 50),
      _loaded(false),
      _popup_displayed(false)
{
    _window = new sf::RenderWindow(sf::VideoMode(w, h, 32), "Runner", sf::Style::Close); //RenderWindow est une classe qui définie une fenêtre qui peut etre utilisée pour faire du dessin 2D
    _window->setFramerateLimit(FRAMERATE_LIMIT); //fixe la limite de fps
    _window->setVerticalSyncEnabled(true);
    _window->setKeyRepeatEnabled(true); //désactive la répétition des touches

    _font.loadFromFile(POLICE);
    _fontmenu.loadFromFile(POLICE);

    _start = std::chrono::system_clock::now();

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

    _popup = new Popup();
}

void View::load()
{
    _totalCoin.setTexture("res/coin.png");
    _totalDiamond.setTexture("res/diamond.png");

    if (!_background.loadTextures(BACKGROUND_IMAGE_B, BACKGROUND_IMAGE_B, BACKGROUND_IMAGE_L, BACKGROUND_IMAGE_L)) //charge le fichier city.png et le place dans la texture background
    {
        std::cerr << "ERROR when loading image file: "
                  << BACKGROUND_IMAGE_B << "/"
                  << BACKGROUND_IMAGE_L << std::endl;
        exit(EXIT_FAILURE);
    }

    if (!_player.loadFromFile(BALL_TWO_IMAGE))
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

    _topScores.setFont(_font);
    _topScores.setColor(sf::Color::Black);
    _topScores.setString("HIGHCORES :  ");
    _topScores.setPosition(_highscores_button.first.getPos().x+400,_highscores_button.first.getPos().y);

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
    _healthText.setString("SANTE :");
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


    for(int i=0;i<14;i++)
        _items.push_back(new Item());


    for(int i=0;i<_items.size();i++)
    {
        _items.at(i)->setPosition(3,53 + 51*i);
        _items.at(i)->setOutlineThickness(3);
        _items.at(i)->setOutlineColor(sf::Color::Black);
        _items.at(i)->setSize(sf::Vector2f(SCREEN_WIDTH/6,50));
        _items.at(i)->setName("");
        this->synchroniseShopBack();
    }

    _items.at(0)->setSelected(true);

    _loaded = true;
    _textPass.setString("<  APPUYEZ SUR ESPACE POUR COMMENCER  >");
}

//=======================================
// Destructeur
//=======================================
View::~View() //destructeur de la classe View
{
    if(_window!= NULL)
        delete _window;
}

void View::setModel(Model * model) //setter qui permet de modifier le modele associé à la vue
{
    _model = model;
}

difficulte View::getDiff()
{
    return dif;
}

bool View::getLoaded() const
{
    return _loaded;
}

void View::synchronise()
{
    _end = std::chrono::system_clock::now();
    int timelapse = std::chrono::duration_cast<std::chrono::milliseconds>
            (_end - _start).count();

    //===SYNCHRO PLAYER===//

    _playerSprite.setPosition(sf::Vector2f(_model->getPlayer()->getPosx(), _model->getPlayer()->getPosy()));

    //====================//
    //===SYNCHRO BACKGROUND===//

    _background.move();

    //=======================//
    //===SYNCHRO PIECES ET DIAMANTS===//

    if(timelapse >= 55)
    {
        _start = std::chrono::system_clock::now();
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

    if(_model->getPlayer()->getHealth() == 0)
    {
//        _popup->setString("VOULEZ VOUS REVIVRE ?");
//        _popup->setLeftString("OUI");
//        _popup->setRightString("NON");
//        _popup_displayed = true;

        gs = menu;
        _model->save();
        this->recup();
        _model->reset();
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

}

void View::synchroniseShop()
{
    for(int i=0;i<_items.size();i++)
    {
        if(_items.at(i)->isSelected())
            _items.at(i)->setFillColor(sf::Color(150,175,175,255));
        else
            _items.at(i)->setFillColor(sf::Color(200,200,200,255));
    }

    if(cs == ball)
    {
        _items.at(0)->initialiseBall(BALL_IMAGE, "Orange smiley");
        _items.at(1)->initialiseBall(BALL_TWO_IMAGE, "Bleue clair");
        _items.at(2)->initialiseBall(BALL_THREE_IMAGE, "Rouge et Noir");
        _items.at(3)->initialiseBall(BALL_FOUR_IMAGE, "Bleu fonce");
        _items.at(4)->initialiseBall(BALL_FIVE_IMAGE, "Rouge et Blanc");
        _items.at(5)->initialiseBall(BALL_SIX_IMAGE, "Verte");
    }
}

void View::synchroniseShopBack()
{
    for(int i=0; i<_items.size();i++)
        _items.at(i)->setName("");

    if (cs == back)
    {
        _items.at(0)->initialiseBackground(BACKGROUND_IMAGE_PREVIEW_B, BACKGROUND_IMAGE_PREVIEW_L, "City");
        _items.at(1)->initialiseBackground(BACKGROUND_TWO_IMAGE_PREVIEW_B, BACKGROUND_TWO_IMAGE_PREVIEW_L, "City OldSchool");
    }
}

void View::recupBest()
{
    ifstream fichierRecup;
    string line = "";
    fichierRecup.open(FICHIER_SCORE, ios::in );
    if( fichierRecup.fail())
    {
        cerr << "ouverture en lecture impossible" << endl;
        exit(EXIT_FAILURE);
    }
    getline(fichierRecup, line);
    _best.setValue(atoi(line.c_str()));
    fichierRecup.close();

    _topScores.setString(to_string(_best.getValue()));
}

void View::recupCoins()
{
    ifstream fichierRecup;
    string line = "";
    fichierRecup.open(FICHIER_COIN, ios::in );
    if( fichierRecup.fail())
    {
        cerr << "ouverture en lecture impossible" << endl;
        exit(EXIT_FAILURE);
    }
    getline(fichierRecup, line);
    _totalCoin.setValue(atoi(line.c_str()));
    fichierRecup.close();
}

void View::recupDiamonds()
{
    ifstream fichierRecup;
    string line = "";
    fichierRecup.open(FICHIER_DIAMOND, ios::in );
    if( fichierRecup.fail())
    {
        cerr << "ouverture en lecture impossible" << endl;
        exit(EXIT_FAILURE);
    }
    getline(fichierRecup, line);
    _totalDiamond.setValue(atoi(line.c_str()));
    fichierRecup.close();
}

void View::recup()
{
    this->recupBest();
    this->recupCoins();
    this->recupDiamonds();
}

//=======================================
// Fonction de dessin
//======================================Awards=
void View::draw()
{
    _window->clear();

    //dessin du background

    _background.draw(_window);

    //--------------------

    //dessin des pièces

    for(int i=0; i<_model->Coins()->size() ; i++)
    {
        _window->draw(*_model->Coins()->at(i));
        //_window->draw(*_model->Coins()->at(i)->Alpha());
    }

    //--------------------

    //dessin des diamants

    for(int i=0; i<_model->Diamonds()->size() ; i++)
        _window->draw(*_model->Diamonds()->at(i));

    //--------------------

    //dessin des bonus

    for(int i=0; i<_model->Awards()->size() ; i++)
        _window->draw(*_model->Awards()->at(i));

    //--------------------


    //dessin de la balle

    _model->getPlayer()->drawShadow(_window);
    _window->draw(_playerSprite);

    //--------------------

    //dessin des obstacles

    for(int i=0; i<_model->Obstacles()->size() ; i++)
        _model->Obstacles()->at(i)->draw(_window);

    //--------------------

    _window->draw(_healthText);

    _model->drawInterface(_window);
    _window->draw(_backhealthRect); //dessin du fond de vie (rouge)
    _window->draw(_healthRect); // dessin de la vie (vert)
    _window->draw(_shieldRect); // dessin du bouclier


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
    {
        if(i->isSelected())
            i->drawPreview(_window);
    }

    for(int i=0;i<_items.size();i++)
    {
        _window->draw(*_items.at(i));
        _items.at(i)->drawText(_window);
    }




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

    _window->draw(_topScores);

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


        while (_window->pollEvent(event)) //tant qu'un évenement est détécté
        {
            if (event.type == sf::Event::Closed || ((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::Escape) && gs == intro)) //si on clique sur la croix de fermeture
            {
                _window->close(); //la fenetre est fermée
                result = false;
                _model->save();

            }
            else if ((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::Escape) && gs!= menu && gs!=intro)
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


            else if (event.type == sf::Event::KeyPressed)
            {
                if((event.key.code == sf::Keyboard::Up || event.key.code == sf::Keyboard::Space) && !_model->getPlayer()->isJumping() && gs==game)
                {
                    _model->setPlayerDirection(up);
                }

                if(event.key.code == sf::Keyboard::Left && gs==game)
                {
                    _model->setPlayerDirection(l);
                }

                if(event.key.code == sf::Keyboard::Right && gs==game)
                {
                    _model->setPlayerDirection(r);
                }
                if((event.key.code == sf::Keyboard::Space) && gs==intro && this->getLoaded())
                {
                    gs = menu;
                }

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
                    for(int i=1;i<_items.size();i++)
                        _items.at(i)->setSelected(false);
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
                    for(int i=1;i<_items.size();i++)
                        _items.at(i)->setSelected(false);
                    _items.at(0)->setSelected(true);
                    this->synchroniseShopBack();
                }

                else if (event.key.code == sf::Keyboard::Down && gs==shop)
                {
                    for(int i=0;i<_items.size();i++)
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
                    for(int i=0;i<_items.size();i++)
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
                if(event.key.code != sf::Keyboard::Up && event.key.code != sf::Keyboard::Space)
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

        }
    }
    return result;
}

gamestates View::getGs()
{
    return gs;
}

void View::toEnglish()
{
    _french_button.first.setString("French");
    _english_button.first.setString("English");
    _hard_button.first.setString("Hard");
    _easy_button.first.setString("Easy");
    _medium_button.first.setString("Medium");

    _settings_button.first.setString("Settings");
    _highscores_button.first.setString("Highscores");
    _game_button.first.setString("Play");
    _shop_button.first.setString("Shop");
    _exit_button.first.setString("Exit");


    _french_button.second.setString("French");
    _english_button.second.setString("English");
    _hard_button.second.setString("Hard");
    _easy_button.second.setString("Easy");
    _medium_button.second.setString("Medium");

    _settings_button.second.setString("Settings");
    _highscores_button.second.setString("Highscores");
    _game_button.second.setString("Play");
    _shop_button.second.setString("Shop");
    _exit_button.second.setString("Exit");

    _healthText.setString("HEALTH : ");

    _textPass.setString("<  PRESS SPACE TO START  >");
}

void View::toFrench()
{
    _french_button.first.setString("Francais");
    _english_button.first.setString("Anglais");
    _hard_button.first.setString("Difficile");
    _easy_button.first.setString("Facile");
    _medium_button.first.setString("Moyen");

    _settings_button.first.setString("Parametres");
    _highscores_button.first.setString("Topscores");
    _game_button.first.setString("Jouer");
    _shop_button.first.setString("Boutique");
    _exit_button.first.setString("Quitter");


    _french_button.second.setString("Francais");
    _english_button.second.setString("Anglais");
    _hard_button.second.setString("Difficile");
    _easy_button.second.setString("Facile");
    _medium_button.second.setString("Moyen");

    _settings_button.second.setString("Parametres");
    _highscores_button.second.setString("Topscores");
    _game_button.second.setString("Jouer");
    _shop_button.second.setString("Boutique");
    _exit_button.second.setString("Quitter");

    _healthText.setString("SANTE : ");

    _textPass.setString("<  APPUYER SUR ESPACE POUR COMMENCER  >");

}
