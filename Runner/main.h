#ifndef MAIN_H
#define MAIN_H

#include <SFML/Graphics.hpp>
#include "Timer.h"

const int SCREEN_WIDTH = 1366;
const int SCREEN_HEIGHT = 768;

const int JUMP_HEIGHT = 25;

enum direction
{
    up,
    down,
    l,
    r,
    none
};

#endif // MAIN_H
