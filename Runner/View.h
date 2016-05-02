#ifndef _VIEW_
#define _VIEW_

#include <SFML/Graphics.hpp>
#include "SlidingBackground.h"
#include "Bonus.h"
#include "Item.h"

enum gamestates
{
    intro,
    menu,
    game,
    shop,
    settings,
    highscores
};

enum langue
{
    fr,
    ang
};

enum difficulte
{
    facile,
    moyen,
    difficile
};

enum choixShop
{
    ball,
    back
};

class Model;
class Item;

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

    std::chrono::time_point<std::chrono::system_clock> _start, _end;

    sf::RectangleShape _healthRect;
    sf::RectangleShape _backhealthRect;
    sf::RectangleShape _shieldRect;

    sf::Texture _backgroundIntro;
    sf::Sprite _backgroundIntroSprite;

    sf::Texture _backgroundMenu;
    sf::Sprite _backgroundMenuSprite;

    sf::Texture _backgroundSettings;
    sf::Sprite _backgroundSettingsSprite;

    sf::Texture _backgroundShop;
    sf::Sprite _backgroundShopSprite;

    sf::Texture _redButton;
    sf::Texture _blueButton;

    sf::Sprite _redButtonSpriteSettings;
    sf::Sprite _blueButtonSpriteSettings;
    sf::Sprite _redButtonSpriteHighscores;
    sf::Sprite _blueButtonSpriteHighscores;
    sf::Sprite _redButtonSpriteGame;
    sf::Sprite _blueButtonSpriteGame;
    sf::Sprite _redButtonSpriteShop;
    sf::Sprite _blueButtonSpriteShop;
    sf::Sprite _redButtonSpriteExit;
    sf::Sprite _blueButtonSpriteExit;
    sf::Sprite _redButtonSpriteFrancais;
    sf::Sprite _blueButtonSpriteFrancais;
    sf::Sprite _redButtonSpriteAnglais;
    sf::Sprite _blueButtonSpriteAnglais;
    sf::Sprite _redButtonSpriteFacile;
    sf::Sprite _blueButtonSpriteFacile;
    sf::Sprite _redButtonSpriteMoyen;
    sf::Sprite _blueButtonSpriteMoyen;
    sf::Sprite _redButtonSpriteDifficile;
    sf::Sprite _blueButtonSpriteDifficile;


    bool SettingsSelected;
    bool HighscoresSelected;
    bool GameSelected;
    bool ShopSelected;
    bool ExitSelected;



    sf::Font _font;
    sf::Font _fontmenu;

    sf::Text _textPass;
    sf::Text _textGame;
    sf::Text _textExit;
    sf::Text _textSettings;
    sf::Text _textShop;
    sf::Text _textHighscores;
    sf::Text _textLang;
    sf::Text _textDiff;
    sf::Text _textFr;
    sf::Text _textAng;
    sf::Text _textFac;
    sf::Text _textMoy;
    sf::Text _textDur;
    sf::Text _healthText;
    sf::Text _textBall;
    sf::Text _textBack;


    sf::RectangleShape _rectBall;
    sf::RectangleShape _rectBack;
    sf::RectangleShape _rectScreen;

    std::vector<Item*> _items;

    choixShop cs;
    langue lg;
    difficulte dif;

    int _cpt;

public:
    View(int w, int h);
    ~View();


    void setModel(Model * model);
    void draw();
    void drawIntro();
    void drawMenu();
    void drawSettings();
    void drawShop();
    void drawHighscores();
    void toEnglish();
    void toFrench();
    void synchronise();
    void synchroniseShop();
    bool treatEvents();
    gamestates getGs();

};
#endif
