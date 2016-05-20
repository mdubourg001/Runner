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
    bool _choose;

    Preview *_preview;

public:
    Item();
    ~Item();

    sf::Text getName();
    void setName(std::string texte);
    bool isSelected();
    void setSelected(bool s);
    bool isChoose();
    void setChoose(bool c);
    Preview *getPreview();

    void drawText(sf::RenderWindow *w);
    void drawPreview(sf::RenderWindow *w);
    void initialiseBall(const std::string B, const std::string Name);
    void initialiseBackground(const std::string BackBig, const std::string BackLittle, const std::string Name);
    void reset();

};

#endif // ITEM_H
