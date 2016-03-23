#include "Preview.h"
#include "main.h"

Preview::Preview()
{
    _background = new SlidingBackground(SCREEN_WIDTH/4,SCREEN_HEIGHT/4,600,337,5);
    _background->loadTextures(BACKGROUND_IMAGE_PREVIEW_L,BACKGROUND_IMAGE_PREVIEW_R);

    _playerTexture.loadFromFile(BALL_IMAGE);
    _playerSprite.setTexture(_playerTexture);
    _playerSprite.setPosition(sf::Vector2f(SCREEN_WIDTH/2,SCREEN_HEIGHT/2));
    _playerSprite.setOrigin(sf::Vector2f(SCREEN_WIDTH/2,SCREEN_HEIGHT/2));
    //_playerSprite.setRotation(10);
}

void Preview::draw(sf::RenderWindow *w)
{
    _background->draw(w);
    w->draw(_playerSprite);
}
