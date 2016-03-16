#include "Menu_View.h"
#include "Menu_Model.h"
#include "main.h"

#include <fstream>
#include <sstream>
#include <iostream>

using namespace std;
//using namespace sf;

//=======================================
// Constructeur
//=======================================
Menu_View::Menu_View(int w, int h)
    : _w(w),_h(h)
{
    _window = new sf::RenderWindow(sf::VideoMode(w, h, 32), "Runner", sf::Style::Close); //RenderWindow est une classe qui définie une fenêtre qui peut etre utilisée pour faire du dessin 2D
    _window->setFramerateLimit(60); //fixe la limite de fps
    _window->setKeyRepeatEnabled(true); //désactive la répétition des touches

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

    _font.loadFromFile(POLICE);
    _text.setFont(_font);
    _text.setColor(sf::Color::Blue);
    _text.setString("Appuyer sur Espace pour continuer");
    _text.setPosition(300,500);

}

//=======================================
// Destructeur
//=======================================
Menu_View::~Menu_View() //destructeur de la classe View
{
    if(_window!= NULL)
        delete _window;
}

//=======================================
// Accesseurs en écriture
//=======================================
void Menu_View::setModel(Menu_Model * menu_model) //setter qui permet de modifier le modele associé à la vue
{
    _menu_model = menu_model;
}

//=======================================
// Fonction de dessin
//=======================================
void Menu_View::draw()
{
    _window->clear();

//dessin du background

    _window->draw(_backgroundMenuSprite);
    _window->draw(_text);

//--------------------


//--------------------

    _window->display();
}

//=======================================
// Traitement des evenements
//=======================================
bool Menu_View::treatEvents()
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
                _text.setString("EH BAH NON C ETAIT UNE BLAGUE !");

            }
        }
    }
    return result;
}
