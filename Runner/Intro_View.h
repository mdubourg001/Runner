#ifndef _INTRO_VIEW_
#define _INTRO_VIEW_

#include <SFML/Graphics.hpp>


class Intro_Model;

class Intro_View {
private:
    int _w, _h;

    sf::RenderWindow * _window;
    Intro_Model* _intro_model;


    sf::Texture _backgroundIntro;
    sf::Sprite _backgroundIntroSprite;

    sf::Font _font;
    sf::Text _text;


public:
    Intro_View(int w, int h);
    ~Intro_View();


    void setModel(Intro_Model * intro_model);
    void draw();
    bool treatEvents();

};
#endif
