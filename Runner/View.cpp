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
    : _w(w),_h(h), _x_player(SCREEN_WIDTH/15), _y_player(SCREEN_HEIGHT-SCREEN_HEIGHT/5)
{
    _window = new sf::RenderWindow(sf::VideoMode(w, h, 32), "Runner", sf::Style::Close); //RenderWindow est une classe qui définie une fenêtre qui peut etre utilisée pour faire du dessin 2D  
    _window->setFramerateLimit(60); //fixe la limite de fps
    _window->setKeyRepeatEnabled(true); //désactive la répétition des touches

    if (!_background.loadFromFile(BACKGROUND_IMAGE)) //charge le fichier city.png et le place dans la texture background
    {
        std::cerr << "ERROR when loading image file: "
                  << BACKGROUND_IMAGE << std::endl;
        exit(EXIT_FAILURE);
    }
    else
    {
        _backgroundSprite.setTexture(_background); //définie la texture background comme texture du sprite de background
        _backgroundSprite.setPosition(sf::Vector2f(0.f,0.f)); //définie la position du sprite de background
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

//=======================================
// Fonction de dessin
//=======================================
void View::draw()
{
    _window->clear();

//dessin du background

    _window->draw(_backgroundSprite);

//--------------------

//dessin de la balle

    _playerSprite.setPosition(sf::Vector2f(_model->getPlayer()->getPosx(), _model->getPlayer()->getPosy()));
    _playerSprite.rotate(10);
    _window->draw(_playerSprite);

//--------------------

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
            cout << "Event detected" << endl; //on affiche "Event detected"

            if ((event.type == sf::Event::Closed) || //si on clique sur la croix de fermeture
                    ((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::Escape))) //on dit que l'évenement est "échap préssé"
            {
                _window->close(); //la fenetre est fermée
                result = false;
            }

            else if (event.type == sf::Event::KeyPressed)
            {
                if(event.key.code == sf::Keyboard::Up)
                {
                    _model->setPlayerDirection(up);
                }

                if(event.key.code == sf::Keyboard::Left)
                {
                    _model->setPlayerDirection(l);
//                    _playerSprite.setRotation(-15);
                }

                else if(event.key.code == sf::Keyboard::Right)
                {
                    _model->setPlayerDirection(r);
//                    _playerSprite.setRotation(15);
                }
            }

            else if(event.type == sf::Event::KeyReleased)
            {
                _model->setPlayerDirection(none);
//                _playerSprite.setRotation(10);
            }
        }
    }
    return result;
}

