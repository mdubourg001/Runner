#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE

#include <boost/test/unit_test.hpp>
#include <../Runner/Player.h>
#include <iostream>

BOOST_AUTO_TEST_CASE(moveball)
{
    Player player(150, 450, 20, 20, 5, 0);
    BOOST_CHECK(player.getPosx() == 150);
    player.move();
    BOOST_CHECK(player.getPosx() == 155);
    player.setMvtx(-5);
    player.move();
    BOOST_CHECK(player.getPosx() == 150);
}

BOOST_AUTO_TEST_CASE(jumpball)
{
    int i = -26; // itérateur vérifiant la valeur du mouvement y de la balle
    int to_add = 0;
    Player player(150, 450, 20, 20, 5, 0);
    BOOST_CHECK(player.getPosy() == 450);
    BOOST_CHECK(player.getMvty() == 0);
    player.setJumping(true);
    player.setMvty(-26); //le mouvement est à 0 avant le saut et il est modifié par une fonction appartenant à la classe model
    while(player.isJumping())
    {
        BOOST_CHECK(player.getMvty() == i);
        BOOST_CHECK(player.getPosy() == 450 + to_add);
        player.jump();
        player.move();
        i++;
        to_add += i; // calcul de la variation de la hauteur depuis le début du saut
    }
}

