#ifndef ITEM_H
#define ITEM_H
#include "View.h"
#include "main.h"
#include "Preview.h"


class Item : public sf::RectangleShape
{
protected:
    sf::Text _name;
    sf::Font _font;
    bool _selected;

    Preview *_preview;

public:
    Item();
    sf::Text getName();
    void setName(std::string texte);
    bool isSelected();
    void setSelected(bool s);
    void drawText(sf::RenderWindow *w);
    void drawPreview(sf::RenderWindow *w);

};

#endif // ITEM_H
