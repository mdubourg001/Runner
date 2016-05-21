#include "Item.h"

//===================CONSTRUCTEUR=====================

Item::Item()
{
    _font.loadFromFile(POLICE);
    _name.setFont(_font);
    _name.setColor(sf::Color::Black);
    _selected = false;
    _choose = false;
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

void Item::setChoose(bool c)
{
    _choose = c;
}

bool Item::isChoose()
{
    return _choose;
}

Preview *Item::getPreview()
{
    return _preview;
}

//=====================================================
//================AUTRES METHODES======================

/*!
 * \brief Item::drawText
 * \param w
 * dessine le nom de l'item dans le shop
 */
void Item::drawText(sf::RenderWindow *w)
{
    _name.setPosition(sf::Vector2f(getPosition().x + 20, getPosition().y + 10));
    w->draw(_name);
}


/*!
 * \brief Item::reset
 * remet la preview de cet item à 0
 */
void Item::reset()
{
    _preview->reset();
}


/*!
 * \brief Item::drawPreview
 * \param w
 * dessine la preview de l'item (ie un aperçu de l'item)
 */
void Item::drawPreview(sf::RenderWindow *w)
{
    _preview->draw(w);
    _preview->move();
}

/*!
 * \brief Item::initialiseBall
 * \param B
 * \param Name
 * change la texture et le nom de la balle en fonction de l'item
 */
void Item::initialiseBall(const std::string B, const std::string Name)
{
    _preview->setBallTexture(B);
    this->setName(Name);
}


/*!
 * \brief Item::initialiseBackground
 * \param BackBig
 * \param BackLittle
 * \param Name
 * initialise la preview
 */
void Item::initialiseBackground(const std::string BackBig, const std::string BackLittle, const std::string Name)
{
    _preview->setBackgroundTexture(BackBig, BackLittle);
    this->setName(Name);
}
