#ifndef _SETTINGS_VIEW_
#define _SETTINGS_VIEW_

#include <SFML/Graphics.hpp>
#include "main.h"
#include <iostream>






class Settings_View {
private:
    int _w, _h;

    sf::RenderWindow * _window;




public:
    Settings_View(int w, int h);
    ~Settings_View();

    void draw();
    bool treatEvents();





};
#endif
