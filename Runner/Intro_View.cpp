#include "Intro_View.h"
#include "Intro_Model.h"
#include "main.h"

#include <fstream>
#include <sstream>
#include <iostream>

using namespace std;
//using namespace sf;

//=======================================
// Constructeur
//=======================================
Intro_View::Intro_View(int w, int h)
    : _w(w),_h(h)
{
    _window = new sf::RenderWindow(sf::VideoMode(w, h, 32), "Runner", sf::Style::Close); //RenderWindow est une classe qui définie une fenêtre qui peut etre utilisée pour faire du dessin 2D
    _window->setFramerateLimit(60); //fixe la limite de fps
    _window->setKeyRepeatEnabled(true); //désactive la répétition des touches

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

    _font.loadFromFile(POLICE);
    _text.setFont(_font);
    _text.setColor(sf::Color::Black);
    _text.setString("<  PRESS SPACE TO START  >");
    _text.setPosition(510,650);
}

//=======================================
// Destructeur
//=======================================
Intro_View::~Intro_View() //destructeur de la classe View
{
    if(_window!= NULL)
        delete _window;
}

//=======================================
// Accesseurs en écriture
//=======================================
void Intro_View::setModel(Intro_Model * intro_model) //setter qui permet de modifier le modele associé à la vue
{
    _intro_model = intro_model;
}

//=======================================
// Fonction de dessin
//=======================================
void Intro_View::draw()
{
    _window->clear();

//dessin du background

    _window->draw(_backgroundIntroSprite);
    _window->draw(_text);

//--------------------


//--------------------

    _window->display();
}

//=======================================
// Traitement des evenements
//=======================================
bool Intro_View::treatEvents()
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
            else if ((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::Space))
            {
                _text.setString("TODO");

            }
        }
    }
    return result;
}
