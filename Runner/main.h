#ifndef MAIN_H
#define MAIN_H

#include <SFML/Graphics.hpp>
#include <chrono>

#define SCREEN_WIDTH 1366
#define SCREEN_HEIGHT 768

#define DETECTION_RADIUS 300
#define JUMP_INITIAL_SPEED 25
#define FRAMERATE_LIMIT 60

#define EASY_SPEED 5
#define MEDIUM_SPEED 7
#define HARD_SPEED 10

#define BACKGROUND_IMAGE_L  "res/city_1.png"
#define BACKGROUND_IMAGE_B  "res/city_2.png"
#define BACKGROUND_IMAGE_PREVIEW_L  "res/city1_preview.png"
#define BACKGROUND_IMAGE_PREVIEW_B  "res/city2_preview.png"
#define BACKGROUND_TWO_IMAGE_L  "res/city_3.png"
#define BACKGROUND_TWO_IMAGE_B  "res/city_4.png"
#define BACKGROUND_TWO_IMAGE_PREVIEW_L  "res/city3_preview.png"
#define BACKGROUND_TWO_IMAGE_PREVIEW_B  "res/city4_preview.png"

#define BALL_IMAGE  "res/ball.png"
#define BALL_STAR_IMAGE  "res/ball_v5.png"
#define BALL_TWO_IMAGE  "res/ball_v2.png"
#define BALL_THREE_IMAGE  "res/ball_v3.png"
#define BALL_FOUR_IMAGE  "res/ball_v4.png"
#define BALL_FIVE_IMAGE  "res/ball_v5.png"
#define BALL_SIX_IMAGE  "res/ball_v6.png"

#define BACKGROUND_INTRO_IMAGE  "res/backgroundIntro.png"
#define BACKGROUND_MENU_IMAGE  "res/backgroundMenu.png"
#define BACKGROUND_SETTINGS  "res/backgroundSettings.png"

#define POLICE "res/slapstick.ttf"
#define POLICEMENU "res/slapstick_shaded.ttf"

#define BOUTON_ROUGE  "res/bouton_rouge.png"
#define BOUTON_BLEU  "res/bouton_bleu.png"

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

#define FICHIER_SCORE  "res/scores.txt"
#define FICHIER_COIN  "res/coins.txt"
#define FICHIER_DIAMOND  "res/diamonds.txt"


enum direction
{
    up,
    down,
    l,
    r,
    none
};

#endif // MAIN_H
