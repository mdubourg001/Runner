#ifndef _SHOP_VIEW_
#define _SHOP_VIEW_

#include <SFML/Graphics.hpp>
#include "main.h"
#include <iostream>

enum choixShop
{
    gene,
    ball,
    back
};

class Shop_View {
private:
    int _w, _h;

    sf::RenderWindow * _window;


    sf::Texture _backgroundShop;
    sf::Sprite _backgroundShopSprite;

    sf::Font _font;
    sf::Text _textBall;
    sf::Text _textBack;

    sf::RectangleShape _rectBall;
    sf::RectangleShape _rectBack;

    std::vector<Item*> _items;

    choixShop cs;

public:
    Shop_View(int w, int h);
    ~Shop_View();

    void draw();
    bool treatEvents();
    void synchronise();



};
#endif
