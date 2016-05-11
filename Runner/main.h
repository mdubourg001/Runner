#ifndef MAIN_H
#define MAIN_H

#include <SFML/Graphics.hpp>
#include <chrono>

#define SCREEN_WIDTH 1366
#define SCREEN_HEIGHT 768

#define JUMP_INITIAL_SPEED 25
#define FRAMERATE_LIMIT 60

#define EASY_SPEED 5
#define MEDIUM_SPEED 7
#define HARD_SPEED 10

const std::string BACKGROUND_IMAGE_L = "res/city_1.png";
const std::string BACKGROUND_IMAGE_B = "res/city_2.png";
const std::string BACKGROUND_IMAGE_PREVIEW_L = "res/city1_preview.png";
const std::string BACKGROUND_IMAGE_PREVIEW_B = "res/city2_preview.png";
const std::string BACKGROUND_TWO_IMAGE_L = "res/city_3.png";
const std::string BACKGROUND_TWO_IMAGE_B = "res/city_4.png";
const std::string BACKGROUND_TWO_IMAGE_PREVIEW_L = "res/city3_preview.png";
const std::string BACKGROUND_TWO_IMAGE_PREVIEW_B = "res/city4_preview.png";

const std::string BALL_IMAGE = "res/ball.png";
const std::string BALL_TWO_IMAGE = "res/ball_v2.png";
const std::string BALL_THREE_IMAGE = "res/ball_v3.png";
const std::string BALL_FOUR_IMAGE = "res/ball_v4.png";
const std::string BALL_FIVE_IMAGE = "res/ball_v5.png";
const std::string BALL_SIX_IMAGE = "res/ball_v6.png";


const std::string BACKGROUND_INTRO_IMAGE = "res/backgroundIntro.png";
const std::string BACKGROUND_MENU_IMAGE = "res/city.png";

const std::string POLICE = "res/slapstick.ttf";
const std::string POLICEMENU = "res/slice.ttf";

const std::string BOUTON_ROUGE = "res/bouton_rouge.png";
const std::string BOUTON_BLEU = "res/bouton_bleu.png";

const std::string BLUECUBE_B = "res/buttons/blue_big.png";
const std::string BLUECUBE_L = "res/buttons/blue_little.png";
const std::string REDCUBE_B = "res/buttons/red_big.png";
const std::string REDCUBE_L = "res/buttons/red_litlle.png";
const std::string GREENCUBE_B = "res/buttons/green_big.png";
const std::string GREENCUBE_L = "res/buttons/green_little.png";
const std::string PURPLECUBE_B = "res/buttons/purple_big.png";
const std::string PURPLECUBE_L = "res/buttons/purple_little.png";
const std::string YELLOWCUBE_B = "res/buttons/yellow_big.png";
const std::string YELLOWCUBE_L = "res/buttons/yellow_little.png";

const std::string FICHIER_SCORE = "res/scores.txt";
const std::string FICHIER_COIN = "res/coins.txt";
const std::string FICHIER_DIAMOND = "res/diamonds.txt";


enum direction
{
    up,
    down,
    l,
    r,
    none
};



#endif // MAIN_H
