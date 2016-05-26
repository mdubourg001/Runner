#include "HighscoresGrid.h"


HighscoresGrid::HighscoresGrid()
{
    this->setSize(sf::Vector2f(SCREEN_WIDTH - SCREEN_WIDTH/3
                               , SCREEN_HEIGHT - SCREEN_HEIGHT/3));
    this->setPosition(SCREEN_WIDTH/6, SCREEN_HEIGHT/4);
    this->setFillColor(sf::Color(192, 192, 192, 255));
    this->setOutlineThickness(10);
    this->setOutlineColor(sf::Color::Black);

    _title_background.setSize(sf::Vector2f(this->getSize().x
                                           , this->getSize().y/10));
    _title_background.setPosition(this->getPosition());
    _title_background.setFillColor(sf::Color(128, 128, 128, 255));


    int row_size = (this->getSize().y //taille d'une ligne
                    - (_title_background.getPosition().y
                       + _title_background.getSize().y
                       - this->getPosition().y))/5;

    _delimiters = vector<sf::RectangleShape>(6);
    for(unsigned int i=0 ; i<5 ; i++)
    {
        _delimiters.push_back(sf::RectangleShape()); //délimiteurs horizontaux
        _delimiters.at(i).setSize(sf::Vector2f(this->getSize().x
                                                ,5));
        _delimiters.at(i).setPosition(this->getPosition().x
                                       ,this->getPosition().y
                                       + _title_background.getSize().y
                                       +(row_size*i));
        _delimiters.at(i).setFillColor(sf::Color::Black);
    }
    _delimiters.push_back(sf::RectangleShape()); //delimiteur vertical
    _delimiters.at(5).setSize(sf::Vector2f(5
                                            ,this->getSize().y));
    _delimiters.at(5).setPosition(this->getPosition().x + this->getSize().x/2
                                   ,this->getPosition().y);
    _delimiters.at(5).setFillColor(sf::Color::Black);


    _font.loadFromFile(POLICE);

    _columns_titles = pair<sf::Text, sf::Text>();
    _columns_titles.first.setString("PSEUDO");
    _columns_titles.first.setFont(_font);
    _columns_titles.first.setOrigin(_columns_titles.first.getLocalBounds().width/2
                                    ,_columns_titles.first.getLocalBounds().height/2);
    _columns_titles.first.setPosition(this->getPosition().x + this->getSize().x/4
                                      ,_title_background.getPosition().y + 15);

    _columns_titles.second.setString("SCORE");
    _columns_titles.second.setFont(_font);
    _columns_titles.second.setOrigin(_columns_titles.second.getLocalBounds().width/2
                                     ,_columns_titles.second.getLocalBounds().height/2);
    _columns_titles.second.setPosition(this->getPosition().x + (this->getSize().x - this->getSize().x/4)
                                       ,_title_background.getPosition().y + 15);

    _pseudonyms = vector<sf::Text>();
    _pseudonyms.reserve(5);
    _scores = vector<sf::Text>();
    _pseudonyms.reserve(5);
    for(unsigned int i=0 ; i<5 ; i++)
    {
        _pseudonyms.push_back(sf::Text());
        _pseudonyms.at(i).setString("LE PSEUDO");
        _pseudonyms.at(i).setColor(sf::Color::Black);
        _pseudonyms.at(i).setCharacterSize(40);
        _pseudonyms.at(i).setFont(_font);
        _pseudonyms.at(i).setPosition(this->getPosition().x + this->getSize().x/20
                                       ,this->getPosition().y
                                       + _title_background.getSize().y
                                       +(row_size*i) + row_size/4);
        _scores.push_back(sf::Text());
        _scores.at(i).setString("LE SCORE");
        _scores.at(i).setColor(sf::Color::Black);
        _scores.at(i).setCharacterSize(40);
        _scores.at(i).setFont(_font);
        _scores.at(i).setPosition(this->getPosition().x + this->getSize().x/2 + this->getSize().x/20
                                   ,this->getPosition().y
                                   + _title_background.getSize().y
                                   +(row_size*i) + row_size/4);
    }

    _clear_button.initialise(GREENCUBE, GREENCUBE, "REINITIALISER"
                             , POLICE, sf::Color::Black
                             , SCREEN_WIDTH-SCREEN_WIDTH/9, SCREEN_HEIGHT-SCREEN_HEIGHT/8);
}

sf::FloatRect HighscoresGrid::get_button_bounds() const
{
    return _clear_button.get_bounds();
}

sf::Vector2f HighscoresGrid::get_button_pos() const
{
    return _clear_button.getPos();
}


void HighscoresGrid::synchronise(vector<pair<string, long>> *highscores)
{
    for(unsigned int it=0 ; it<5 ; it++)
        _pseudonyms.at(it).setString(highscores->at(it).first);

    for(unsigned int it=0 ; it<5 ; it++)
        _scores.at(it).setString(to_string(highscores->at(it).second));
}

void HighscoresGrid::draw(sf::RenderWindow *w)
{
    w->draw(*this);
    w->draw(_title_background);
    for(auto d : _delimiters)
    {
        w->draw(d);
    }
    w->draw(_columns_titles.first);
    w->draw(_columns_titles.second);
    for(auto p : _pseudonyms)
    {
        w->draw(p);
    }
    for(auto s : _scores)
    {
        w->draw(s);
    }

    _clear_button.draw(w);
}

void HighscoresGrid::reset()
{
    for(unsigned int it=0 ; it<5 ; it++)
        _pseudonyms.at(it).setString("NOONE");

    for(unsigned int it=0 ; it<5 ; it++)
        _scores.at(it).setString(to_string(0));
}

