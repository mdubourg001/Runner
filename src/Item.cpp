#include "Item.h"

#include <fstream>
#include <sstream>
#include <iostream>

//===================CONSTRUCTEUR=====================




Item::Item()
    : _selected(false), _choose(false), _loaded(false), _value(0), _type("none")
{
    _font.loadFromFile(POLICE);
    _name.setFont(_font);
    _name.setColor(sf::Color::Black);
    _preview = new Preview();
}

Item::~Item()
{
    delete _preview;
}

//====================================================

//==================ACCESSEURS========================

sf::Text Item::getName() const
{ return _name; }

void Item::setName(std::string texte)
{ _name.setString(texte); }

bool Item::isSelected() const
{ return _selected; }

void Item::setSelected(bool s)
{ _selected = s; }

bool Item::isChoose() const
{ return _choose; }

void Item::setChoose(bool c)
{ _choose = c; }

bool Item::isLock() const
{ return _lock; }

void Item::setLock(bool l)
{ _lock = l; }

bool Item::getLoaded() const
{ return _loaded; }

void Item::setLoaded(bool loaded)
{ _loaded = loaded; }

Preview *Item::getPreview() const
{ return _preview; }

int Item::getValue() const
{ return _value; }

string Item::getType() const
{ return _type; }

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
void Item::initialiseBall(const std::string B, const std::string Name, int value, string type)
{
    _preview->setBallTexture(B);
    this->setName(Name);
    _loaded = true;
    _value = value;
    _type = type;
}

/*!
 * \brief Item::initialiseBackground
 * \param BackBig
 * \param BackLittle
 * \param Name
 * initialise la preview
 */
void Item::initialiseBackground(const std::string BackBig, const std::string BackLittle, const std::string Name, int value, string type)
{
    _preview->setBackgroundTexture(BackBig, BackLittle);
    this->setName(Name);
    _loaded = true;
    _value = value;
    _type = type;
}

/*!
 * \brief Item::reset
 * remet la preview de cet item à 0
 */
void Item::reset()
{
    _preview->reset();
}

void Item::LockOrNot(int l)
{
    ifstream readLock(FICHIER_LOCK_ITEM, ios::in);
    string line = "";
    if(readLock)
    {
        for(int j=-1; j<l;j++)
            getline(readLock, line);
        if(line == "unlock")
            _lock = false;
        else if(line == "lock")
            _lock = true;
        readLock.close();
    }
    else
    {
        cerr << "ouverture en lecture impossible";
        exit(EXIT_FAILURE);
    }
}

void Item::unLock(int l)
{
    ifstream readLock(FICHIER_LOCK_ITEM, ios::in);
    string line[NBR_ITEM];
    if(readLock)
    {
        for(unsigned int i=0; i<NBR_ITEM; i++)
        {
            getline(readLock,line[i]);
            line[i] += "\n";
        }
        readLock.close();
    }
    else
    {
        cerr << "ouverture en lecture impossible";
        exit(EXIT_FAILURE);
    }
    line[l] = "unlock\n";

    ofstream writeLock(FICHIER_LOCK_ITEM, ios::out);
    if(writeLock)
    {
        for(unsigned int i=0; i<NBR_ITEM; i++)
        {
            writeLock << line[i];
        }
        writeLock.close();
    }
    else
    {
        cerr << "ouverture en écriture imossible";
        exit(EXIT_FAILURE);
    }
}
