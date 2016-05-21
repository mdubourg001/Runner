#include "utils.h"

float distance(sf::Vector2f first, sf::Vector2f second)
    //retourne la distance entre 2 points de l'écran
{
    auto diff = first - second;
    return sqrt((diff.x * diff.x) + (diff.y * diff.y));
}
