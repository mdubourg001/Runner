#include "Item.h"

//===================CONSTRUCTEUR=====================

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

//====================================================
//==================ACCESSEURS========================

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


Preview *Item::getPreview()
{
    return _preview;
}

//=====================================================
//================AUTRES METHODES======================

void Item::drawText(sf::RenderWindow *w)
    //dessine le nom de l'item dans le shop
{
    _name.setPosition(sf::Vector2f(getPosition().x + 20, getPosition().y + 10));
    w->draw(_name);
}

void Item::reset()
    //remet la preview de cet item à 0
{
    _preview->reset();
}

void Item::drawPreview(sf::RenderWindow *w)
    //dessine la preview de l'item (ie un aperçu de l'item)
{
    _preview->draw(w);
    _preview->move();
}

void Item::initialiseBall(const std::string B, const std::string Name)
    //change la texture et le nom de la balle en fonction de l'item
{
    _preview->setBallTexture(B);
    this->setName(Name);
}

void Item::initialiseBackground(const std::string BackBig, const std::string BackLittle, const std::string Name)
    //initialise la preview
{
    _preview->setBackgroundTexture(BackBig, BackLittle);
    this->setName(Name);
}

//========================================================
