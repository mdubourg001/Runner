#ifndef _VIEW_
#define _VIEW_

#include <SFML/Graphics.hpp>
#include <chrono>
#include "SlidingBackground.h"
#include "Bonus.h"
#include "Counter.h"
#include "Item.h"
#include "Button.h"

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

    sf::Font _font;
    sf::Font _fontmenu;

    std::pair<Button, Button> _settings_button;
    std::pair<Button, Button> _highscores_button;
    std::pair<Button, Button> _game_button;
    std::pair<Button, Button> _shop_button;
    std::pair<Button, Button> _exit_button;
    std::pair<Button, Button> _french_button;
    std::pair<Button, Button> _english_button;
    std::pair<Button, Button> _easy_button;
    std::pair<Button, Button> _medium_button;
    std::pair<Button, Button> _hard_button;

    sf::Text _healthText;
    sf::Text _topScores;
    sf::Text _textBall;
    sf::Text _textBack;
    sf::Text _textPass;

    sf::RectangleShape _rectBall;
    sf::RectangleShape _rectBack;
    sf::RectangleShape _rectScreen;

    std::vector<Item*> _items;

    choixShop cs;
    langue lg;
    difficulte dif;

    int _cpt;
    Counter _best;
    Counter _totalCoin;
    Counter _totalDiamond;

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
    difficulte getDiff();
    void recupBest();
    void recupCoins();
    void recupDiamonds();
    void recup();

};
#endif
