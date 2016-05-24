#ifndef POPUP_H
#define POPUP_H

#include <SFML/Graphics.hpp>
#include <iostream>
#include "Button.h"

using namespace std;

class Popup : public sf::RectangleShape
{
protected:
    Button _left; //bouton 'ok'
    Button _right; //bouton 'annuler'
    sf::Text _text; //texte du popup
    sf::Font _font;
    sf::RectangleShape _timebar; //temps restant pour répondre
    bool _answered;
    bool _answer; //oui ou non

public:
    Popup();
    Popup(string text, string left_text = "OK", string right_text = "ANNULER");
    void initialise(string text, string left = "OK", string right = "ANNULER");

    void setString(string str);
    void setLeftString(string str);
    void setRightString(string str);
    bool answered() const;
    bool getanswer() const;
    void set_size_timebar(unsigned int size);
    void set_color_timebar(sf::Color color);
    int get_size_timebar() const;

    void draw(sf::RenderWindow *w);
    void treat_events(sf::RenderWindow *w, sf::Event &event);
    void reset();
};

#endif // POPUP_H
