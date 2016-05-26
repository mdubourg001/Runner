#include "Preview.h"
#include "main.h"

Preview::Preview()
{
    _background = new SlidingBackground((SCREEN_WIDTH/6)-3,53,SCREEN_WIDTH-SCREEN_WIDTH/6,SCREEN_HEIGHT-56,1,5);
    _background->loadTextures(BACKGROUND_IMAGE_PREVIEW_B,BACKGROUND_IMAGE_PREVIEW_B,
                              BACKGROUND_IMAGE_PREVIEW_L,BACKGROUND_IMAGE_PREVIEW_L);

    _playerTexture.loadFromFile(BALL_IMAGE);
    _playerSprite.setTexture(_playerTexture);
    _playerSprite.setPosition(sf::Vector2f(POS_X_PLAYER_PREVIEW, POS_Y_PLAYER_PREVIEW));
    _playerSprite.setOrigin(sf::Vector2f(25, 25));
}

void Preview::setBallTexture(std::string B)
{ _playerTexture.loadFromFile(B); }

void Preview::setBackgroundTexture(const std::string BackBig, const std::string BackLittle)
{ _background->loadTextures(BackBig, BackBig, BackLittle, BackLittle); }

/*!
 * \brief Preview::draw
 * \param w
 * dessine la preview (backgound + balle)
 */
void Preview::draw(sf::RenderWindow *w)
{
    _background->draw(w);
    _playerSprite.rotate(10);
    w->draw(_playerSprite);
}

/*!
 * \brief Preview::move
 *  anime le background
 */
void Preview::move()
{
    _background->move();
}

/*!
 * \brief Preview::reset
 * remet la preview à 0
 */
void Preview::reset()
{
    _background->reset();
}
