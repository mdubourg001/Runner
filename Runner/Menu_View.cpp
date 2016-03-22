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
    _textShop.setString("Achat");
    _textShop.setPosition(300,350);

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
    _window->draw(_textGame);
    _window->draw(_textExit);
    _window->draw(_textShop);
    _window->draw(_textSettings);


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
        int x;
        int y;

        while (_window->pollEvent(event)) //tant qu'un évenement est détécté
        {


            if ((event.type == sf::Event::Closed) || //si on clique sur la croix de fermeture
                    ((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::Escape))) //on dit que l'évenement est "échap préssé"
            {
                _window->close(); //la fenetre est fermée
                result = false;
            }
            else if (event.type == sf::Event::MouseButtonPressed)
            {
                x = event.mouseButton.x;
                y = event.mouseButton.y;


                if(x>=300 && x<=380 && y>=306 && y<=330)
                    cout << "Jouer" << endl;
                else if(x>=300 && x<=385 && y>=356 && y<=380)
                    cout << "Achat" << endl;
                else if(x>=300 && x<=463 && y>=407 && y<=430)
                    cout << "Parametres" << endl;
                else if(x>=300 && x<=404 && y>=457 && y<=479)
                {
                    _window->close();
                    result = false;
                }

            }
            else if (event.type == sf::Event::MouseMoved)
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
