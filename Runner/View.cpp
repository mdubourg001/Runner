#include "View.h"
#include "Model.h"
#include "main.h"

#include <fstream>
#include <sstream>
#include <iostream>

using namespace std;
//using namespace sf;

//=======================================
// Constructeur
//=======================================
View::View(int w, int h)
    : _w(w),_h(h), _x_player(SCREEN_WIDTH/15), _y_player(SCREEN_HEIGHT-SCREEN_HEIGHT/5), _background(SCREEN_WIDTH, SCREEN_HEIGHT, 2, 5), _cpt(160) ,gs(intro), cp(gen)
{
    _window = new sf::RenderWindow(sf::VideoMode(w, h, 32), "Runner", sf::Style::Close); //RenderWindow est une classe qui définie une fenêtre qui peut etre utilisée pour faire du dessin 2D
    _window->setFramerateLimit(FRAMERATE_LIMIT); //fixe la limite de fps
    _window->setVerticalSyncEnabled(true);
    _window->setKeyRepeatEnabled(true); //désactive la répétition des touches

    _font.loadFromFile(POLICE);


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

    if (!_backgroundSettings.loadFromFile(BACKGROUND_MENU_IMAGE)) //charge le fichier city.png et le place dans la texture background
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



    _textLang.setFont(_font);
    _textLang.setColor(sf::Color::Blue);
    _textLang.setString("Langue : ");
    _textLang.setStyle(sf::Text::Underlined);
    _textLang.setPosition(600,250);

    _textDiff.setFont(_font);
    _textDiff.setColor(sf::Color::Blue);
    _textDiff.setString("Difficulte : ");
    _textDiff.setPosition(600,350);

    _textFr.setFont(_font);
    _textFr.setColor(sf::Color::Red);
    _textFr.setString("Francais");
    _textFr.setPosition(800,250);

    _textAng.setFont(_font);
    _textAng.setColor(sf::Color::Blue);
    _textAng.setString("Anglais");
    _textAng.setPosition(800,300);

    _textFac.setFont(_font);
    _textFac.setColor(sf::Color::Red);
    _textFac.setString("Facile");
    _textFac.setPosition(800,350);

    _textMoy.setFont(_font);
    _textMoy.setColor(sf::Color::Blue);
    _textMoy.setString("Moyen");
    _textMoy.setPosition(800,400);

    _textDur.setFont(_font);
    _textDur.setColor(sf::Color::Blue);
    _textDur.setString("Difficile");
    _textDur.setPosition(800,450);

    _textGame.setFont(_font);
    _textGame.setColor(sf::Color::Blue);
    _textGame.setString("Jouer");
    _textGame.setPosition(300,300);

    _textExit.setFont(_font);
    _textExit.setColor(sf::Color::Blue);
    _textExit.setString("Quitter");
    _textExit.setPosition(300,450);

    _textSettings.setFont(_font);
    _textSettings.setColor(sf::Color::Blue);
    _textSettings.setString("Parametres");
    _textSettings.setPosition(300,400);

    _textShop.setFont(_font);
    _textShop.setColor(sf::Color::Blue);
    _textShop.setString("Boutique");
    _textShop.setPosition(300,350);

    _textPass.setFont(_font);
    _textPass.setColor(sf::Color::Black);
    _textPass.setString("<  APPUYER SUR ESPACE POUR COMMENCER  >");
    _textPass.setPosition(510,650);

    _healthText.setFont(_font);
    _healthText.setColor(sf::Color::Black);
    _healthText.setString("SANTE :");
    _healthText.setCharacterSize(60);
    _healthText.setPosition(10,690);
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
// Accesseurs en écriture
//=======================================
void View::setModel(Model * model) //setter qui permet de modifier le modele associé à la vue
{
    _model = model;
}

void View::synchronise()
{
    _cpt--;

    //===SYNCHRO PLAYER===//

    _playerSprite.setPosition(sf::Vector2f(_model->getPlayer()->getPosx(), _model->getPlayer()->getPosy()));
    if(!_model->getPlayer()->isJumping())
        _model->getPlayer()->rotate(_playerSprite);

    //====================//
    //===SYNCHRO BACKGROUND===//

    _background.move();

    //=======================//
    //===SYNCHRO PIECES===//

    if(_cpt % 5 == 0)
        for_each(_model->Coins()->begin(), _model->Coins()->end(), [](Coin* &c){c->animate(50);});

    //===================//

    //=======================//
    //===SYNCHRO DIAMANTS===//

    if(_cpt % 5 == 0)
        for_each(_model->Diamonds()->begin(), _model->Diamonds()->end(), [](Diamond* &d){d->animate(50);});


    //===================//

    //===================//

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
        _window->draw(*_model->Coins()->at(i));

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
    _window->draw(_textGame);
    _window->draw(_textExit);
    _window->draw(_textShop);
    _window->draw(_textSettings);

    _window->display();
}

void View::drawSettings()
{
    _window->clear();

    _window->draw(_backgroundSettingsSprite);
    _window->draw(_textLang);
    _window->draw(_textDiff);
    _window->draw(_textFr);
    _window->draw(_textAng);
    _window->draw(_textFac);
    _window->draw(_textMoy);
    _window->draw(_textDur);

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
            }
            else if ((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::Escape) && gs!= menu && gs!=intro)
            {
                gs = menu;
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
                if((event.key.code == sf::Keyboard::Up || event.key.code == sf::Keyboard::Space) && !_model->getPlayer()->isJumping() && gs==intro)
                {
                    gs = menu;
                }
                if((event.key.code == sf::Keyboard::Down && gs == settings))
                {
                    if(cp==gen)
                    {
                        if(_textLang.getStyle() == sf::Text::Underlined)
                        {
                            _textLang.setStyle(sf::Text::Regular);
                            _textDiff.setStyle(sf::Text::Underlined);
                        }
                        else if(_textDiff.getStyle() == sf::Text::Underlined)
                        {
                            _textDiff.setStyle(sf::Text::Regular);
                            _textLang.setStyle(sf::Text::Underlined);
                        }

                    }
                    else if (cp==dif)
                    {
                        if(_textFac.getStyle() == sf::Text::Underlined)
                        {
                            _textFac.setStyle(sf::Text::Regular);
                            _textMoy.setStyle(sf::Text::Underlined);
                        }
                        else if(_textMoy.getStyle() == sf::Text::Underlined)
                        {
                            _textMoy.setStyle(sf::Text::Regular);
                            _textDur.setStyle(sf::Text::Underlined);
                        }
                        else if(_textDur.getStyle() == sf::Text::Underlined)
                        {
                            _textDur.setStyle(sf::Text::Regular);
                            _textFac.setStyle(sf::Text::Underlined);
                        }
                    }

                    else if(cp==lang)
                    {
                        if(_textFr.getStyle() == sf::Text::Underlined)
                        {
                            _textFr.setStyle(sf::Text::Regular);
                            _textAng.setStyle(sf::Text::Underlined);
                        }
                        else if(_textAng.getStyle() == sf::Text::Underlined)
                        {
                            _textAng.setStyle(sf::Text::Regular);
                            _textFr.setStyle(sf::Text::Underlined);
                        }
                    }
                }
                if((event.key.code == sf::Keyboard::Up || event.key.code == sf::Keyboard::Space) && !_model->getPlayer()->isJumping() && gs==settings)
                {
                    if(cp==gen)
                    {
                        if(_textLang.getStyle() == sf::Text::Underlined)
                        {
                            _textLang.setStyle(sf::Text::Regular);
                            _textDiff.setStyle(sf::Text::Underlined);
                        }
                        else if(_textDiff.getStyle() == sf::Text::Underlined)
                        {
                            _textDiff.setStyle(sf::Text::Regular);
                            _textLang.setStyle(sf::Text::Underlined);
                        }
                    }

                    else if (cp==dif)
                    {
                        if(_textFac.getStyle() == sf::Text::Underlined)
                        {
                            _textFac.setStyle(sf::Text::Regular);
                            _textDur.setStyle(sf::Text::Underlined);
                        }
                        else if(_textMoy.getStyle() == sf::Text::Underlined)
                        {
                            _textMoy.setStyle(sf::Text::Regular);
                            _textFac.setStyle(sf::Text::Underlined);
                        }
                        else if(_textDur.getStyle() == sf::Text::Underlined)
                        {
                            _textDur.setStyle(sf::Text::Regular);
                            _textMoy.setStyle(sf::Text::Underlined);
                        }
                    }

                    else if (cp==lang)
                    {
                        if(_textFr.getStyle() == sf::Text::Underlined)
                        {
                            _textFr.setStyle(sf::Text::Regular);
                            _textAng.setStyle(sf::Text::Underlined);
                        }
                        else if(_textAng.getStyle() == sf::Text::Underlined)
                        {
                            _textAng.setStyle(sf::Text::Regular);
                            _textFr.setStyle(sf::Text::Underlined);
                        }
                    }
                }
                if(event.key.code == sf::Keyboard::Return && gs==settings)
                {
                    if(cp==gen)
                    {
                        if(_textDiff.getStyle() == sf::Text::Underlined)
                        {
                            _textDiff.setStyle(sf::Text::Regular);
                            _textFac.setStyle(sf::Text::Underlined);
                            cp = dif;
                        }
                        else if (_textLang.getStyle() == sf::Text::Underlined)
                        {
                            _textLang.setStyle(sf::Text::Regular);
                            _textFr.setStyle(sf::Text::Underlined);
                            cp = lang;
                        }
                    }
                    else if (cp==lang)
                    {
                        if (_textFr.getStyle() == sf::Text::Underlined)
                        {
                            toFrench();
                            _textFr.setColor(sf::Color::Red);
                            _textAng.setColor(sf::Color::Blue);
                            _textFr.setStyle(sf::Text::Regular);
                            _textLang.setStyle(sf::Text::Underlined);
                            cp = gen;
                        }
                        else if (_textAng.getStyle() == sf::Text::Underlined)
                        {
                            toEnglish();
                            _textAng.setColor(sf::Color::Red);
                            _textFr.setColor(sf::Color::Blue);
                            _textAng.setStyle(sf::Text::Regular);
                            _textLang.setStyle(sf::Text::Underlined);
                            cp = gen;
                        }
                    }
                    else if (cp==dif)
                    {
                        if (_textFac.getStyle() == sf::Text::Underlined)
                        {
                            // changer la difficulté
                            _textFac.setColor(sf::Color::Red);
                            _textMoy.setColor(sf::Color::Blue);
                            _textDur.setColor(sf::Color::Blue);
                            _textFac.setStyle(sf::Text::Regular);
                            _textDiff.setStyle(sf::Text::Underlined);
                            cp = gen;
                        }
                        else if (_textMoy.getStyle() == sf::Text::Underlined)
                        {
                            // changer la difficulté
                            _textMoy.setColor(sf::Color::Red);
                            _textFac.setColor(sf::Color::Blue);
                            _textDur.setColor(sf::Color::Blue);
                            _textMoy.setStyle(sf::Text::Regular);
                            _textDiff.setStyle(sf::Text::Underlined);
                            cp = gen;
                        }
                        else  if (_textDur.getStyle() == sf::Text::Underlined)
                        {
                            // changer la difficulté
                            _textDur.setColor(sf::Color::Red);
                            _textMoy.setColor(sf::Color::Blue);
                            _textFac.setColor(sf::Color::Blue);
                            _textDur.setStyle(sf::Text::Regular);
                            _textDiff.setStyle(sf::Text::Underlined);
                            cp = gen;
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


                if(x>=300 && x<=380 && y>=306 && y<=330)
                    gs = game;
                else if(x>=300 && x<=385 && y>=356 && y<=380)
                    gs = shop;
                else if(x>=300 && x<=463 && y>=407 && y<=430)
                    gs = settings;
                else if(x>=300 && x<=404 && y>=457 && y<=479)
                {
                    _window->close();
                    result = false;
                }

            }
            else if (event.type == sf::Event::MouseMoved && gs == menu)
            {
                int xM = event.mouseMove.x;
                int yM = event.mouseMove.y;

                if(xM>=300 && xM<=380 && yM>=306 && yM<=330)
                    _textGame.setColor(sf::Color::Red);
                else
                    _textGame.setColor(sf::Color::Blue);

                if(xM>=300 && xM<=385 && yM>=356 && yM<=380)
                    _textShop.setColor(sf::Color::Red);
                else
                    _textShop.setColor(sf::Color::Blue);

                if(xM>=300 && xM<=463 && yM>=407 && yM<=430)
                    _textSettings.setColor(sf::Color::Red);
                else
                    _textSettings.setColor(sf::Color::Blue);

                if(xM>=300 && xM<=404 && yM>=457 && yM<=479)
                    _textExit.setColor(sf::Color::Red);
                else
                    _textExit.setColor(sf::Color::Blue);


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
    _textAng.setString("English");
    _textDiff.setString("Difficulty : ");
    _textDur.setString("Hard");
    _textFac.setString("Easy");
    _textFr.setString("French");
    _textLang.setString("Language : ");
    _textMoy.setString("Medium");

    _textGame.setString("Play");
    _textExit.setString("Exit");
    _textSettings.setString("Settings");
    _textShop.setString("Shop");

    _healthText.setString("HEALTH : ");

    _textPass.setString("<  PRESS SPACE TO START  >");
}

void View::toFrench()
{
    _textAng.setString("Anglais");
    _textDiff.setString("Difficulte : ");
    _textDur.setString("Difficile");
    _textFac.setString("Facile");
    _textFr.setString("Francais");
    _textLang.setString("Langue : ");
    _textMoy.setString("Moyen");

    _textGame.setString("Joueur");
    _textExit.setString("Quitter");
    _textSettings.setString("Paramètres");
    _textShop.setString("Boutique");

    _healthText.setString("SANTE : ");

    _textPass.setString("<  APPUYER SUR ESPACE POUR COMMENCER  >");

}

