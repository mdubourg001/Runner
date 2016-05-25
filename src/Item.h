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

public:
    Item();
    ~Item();

    sf::Text getName();
    void setName(std::string texte);
    bool isSelected();
    void setSelected(bool s);
    bool isChoose();
    void setChoose(bool c);
    bool isLock();
    void setLock(bool l);
    bool getLoaded() const;
    void setLoaded(bool loaded);
    int getValue() const;
    string getType() const;

    Preview *getPreview();

    void drawText(sf::RenderWindow *w);
    void drawPreview(sf::RenderWindow *w);
    void initialiseBall(const std::string B, const std::string Name, int value, string type);
    void initialiseBackground(const std::string BackBig, const std::string BackLittle, const std::string Name, int value, string type);
    void initialiseValueAndType(int v, int t);
    void reset();
    void LockOrNot(int i);
    void unLock(int l);

};

#endif // ITEM_H
