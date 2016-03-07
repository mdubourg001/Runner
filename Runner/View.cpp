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
    : _w(w),_h(h), _xsprite(SCREEN_WIDTH/15), _ysprite(SCREEN_HEIGHT-SCREEN_HEIGHT/5)
{
    _window = new sf::RenderWindow(sf::VideoMode(w, h, 32), "Runner", sf::Style::Close); //RenderWindow est une classe qui définie une fenêtre qui peut etre utilisée pour faire du dessin 2D

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
        _playerSprite.setPosition(sf::Vector2f(_xsprite, _ysprite));
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

    _model->getPlayerPosition(_xsprite, _ysprite);
    _playerSprite.setPosition(sf::Vector2f(_xsprite, _ysprite));
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
                if(event.type == sf::Keyboard::Left)
                    _model->setPlayerDirection(true);
            }
        }
    }
    return result;
}

