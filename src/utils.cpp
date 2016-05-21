#include "utils.h"


/*!
 * \brief distance
 * \param first
 * \param second
 * \return la distance entre deux points de l'écran
 */
float distance(sf::Vector2f first, sf::Vector2f second)
{
    auto diff = first - second;
    return sqrt((diff.x * diff.x) + (diff.y * diff.y));
}
