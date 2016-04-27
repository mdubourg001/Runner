#ifndef COUNTER_H
#define COUNTER_H
#include "main.h"


class Counter
{
protected:
    int _value; //indique à quelle valeur se trouve le compteur
    sf::Sprite _sprite; //icone du compteur
    sf::Texture _texture; //texture de l'icone
    sf::Text _text; //valeur du compteur sous forme de texte
    sf::Font _font;

public:
    Counter();
    Counter(int value, int posx, int posy, int width, int height);
    Counter(int value, int posx, int posy); // constructeur pour les test unitaires
    int getValue() const;
    void setValue(int value);
    void setTexture(std::string filename);
    void initSprite(int w, int h, int posx, int posy);
    void increment(); //incrémente le compteur de 1
    void decrement(); //décremente le compteur de 1
    void hundredincrement(); //incrémente le compteur de 100
    void draw(sf::RenderWindow *w);
};

#endif // COUNTER_H
