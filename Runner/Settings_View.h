#ifndef _SETTINGS_VIEW_
#define _SETTINGS_VIEW_

#include <SFML/Graphics.hpp>
#include "main.h"
#include <iostream>



enum choixParametres
{
    gen,
    lang,
    dif
};


class Settings_View {
private:
    int _w, _h;

    sf::RenderWindow * _window;


    sf::Texture _backgroundSettings;
    sf::Sprite _backgroundSettingsSprite;

    sf::Font _font;
    sf::Text _textLang;
    sf::Text _textDiff;
    sf::Text _textFr;
    sf::Text _textAng;
    sf::Text _textFac;
    sf::Text _textMoy;
    sf::Text _textDur;


    choixParametres cp;

public:
    Settings_View(int w, int h);
    ~Settings_View();

    void draw();
    bool treatEvents();
    void toEnglish();
    void toFrench();




};
#endif
