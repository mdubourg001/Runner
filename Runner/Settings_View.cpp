#include "Settings_View.h"
#include "Settings_Model.h"
#include "main.h"

#include <fstream>
#include <sstream>
#include <iostream>

using namespace std;
//using namespace sf;

//=======================================
// Constructeur
//=======================================
Settings_View::Settings_View(int w, int h)
    : _w(w),_h(h) , cp(gen)
{
    _window = new sf::RenderWindow(sf::VideoMode(w, h, 32), "Runner", sf::Style::Close); //RenderWindow est une classe qui définie une fenêtre qui peut etre utilisée pour faire du dessin 2D
    _window->setFramerateLimit(60); //fixe la limite de fps
    _window->setKeyRepeatEnabled(true); //désactive la répétition des touches

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

    _font.loadFromFile(POLICE);

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

}

//=======================================
// Destructeur
//=======================================
Settings_View::~Settings_View() //destructeur de la classe View
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
void Settings_View::draw()
{
    _window->clear();

    //dessin du background

    _window->draw(_backgroundSettingsSprite);
    _window->draw(_textLang);
    _window->draw(_textDiff);
    _window->draw(_textFr);
    _window->draw(_textAng);
    _window->draw(_textFac);
    _window->draw(_textMoy);
    _window->draw(_textDur);


    //--------------------


    //--------------------

    _window->display();
}

//=======================================
// Traitement des evenements
//=======================================
bool Settings_View::treatEvents()
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
            else if ((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::Down))
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

            else if ((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::Up))
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
            else if ((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::Return))
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
    }
    return result;
}

//=======================================
// Autres méthodes
//=======================================

void Settings_View::toEnglish()
{
    _textAng.setString("English");
    _textDiff.setString("Difficulty : ");
    _textDur.setString("Hard");
    _textFac.setString("Easy");
    _textFr.setString("French");
    _textLang.setString("Language : ");
    _textMoy.setString("Medium");
}

void Settings_View::toFrench()
{
    _textAng.setString("Anglais");
    _textDiff.setString("Difficulte : ");
    _textDur.setString("Difficile");
    _textFac.setString("Facile");
    _textFr.setString("Francais");
    _textLang.setString("Langue : ");
    _textMoy.setString("Moyen");
}
