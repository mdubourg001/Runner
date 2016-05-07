#ifndef MAIN_H
#define MAIN_H

#include <SFML/Graphics.hpp>
#include <chrono>

#define SCREEN_WIDTH 1366
#define SCREEN_HEIGHT 768

#define JUMP_INITIAL_SPEED 25
#define FRAMERATE_LIMIT 60

const std::string BACKGROUND_IMAGE_L = "res/city_1.png";
const std::string BACKGROUND_IMAGE_B = "res/city2.png";
const std::string BACKGROUND_IMAGE_PREVIEW_L = "res/city1_preview.png";
const std::string BACKGROUND_IMAGE_PREVIEW_B = "res/city2_preview.png";
const std::string BALL_IMAGE = "res/ball_v2.png";
const std::string BACKGROUND_INTRO_IMAGE = "res/backgroundIntro.png";
const std::string POLICE = "res/slapstick.ttf";
const std::string POLICEMENU = "res/slice.ttf";
const std::string BACKGROUND_MENU_IMAGE = "res/city.png";
const std::string BOUTON_ROUGE = "res/bouton_rouge.png";
const std::string BOUTON_BLEU = "res/bouton_bleu.png";
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
