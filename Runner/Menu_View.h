#ifndef _MENU_VIEW_
#define _MENU_VIEW_

#include <SFML/Graphics.hpp>


class Menu_Model;

class Menu_View {
private:
    int _w, _h;

    sf::RenderWindow * _window;
    Menu_Model* _menu_model;


    sf::Texture _backgroundMenu;
    sf::Sprite _backgroundMenuSprite;

    sf::Font _font;
    sf::Text _textGame;
    sf::Text _textExit;
    sf::Text _textSettings;
    sf::Text _textShop;


public:
    Menu_View(int w, int h);
    ~Menu_View();


    void setModel(Menu_Model * menu_model);
    void draw();
    bool treatEvents();

};
#endif
