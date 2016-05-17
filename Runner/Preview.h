#ifndef PREVIEW_H
#define PREVIEW_H
#include "main.h"
#include "SlidingBackground.h"
#include "Player.h"

class Preview
{
private:
    SlidingBackground *_background;
    sf::Sprite _playerSprite;
    sf::Texture _playerTexture;

public:
    Preview();

    void setBallTexture(std::string B);
    void setBackgroundTexture(const std::string BackBig, const std::string BackLittle);

    void draw(sf::RenderWindow *w);
    void move();
    void reset();
};

#endif // PREVIEW_H
