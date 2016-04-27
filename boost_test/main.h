#ifndef MAIN_H
#define MAIN_H

#include <SFML/Graphics.hpp>

const int SCREEN_WIDTH = 1366; //largeur de l'écran
const int SCREEN_HEIGHT = 768; //hauteur de l'écran

const int JUMP_INITIAL_SPEED = 25; //hauteur du saut de la balle
const int FRAMERATE_LIMIT = 60; //limite de fps du programme

const std::string BACKGROUND_IMAGE_L = "res/city_1.png";
const std::string BACKGROUND_IMAGE_B = "res/city2.png";
const std::string BACKGROUND_IMAGE_PREVIEW_L = "res/city_preview.png";
const std::string BACKGROUND_IMAGE_PREVIEW_R = "res/city2_preview.png";
const std::string BALL_IMAGE = "res/ball.png"; //sprite de la balle
const std::string BACKGROUND_INTRO_IMAGE = "res/backgroundIntro.png";
const std::string POLICE = "res/slapstick.ttf"; //police générale
const std::string BACKGROUND_MENU_IMAGE = "res/background.png";

enum gamestates //énumération gérant l'état courant du jeu
{
    intro,
    menu,
    game
};


#endif // MAIN_H
