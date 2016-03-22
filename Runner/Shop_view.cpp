#include "Shop_view.h"
#include "Shop_model.h"
#include "main.h"

#include <fstream>
#include <sstream>
#include <iostream>

using namespace std;
//using namespace sf;

//=======================================
// Constructeur
//=======================================
Shop_View::Shop_View(int w, int h)
    : _w(w),_h(h)
{
    _window = new sf::RenderWindow(sf::VideoMode(w, h, 32), "Runner", sf::Style::Close); //RenderWindow est une classe qui définie une fenêtre qui peut etre utilisée pour faire du dessin 2D
    _window->setFramerateLimit(60); //fixe la limite de fps
    _window->setKeyRepeatEnabled(false); //désactive la répétition des touches

    /*if (!_backgroundShop.loadFromFile(BACKGROUND_MENU_IMAGE)) //charge le fichier city.png et le place dans la texture background
    {
        std::cerr << "ERROR when loading image file: "
                  << BACKGROUND_MENU_IMAGE << std::endl;
        exit(EXIT_FAILURE);
    }
    else
    {
        _backgroundShopSprite.setTexture(_backgroundShop); //définie la texture background comme texture du sprite de background
        _backgroundShopSprite.setPosition(sf::Vector2f(0.f,0.f)); //définie la position du sprite de background
    }*/

    _rectBall.setSize(sf::Vector2f(SCREEN_WIDTH/2,50));
    _rectBall.setFillColor(sf::Color(100,100,100,255));

    _rectBack.setSize(sf::Vector2f(SCREEN_WIDTH/2,50));
    _rectBack.setPosition(SCREEN_WIDTH/2,0);
    _rectBack.setFillColor(sf::Color(150,150,150,255));


    _font.loadFromFile(POLICE);

    _textBall.setFont(_font);
    _textBall.setColor(sf::Color::Blue);
    _textBall.setString("Ball : ");
    _textBall.setPosition(10,10);

    _textBack.setFont(_font);
    _textBack.setColor(sf::Color::Blue);
    _textBack.setString("Background : ");
    _textBack.setPosition((SCREEN_WIDTH/2)+10,10);

    for(int i=0;i<14;i++)
        _items.push_back(new Item());


    for(int i=0;i<_items.size();i++)
    {
        _items.at(i)->setPosition(3,53 + 51*i);
        _items.at(i)->setOutlineThickness(3);
        _items.at(i)->setOutlineColor(sf::Color::Black);
        _items.at(i)->setSize(sf::Vector2f(SCREEN_WIDTH/6,50));

    }

    _items.at(0)->setSelected(true);
    _items.at(5)->setName("dsfsdfs");

}

//=======================================
// Destructeur
//=======================================
Shop_View::~Shop_View() //destructeur de la classe View
{
    if(_window!= NULL)
        delete _window;
}

//=======================================
// Accesseurs en écriture
//=======================================

//=======================================
// Fonction de dessin
//=======================================
void Shop_View::draw()
{
    _window->clear(sf::Color::White);

    //dessin du background

   // _window->draw(_backgroundShopSprite);
    _window->draw(_rectBall);
    _window->draw(_rectBack);
    _window->draw(_textBall);
    _window->draw(_textBack);

    for(int i=0;i<_items.size();i++)
    {
        _window->draw(*_items.at(i));
        _items.at(i)->drawText(_window);
    }


    //--------------------


    //--------------------

    _window->display();
}

//=======================================
// Traitement des evenements
//=======================================
bool Shop_View::treatEvents()
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
            else if ((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::Right))
            {
                if(_rectBall.getFillColor() == sf::Color(100,100,100,255))
                {
                    _rectBall.setFillColor(sf::Color(150,150,150,255));
                    _rectBack.setFillColor(sf::Color(100,100,100,255));
                }
                else
                {
                    _rectBall.setFillColor(sf::Color(100,100,100,255));
                    _rectBack.setFillColor(sf::Color(150,150,150,255));
                }
                for(int i=1;i<_items.size();i++)
                    _items.at(i)->setSelected(false);
                _items.at(0)->setSelected(true);
            }

            else if ((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::Left))
            {
                if(_rectBall.getFillColor() == sf::Color(100,100,100,255))
                {
                    _rectBall.setFillColor(sf::Color(150,150,150,255));
                    _rectBack.setFillColor(sf::Color(100,100,100,255));
                }
                else
                {
                    _rectBall.setFillColor(sf::Color(100,100,100,255));
                    _rectBack.setFillColor(sf::Color(150,150,150,255));
                }
                for(int i=1;i<_items.size();i++)
                    _items.at(i)->setSelected(false);
                _items.at(0)->setSelected(true);
            }
            else if ((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::Return))
            {

            }

            else if ((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::Down))
            {

                for(int i=0;i<_items.size();i++)
                {
                    if(_items.at(i)->isSelected() && i != 13)
                    {
                        _items.at(i)->setSelected(false);
                        _items.at(i+1)->setSelected(true);
                        break;
                    }
                }
            }
            else if ((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::Up))
            {
                for(int i=0;i<_items.size();i++)
                {
                    if(_items.at(i)->isSelected() && i != 0)
                    {
                        _items.at(i)->setSelected(false);
                        _items.at(i-1)->setSelected(true);
                        break;
                    }
                }
            }
        }


    }
    return result;
}

//=======================================
// Autres méthodes
//=======================================

void Shop_View::synchronise()
{
    for(int i=0;i<_items.size();i++)
    {
    if(_items.at(i)->isSelected())
        _items.at(i)->setFillColor(sf::Color(150,175,175,255));
    else
        _items.at(i)->setFillColor(sf::Color(200,200,200,255));
    }
}
