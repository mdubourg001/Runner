#ifndef MAIN_H
#define MAIN_H

#include <SFML/Graphics.hpp>
#include "Timer.h"

const int SCREEN_WIDTH = 1366;
const int SCREEN_HEIGHT = 768;

const int JUMP_HEIGHT = 25;

const std::string BACKGROUND_IMAGE = "res/city.png";
const std::string BALL_IMAGE = "res/ball.png";
const std::string BACKGROUND_INTRO_IMAGE = "res/intro.png";
const std::string POLICE = "res/Antique_Olive.ttf";
const std::string BACKGROUND_MENU_IMAGE = "res/background.png";

enum direction
{
    up,
    down,
    l,
    r,
    none
};

enum gamestates
{
    intro,
    menu,
    game
};

#endif // MAIN_H
