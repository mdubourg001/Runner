#ifndef _VIEW_
#define _VIEW_

#include <SFML/Graphics.hpp>
#include "SlidingBackground.h"
#include "Bonus.h"

enum gamestates
{
    intro,
    menu,
    game,
    shop,
    settings
};

enum choixParametres
{
    gen,
    lang,
    dif
};


class Model;

class View
{
private:
    int _w, _h;

    gamestates gs;

    sf::RenderWindow * _window;
    Model* _model;

    sf::Texture _player;
    sf::Sprite _playerSprite;
    int _x_player;
    int _y_player;

    SlidingBackground _background;

    sf::Texture _backgroundIntro;
    sf::Sprite _backgroundIntroSprite;

    sf::Texture _backgroundMenu;
    sf::Sprite _backgroundMenuSprite;

    sf::Texture _backgroundSettings;
    sf::Sprite _backgroundSettingsSprite;


    sf::Font _font;

    sf::Text _textPass;
    sf::Text _textGame;
    sf::Text _textExit;
    sf::Text _textSettings;
    sf::Text _textShop;
    sf::Text _textLang;
    sf::Text _textDiff;
    sf::Text _textFr;
    sf::Text _textAng;
    sf::Text _textFac;
    sf::Text _textMoy;
    sf::Text _textDur;
    sf::Text _healthText;



    choixParametres cp;


    int _cpt;

public:
    View(int w, int h);
    ~View();


    void setModel(Model * model);
    void draw();
    void drawIntro();
    void drawMenu();
    void drawSettings();
    void toEnglish();
    void toFrench();
    void synchronise();
    bool treatEvents();
    gamestates getGs();

};
#endif
