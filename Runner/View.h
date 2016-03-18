#ifndef _VIEW_
#define _VIEW_

#include <SFML/Graphics.hpp>
#include "SlidingBackground.h"



class Model;

class View {
private:
    int _w, _h;

    sf::RenderWindow * _window;
    Model* _model;

    sf::Texture _player;
    sf::Sprite _playerSprite;
    int _x_player;
    int _y_player;

    SlidingBackground _background;

public:
    View(int w, int h);
    ~View();


    void setModel(Model * model);
    void draw();
    void synchronise();
    bool treatEvents();

};
#endif
