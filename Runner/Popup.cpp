#include "Popup.h"
#include "main.h"

Popup::Popup()
{

}

Popup::Popup(string text, string left_text, string right_text)
{
    this->setSize(sf::Vector2f(350, 250));
    this->setOrigin(sf::Vector2f(175, 125));
    this->setPosition(sf::Vector2f(SCREEN_WIDTH/2, SCREEN_HEIGHT/2));
    this->setFillColor(sf::Color(102, 178, 255, 255));
    this->setOutlineThickness(15);
    this->setOutlineColor(sf::Color::Black);

    _font.loadFromFile(POLICEMENU);
    _text.setString(text);
    _text.setFont(_font);
    _text.setColor(sf::Color::Black);
    _text.setOrigin(_text.getLocalBounds().width/2
                    , _text.getLocalBounds().height/2);
    _text.setPosition(this->getPosition().x
                      ,this->getPosition().y - 75);

    _left.initialise("res/greencube.png", "res/greencube.png", left_text
                     ,POLICEMENU, sf::Color::Black
                     , SCREEN_WIDTH/2 - 125
                     , SCREEN_HEIGHT/2 + 40);
    _right.initialise("res/redcube.png", "res/redcube.png", right_text
                      ,POLICEMENU, sf::Color::Black
                      , SCREEN_WIDTH/2 + 75
                      , SCREEN_HEIGHT/2 + 40);
}




void Popup::setString(string str)
{ _text.setString(str) ;}

void Popup::setLeftString(string str)
{ _left.setString(str); }

void Popup::setRightString(string str)
{ _right.setString(str); }

bool Popup::answered() const
{ return _answered; }



void Popup::draw(sf::RenderWindow *w)
{
    w->draw(*this);
    w->draw(_text);
    _left.draw(w);
    _right.draw(w);
}

bool Popup::getanswer()
{

}
