#ifndef _VIEW_
#define _VIEW_

#include <SFML/Graphics.hpp>
#include <chrono>
#include "SlidingBackground.h"
#include "Bonus.h"
#include "Counter.h"
#include "Item.h"
#include "Button.h"
#include "Model.h"
#include "Popup.h"
#include "clock.h"
#include "HighscoresGrid.h"

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
    sf::RenderWindow * _window;
    Model* _model;
    SlidingBackground _background;

    int _w, _h;
    int _x_player;
    int _y_player;
    int cpt1;
    int cpt2;

    bool _loaded;
    bool _asChanged;

    bool _popup_displayed;
    bool _popup_confirm;

    string _ball_choose;
    string _back_choose;


    sf::RectangleShape _healthRect;
    sf::RectangleShape _backhealthRect;
    sf::RectangleShape _shieldRect;

    sf::Texture _playerStar;

    sf::Texture _player;
    sf::Sprite _playerSprite;

    sf::Texture _backgroundIntro;
    sf::Sprite _backgroundIntroSprite;

    sf::Texture _backgroundMenu;
    sf::Sprite _backgroundMenuSprite;

    sf::Texture _backgroundSettings;
    sf::Sprite _backgroundSettingsSprite;

    sf::Texture _backgroundShop;
    sf::Sprite _backgroundShopSprite;

    sf::Font _font;

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

    Button _buy_button;
    Button _select_button;

    sf::Text _healthText;
    sf::Text _textBall;
    sf::Text _textBack;
    sf::Text _textPass;
    sf::Text _text_pause;

    sf::RectangleShape _rectBall;
    sf::RectangleShape _rectBack;
    sf::RectangleShape _rectScreen;

    std::vector<Item*> _items;

    gamestates gs;
    langue lg;
    difficulte dif;
    choixShop cs;


    Counter _best;
    Counter _totalCoin;
    Counter _totalDiamond;

    Clock _background_timer;
    Clock _animation_timer;
    Clock _revive_timer;

    HighscoresGrid _highscores_grid;

    Popup* _popup;

public:
    View(int w, int h);
    ~View();

    void load();
    void loadNextShop();

    void setModel(Model * model);
    difficulte getDiff() const;
    gamestates getGs() const;
    choixShop getCs() const;
    bool getLoaded() const;
    string get_player_name() const;
    sf::Texture getPlayer() const;
    void setPlayer(const sf::Texture &player);
    string getBall_choose() const;
    void setBall_choose(const string &ball_choose);
    string getBack_choose() const;
    void setBack_choose(const string &back_choose);
    bool getAsChanged() const;
    void setAsChanged(bool asChanged);
    bool get_popup_displayed() const;
    void set_popup_displayed(bool popup_displayed);

    void synchronise();
    void synchroniseShop();
    void synchroniseShopBack();

    void recupBest();
    void recupCoins();
    void recupDiamonds();
    void recupChoose();
    void recup();

    void draw();
    void drawIntro();
    void drawMenu();
    void drawSettings();
    void drawShop();
    void drawHighscores();

    bool treatEvents();

    void toEnglish();
    void toFrench();
};
#endif
