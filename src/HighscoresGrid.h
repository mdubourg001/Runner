#ifndef HIGHSCORESGRID_H
#define HIGHSCORESGRID_H

#include <SFML/Graphics.hpp>
#include <iostream>

#include "main.h"
#include "Button.h"

using namespace std;

class HighscoresGrid : public sf::RectangleShape
{
protected:
    sf::Font _font;

    sf::RectangleShape _title_background;
    pair<sf::Text, sf::Text> _columns_titles;

    vector<sf::RectangleShape> _delimiters;
    vector<sf::Text> _pseudonyms;
    vector<sf::Text> _scores;

    Button _clear_button;

public:
    HighscoresGrid();
    ~HighscoresGrid() = default;

    sf::FloatRect get_button_bounds() const;
    sf::Vector2f get_button_pos() const;

    void synchronise(vector<pair<string, long> > *highscores);
    void draw(sf::RenderWindow *w);
    void reset();
};

#endif // HIGHSCORESGRID_H
