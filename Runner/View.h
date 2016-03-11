#ifndef _VIEW_
#define _VIEW_

#include <SFML/Graphics.hpp>

const std::string BACKGROUND_IMAGE = "res/city.png";
const std::string BALL_IMAGE = "res/ball.png";

class Model;

class View {
private:
    int _w, _h;

    sf::RenderWindow * _window;
    Model * _model;

    sf::Texture _player;
    sf::Sprite _playerSprite;
    int _x_player;
    int _y_player;

    sf::Texture _background;
    sf::Sprite _backgroundSprite;

public:
    View(int w, int h);
    ~View();

    void setModel(Model * model);
    void draw();
    bool treatEvents();

};
#endif
