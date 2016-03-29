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
    : _w(w),_h(h), _x_player(SCREEN_WIDTH/15), _y_player(SCREEN_HEIGHT-SCREEN_HEIGHT/5), _background(SCREEN_WIDTH, SCREEN_HEIGHT, 5), _cpt(160)
{
    _window = new sf::RenderWindow(sf::VideoMode(w, h, 32), "Runner", sf::Style::Close); //RenderWindow est une classe qui définie une fenêtre qui peut etre utilisée pour faire du dessin 2D  
    _window->setFramerateLimit(FRAMERATE_LIMIT); //fixe la limite de fps
    _window->setVerticalSyncEnabled(true);
    _window->setKeyRepeatEnabled(true); //désactive la répétition des touches

    if (!_background.loadTextures(BACKGROUND_IMAGE_L, BACKGROUND_IMAGE_R)) //charge le fichier city.png et le place dans la texture background
    {
        std::cerr << "ERROR when loading image file: "
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

//dessin des obstacles

     for(int i=0; i<_model->Obstacles()->size() ; i++)
        _window->draw(*_model->Obstacles()->at(i));

//--------------------

//dessin de la balle

    _model->getPlayer()->drawShadow(_window);
    _window->draw(_playerSprite);

//--------------------



    _model->drawInterface(_window);


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
        while (_window->pollEvent(event)) //tant qu'un évenement est détécté
        {
            if ((event.type == sf::Event::Closed) || //si on clique sur la croix de fermeture
                    ((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::Escape))) //on dit que l'évenement est "échap préssé"
            {
                _window->close(); //la fenetre est fermée
                result = false;
            }

            else if (event.type == sf::Event::KeyPressed)
            {
                if((event.key.code == sf::Keyboard::Up || event.key.code == sf::Keyboard::Space) && !_model->getPlayer()->isJumping())
                {
                    _model->setPlayerDirection(up);
                }

                if(event.key.code == sf::Keyboard::Left)
                {
                    _model->setPlayerDirection(l);
                }

                if(event.key.code == sf::Keyboard::Right)
                {
                    _model->setPlayerDirection(r);
                }
            }

            else if(event.type == sf::Event::KeyReleased)
            {
                if(event.key.code != sf::Keyboard::Up && event.key.code != sf::Keyboard::Space)
                    _model->setPlayerDirection(none);
            }
        }
    }
    return result;
}
