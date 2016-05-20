#include "Popup.h"
#include "main.h"

Popup::Popup()
{

}

Popup::Popup(string text, string left_text, string right_text)
    : _answered {false}, _answer{true}
{
    this->setSize(sf::Vector2f(350, 250));
    this->setOrigin(sf::Vector2f(175, 125));
    this->setPosition(sf::Vector2f(SCREEN_WIDTH/2, SCREEN_HEIGHT/2));
    this->setFillColor(sf::Color(102, 178, 255, 255));
    this->setOutlineThickness(10);
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

void Popup::initialise(string text, string left, string right)
{
    _text.setString(text);
    _left.setString(left);
    _right.setString(right);
}


void Popup::setString(string str)
{ _text.setString(str) ;}

void Popup::setLeftString(string str)
{ _left.setString(str); }

void Popup::setRightString(string str)
{ _right.setString(str); }

bool Popup::answered() const
{ return _answered; }

bool Popup::getanswer() const
{ return _answer; }


void Popup::draw(sf::RenderWindow *w)
{
    w->draw(*this);
    w->draw(_text);
    _left.draw(w);
    _right.draw(w);
}

void Popup::treat_events(sf::RenderWindow *w, sf::Event &event)
{
    while(w->pollEvent(event))
    {
        if(event.type == sf::Event::MouseButtonPressed)
        {
            float x = event.mouseButton.x;
            float y = event.mouseButton.y;

            pair<float, float> left_x_bounds = std::make_pair(_left.getPos().x + _left.getLocalBounds().width/2, _left.getPos().x - _left.getLocalBounds().width/2);
            pair<float, float> left_y_bounds = std::make_pair(_left.getPos().y + _left.getLocalBounds().height/2, _left.getPos().y - _left.getLocalBounds().height/2);
            pair<float, float> right_x_bounds = std::make_pair(_right.getPos().x + _right.getLocalBounds().width/2, _right.getPos().x - _right.getLocalBounds().width/2);
            pair<float, float> right_y_bounds = std::make_pair(_right.getPos().y + _right.getLocalBounds().height/2, _right.getPos().y - _right.getLocalBounds().height/2);

            if(x <= left_x_bounds.first && x >= left_x_bounds.second
                    && y <= left_y_bounds.first && y>= left_y_bounds.second)
            {
                _answered = true;
                _answer = true;
            }
            else if(x <= right_x_bounds.first && x >= right_x_bounds.second
                    && y <= right_y_bounds.first && y>= right_y_bounds.second)
            {
                _answered = true;
                _answer = false;
            }

        }
    }
}


















