#ifndef ITEM_H
#define ITEM_H
#include "main.h"


class Item : public sf::RectangleShape
{
protected:
    sf::Text _name;
    sf::Font _font;
    bool _selected;
    //View _preview;

public:
    Item();
    sf::Text getName();
    void setName(std::string texte);
    bool isSelected();
    void setSelected(bool s);
    void drawText(sf::RenderWindow *w);
};

#endif // ITEM_H
