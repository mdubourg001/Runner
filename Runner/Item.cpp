#include "Item.h"

Item::Item()
{
    _font.loadFromFile(POLICE);
    _name.setFont(_font);
    _name.setColor(sf::Color::Black);
    _selected = false;
    _preview = new Preview();
}

Item::~Item()
{
    delete _preview;
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

void Item::reset()
{
    _preview->reset();
}

void Item::drawPreview(sf::RenderWindow *w)
{
    _preview->draw(w);
    _preview->move();
}

Preview *Item::getPreview()
{
    return _preview;
}

void Item::initialiseBall(const std::string B, const std::string Name)
{
    _preview->setBallTexture(B);
    this->setName(Name);
}

void Item::initialiseBackground(const std::string BackBig, const std::string BackLittle, const std::string Name)
{
    _preview->setBackgroundTexture(BackBig, BackLittle);
    this->setName(Name);
}
