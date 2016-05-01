#ifndef _VIEW_
#define _VIEW_

#include <SFML/Graphics.hpp>
#include "SlidingBackground.h"
#include "Bonus.h"



class Model;

class View
{
private:
    int _w, _h;

    sf::RenderWindow * _window;
    Model* _model;

    sf::Texture _player;
    sf::Sprite _playerSprite;
    int _x_player;
    int _y_player;

    SlidingBackground _background;

    std::chrono::time_point<std::chrono::system_clock> _start, _end;

    int _cpt;

public:
    View(int w, int h);
    ~View();


    void setModel(Model * model);
    void draw();
    void synchronise();
    bool treatEvents();

};
#endif
