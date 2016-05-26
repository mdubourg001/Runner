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
    bool _lock;
    bool _loaded;
    int _value;
    string _type;

    Preview *_preview;

    Counter _cost;

public:
    Item();
    ~Item();

    sf::Text getName() const;
    void setName(std::string texte);
    bool isSelected() const;
    void setSelected(bool s);
    bool isChoose() const;
    void setChoose(bool c);
    bool isLock() const;
    void setLock(bool l);
    bool getLoaded() const;
    void setLoaded(bool loaded);
    Preview *getPreview() const;
    int getValue() const;
    string getType() const;


    void drawText(sf::RenderWindow *w);
    void drawPreview(sf::RenderWindow *w);
    void initialiseBall(const std::string B, const std::string Name, int value, string type);
    void initialiseBackground(const std::string BackBig, const std::string BackLittle, const std::string Name, int value, string type);
    void reset();
    void LockOrNot(int l);
    void unLock(int l);
    void drawCost(sf::RenderWindow *w);

};

#endif // ITEM_H
