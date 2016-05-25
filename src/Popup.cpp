#include "Popup.h"
#include "main.h"

Popup::Popup()
{
    
}

Popup::Popup(string text, string left_text, string right_text)
    : _answered {false}, _answer{true}, _read_text{false}
{
    this->setSize(sf::Vector2f(700, 250));
    this->setOrigin(sf::Vector2f(350, 125));
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
                     , SCREEN_HEIGHT/2 + 20);
    _right.initialise("res/redcube.png", "res/redcube.png", right_text
                      ,POLICEMENU, sf::Color::Black
                      , SCREEN_WIDTH/2 + 75
                      , SCREEN_HEIGHT/2 + 20);

    _timebar.setSize(sf::Vector2f(250, 25));
    _timebar.setOutlineThickness(5);
    _timebar.setFillColor(sf::Color::Green);
    _timebar.setOrigin(125, 25);
    _timebar.setPosition(this->getPosition().x
                         ,this->getPosition().y);
}

void Popup::initialise(string text, string left, string right)
{
    _text.setString(text);
    _text.setOrigin(_text.getLocalBounds().width/2
                    , _text.getLocalBounds().height/2);
    _text.setPosition(this->getPosition().x
                      ,this->getPosition().y - 75);

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

void Popup::set_size_timebar(unsigned int size)
{ _timebar.setSize(sf::Vector2f(size, 25)); }

void Popup::set_color_timebar(sf::Color color)
{ _timebar.setFillColor(color); }

int Popup::get_size_timebar() const
{ return _timebar.getSize().x; }

bool Popup::get_read_text() const
{ return _read_text; }

void Popup::set_read_text(bool read)
{ _read_text = read; }

std::string Popup::get_temp_name() const
{ return _temp_name.first; }

void Popup::set_temp_name(const std::string &temp_name)
{
    _temp_name.first = temp_name;
    this->actualise_read_name();
}


/*!
 * \brief Popup::draw
 * \param w
 * dessine le popup au milieu de l'écran
 */
void Popup::draw(sf::RenderWindow *w)
{
    w->draw(*this);
    w->draw(_text);
    _left.draw(w);
    _right.draw(w);

    if(_timebar.getSize().x > 0)
        w->draw(_timebar);
}


/*!
 * \brief Popup::treat_events
 * \param w
 * \param event
 * traite les évenements souris quand le popup est affiché
 */
void Popup::treat_events(sf::RenderWindow *w, sf::Event &event)
{
    while(w->pollEvent(event))
    {
        if(event.type == sf::Event::MouseButtonPressed)
        {
            float x = event.mouseButton.x;
            float y = event.mouseButton.y;

            pair<float, float> left_x_bounds = std::make_pair(_left.getPos().x + _left.get_size().width, _left.getPos().x);
            pair<float, float> left_y_bounds = std::make_pair(_left.getPos().y + _left.get_size().height, _left.getPos().y);
            pair<float, float> right_x_bounds = std::make_pair(_right.getPos().x + _right.get_size().width, _right.getPos().x);
            pair<float, float> right_y_bounds = std::make_pair(_right.getPos().y + _right.get_size().height, _right.getPos().y);

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

        else if(_read_text && event.type == sf::Event::TextEntered)
        {
            if(event.text.unicode == 8) //backspace
            {
                if(_temp_name.first.size() > 0)
                    _temp_name.first.pop_back();
            }
            else if(event.text.unicode >= 97 && event.text.unicode <= 122) //si la touche entrée est bien une lettre
            {
                if(_temp_name.first.size() < 6)
                    _temp_name.first += static_cast<char>(event.text.unicode);
            }
            else if(event.text.unicode == 13) //retour chariot
            {
                _answered = true;
                _answer = true;
            }

            this->actualise_read_name();

        }
    }
}


void Popup::reset()
{
    _timebar.setSize(sf::Vector2f(0, 25));
    _temp_name.first.clear();
    _temp_name.second.clear();
    _answered = false;
    _answer = true;
}


void Popup::actualise_read_name()
{
    if(_read_text)
    {
        _temp_name.second.clear();
        for(unsigned int i=0; i < _temp_name.first.size() ; i++)
        {
            _temp_name.second += _temp_name.first.at(i);
            _temp_name.second += " ";
        }
        while(_temp_name.second.size() < 11)
        {
            _temp_name.second += " _";
        }

        this->initialise("SAISISSEZ VOTRE NOM: " + _temp_name.second , "VALIDER", "QUITTER");
    }
}


















