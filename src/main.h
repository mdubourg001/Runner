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
