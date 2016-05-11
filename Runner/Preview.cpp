#include "Preview.h"
#include "main.h"

Preview::Preview()
{
    _background = new SlidingBackground((SCREEN_WIDTH/6)-3,53,SCREEN_WIDTH-SCREEN_WIDTH/6,SCREEN_HEIGHT-56,1,5);
    _background->loadTextures(BACKGROUND_IMAGE_PREVIEW_B,BACKGROUND_IMAGE_PREVIEW_B,
                              BACKGROUND_IMAGE_PREVIEW_L,BACKGROUND_IMAGE_PREVIEW_L);

    _playerTexture.loadFromFile(BALL_IMAGE);
    _playerSprite.setTexture(_playerTexture);
    _playerSprite.setPosition(sf::Vector2f(SCREEN_WIDTH/2 + SCREEN_WIDTH/9 ,SCREEN_HEIGHT-SCREEN_HEIGHT/5));
    _playerSprite.setOrigin(sf::Vector2f(25, 25));
}

void Preview::draw(sf::RenderWindow *w)
{
    _background->draw(w);
    _playerSprite.rotate(10);
    w->draw(_playerSprite);
}

void Preview::move()
{
    _background->move();
}

void Preview::reset()
{
    _background->reset();
}

void Preview::setBallTexture(std::string B)
{
    _playerTexture.loadFromFile(B);
}

void Preview::setBackgroundTexture(const std::string BackBig, const std::string BackLittle)
{
    _background->loadTextures(BackBig, BackBig, BackLittle, BackLittle);
}
