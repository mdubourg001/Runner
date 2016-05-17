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
    bool _answered; //l'utilisateur à t'il répondu au popup

public:
    Popup();
    Popup(string text, string left_text = "OK", string right_text = "ANNULER");

    void setString(string str);
    void setLeftString(string str);
    void setRightString(string str);
    bool answered() const;

    void draw(sf::RenderWindow *w);
    bool getanswer();
};

#endif // POPUP_H
