#ifndef MAIN_H
#define MAIN_H

#include <SFML/Graphics.hpp>
#include <chrono>

#define SCREEN_WIDTH 1366
#define SCREEN_HEIGHT 768

#define DETECTION_RADIUS 400
#define JUMP_INITIAL_SPEED 25
#define FRAMERATE_LIMIT 60

#define HOURGLASS_SPEED 3
#define EASY_SPEED 5
#define MEDIUM_SPEED 7
#define HARD_SPEED 10

#define BALL_WIDTH 50
#define BALL_LIFE 400
#define BALL_WIN_AND_LOOZ_LIFE 80

#define CUBE_WIDTH 50

#define SCALE_BUTTON 0.83

#define HEALTH_RECT_HEIGHT 50

#define POS_X_TOTAL_COIN SCREEN_WIDTH - 130
#define POS_X_TOTAL_DIAMOND SCREEN_WIDTH - 300
#define POS_Y_TOTAL SCREEN_HEIGHT - 70

#define POS_X_COIN_COUNTER SCREEN_WIDTH - 130
#define POS_X_SCORE_COUNTER SCREEN_WIDTH - 500
#define POS_X_DIAMOND_COUNTER SCREEN_WIDTH - 300
#define POS_Y_COUNTER SCREEN_HEIGHT - 70

#define POS_X_OBSTACLE SCREEN_WIDTH + 100
#define POS_Y_OBSTACLE_1 SCREEN_HEIGHT - SCREEN_HEIGHT/4 + 40
#define POS_Y_OBSTACLE_2 SCREEN_HEIGHT - SCREEN_HEIGHT/4
#define POS_Y_OBSTACLE_3 SCREEN_HEIGHT - SCREEN_HEIGHT/4 - 40
#define POS_Y_OBSTACLE_4 SCREEN_HEIGHT - SCREEN_HEIGHT/4 - 80

#define NBR_ITEM 14
#define NBR_BALL 6
#define NBR_BACK 3
#define NBR_SCORES 5
#define NBR_CUBES 5

#define POS_Y_BUTTON (SCREEN_HEIGHT/2)-100
#define POS_Y_BUTTON_HOVER (SCREEN_HEIGHT/2)-115
#define POS_BUTTON_SETTINGS (SCREEN_HEIGHT/4)-100
#define POS_BUTTON_SHOP (SCREEN_HEIGHT/4)+475
#define POS_TEXT_SHOP 10

#define POS_X_HEALTH_RECT 225
#define POS_Y_HEALTH_RECT 710
#define POS_X_SHIELD_RECT 625

#define THICKNESS 3
#define WIDTH_SPRITE 50

#define DIFFICULTY_EASY 0
#define DIFFICULTY_MEDIUM 1000
#define DIFFICULTY_HARD 1300

#define POS_X_PLAYER_PREVIEW (SCREEN_WIDTH/2 +SCREEN_HEIGHT/9)
#define POS_Y_PLAYER_PREVIEW (SCREEN_HEIGHT-SCREEN_HEIGHT/5)

#define POS_X_BUTTON_LEFT_POPUP SCREEN_WIDTH/2 - 125
#define POS_X_BUTTON_RIGHT_POPUP SCREEN_WIDTH/2 + 75
#define POS_Y_BUTTON_POPUP SCREEN_HEIGHT/2 + 20

#define BACKGROUND_IMAGE_L  "res/background/city_1.png"
#define BACKGROUND_IMAGE_B  "res/background/city_2.png"
#define BACKGROUND_IMAGE_PREVIEW_L  "res/preview/city1_preview.png"
#define BACKGROUND_IMAGE_PREVIEW_B  "res/preview/city2_preview.png"

#define BACKGROUND_TWO_IMAGE_L  "res/background/city_3.png"
#define BACKGROUND_TWO_IMAGE_B  "res/background/city_4.png"
#define BACKGROUND_TWO_IMAGE_PREVIEW_L  "res/preview/city3_preview.png"
#define BACKGROUND_TWO_IMAGE_PREVIEW_B  "res/preview/city4_preview.png"

#define BACKGROUND_THREE_IMAGE_L  "res/background/duck.png"
#define BACKGROUND_THREE_IMAGE_B  "res/background/backDuckHunt.png"
#define BACKGROUND_THREE_IMAGE_PREVIEW_L  "res/preview/duck_preview.png"
#define BACKGROUND_THREE_IMAGE_PREVIEW_B  "res/preview/backDuckHunt_preview.png"

#define BALL_IMAGE  "res/ball/ball.png"
#define BALL_STAR_IMAGE  "res/ball/ball_v5.png"
#define BALL_TWO_IMAGE  "res/ball/ball_v2.png"
#define BALL_THREE_IMAGE  "res/ball/ball_v3.png"
#define BALL_FOUR_IMAGE  "res/ball/ball_v4.png"
#define BALL_FIVE_IMAGE  "res/ball/ball_v5.png"
#define BALL_SIX_IMAGE  "res/ball/ball_v6.png"

#define BACKGROUND_INTRO_IMAGE  "res/background/backgroundIntro.png"
#define BACKGROUND_MENU_IMAGE  "res/background/backgroundMenu.png"
#define BACKGROUND_SETTINGS  "res/background/backgroundSettings.png"

#define POLICE "res/font/slapstick.ttf"
#define POLICEMENU "res/font/slapstick_shaded.ttf"

#define ONE_COIN "res/bonus/coin.png"
#define ONE_DIAMOND "res/bonus/diamond.png"
#define COIN "res/bonus/coinsprite.png"
#define DIAMOND "res/bonus/diamondsprite.png"
#define MAGNET "res/bonus/aimant.png"
#define RANDOMBONUS "res/bonus/aleatoire.png"
#define HOURGLASS "res/bonus/sablier.png"
#define HEART "res/bonus/heart.png"
#define SHIELD "res/bonus/bouclier.png"
#define STAR "res/bonus/etoile.png"
#define FEATHER "res/bonus/plume.png"
#define REDCOIN "res/bonus/redcoin.png"

#define BLUECUBE "res/cube/bluecube.png"
#define REDCUBE "res/cube/redcube.png"
#define GREENCUBE "res/cube/greencube.png"
#define PURPLECUBE "res/cube/purplecube.png"
#define YELLOWCUBE "res/cube/yellowcube.png"

#define BLUECUBE_B  "res/buttons/blue_big.png"
#define BLUECUBE_L  "res/buttons/blue_little.png"
#define REDCUBE_B  "res/buttons/red_big.png"
#define REDCUBE_L  "res/buttons/red_little.png"
#define GREENCUBE_B  "res/buttons/green_big.png"
#define GREENCUBE_L  "res/buttons/green_little.png"
#define PURPLECUBE_B  "res/buttons/purple_big.png"
#define PURPLECUBE_L  "res/buttons/purple_little.png"
#define YELLOWCUBE_B  "res/buttons/yellow_big.png"
#define YELLOWCUBE_L  "res/buttons/yellow_little.png"

#define FICHIER_SCORE  "res/fichier_texte/scores.txt"
#define FICHIER_COIN  "res/fichier_texte/coins.txt"
#define FICHIER_DIAMOND  "res/fichier_texte/diamonds.txt"
#define FICHIER_ENGLISH "res/fichier_texte/english.txt"
#define FICHIER_FRENCH "res/fichier_texte/french.txt"
#define FICHIER_LOCK_ITEM "res/fichier_texte/lock.txt"
#define FICHIER_CHOOSE "res/fichier_texte/choose.txt"

enum direction
{
    up,
    down,
    l,
    r,
    none
};

#endif // MAIN_H
