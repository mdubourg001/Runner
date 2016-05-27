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
    bool _selected; // permet de savoir sur quel item nous somme positionner dans le shop
    bool _choose; // permet de choisir, ainsi jouer avec cet item
    bool _lock; // permet de savoir si il est débloquer ou non
    bool _loaded;
    int _value; // son prix
    string _type; // avec quelle monnaie doit on l'acheter (diamants ou pieces)

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
