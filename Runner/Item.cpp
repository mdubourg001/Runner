#include "Item.h"

Item::Item()
{
    _font.loadFromFile(POLICE);
    _name.setFont(_font);
    _name.setColor(sf::Color::Black);
    _selected = false;
}

sf::Text Item::getName()
{
    return _name;
}

void Item::setName(std::string texte)
{
    _name.setString(texte);
}

void Item::setSelected(bool s)
{
    _selected = s;
}

bool Item::isSelected()
{
    return _selected;
}

void Item::drawText(sf::RenderWindow *w)
{
    _name.setPosition(sf::Vector2f(getPosition().x + 20, getPosition().y + 10));
    w->draw(_name);
}
