#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE

#include <boost/test/unit_test.hpp>
#include <../Runner/Player.h>
#include <iostream>

//===========TEST DU MOUVEMENT DE LA BALLE SELON L'AXE X ==========//
//=================================================================//
//      Ces tests se charge tout d'abord de vérifier que le        //
//    constructeur initialise bien les attributs de la balle.      //
//    On teste ensuite que la méthode move() se charge bien de     //
//          modifier la position de la balle comme voulu.          //
//=================================================================//
//=================================================================//

BOOST_AUTO_TEST_CASE(moveball)
{
    Player player(150, 450, 20, 20, 5, 0);
    BOOST_CHECK(player.getPosx() == 150);
    BOOST_CHECK(player.getWidth() == 20);
    BOOST_CHECK(player.getHeight() == 20);
    BOOST_CHECK(player.getMvtx() == 5);
    BOOST_CHECK(player.getMvty() == 0);

    player.move();
    BOOST_CHECK(player.getPosx() == 155);
    player.setMvtx(-5);
    player.setMvty(-10);
    player.move();
    BOOST_CHECK(player.getPosx() == 150);
    BOOST_CHECK(player.getPosy() == 440);
}

//==================TEST DE LA FONCTION DE SAUT ===================//
//=================================================================//
//    Ici, on crée la variable i qui représentera la valeur du     //
//   mouvement y voulue à chaque tour de boucle (pendant le saut). //
//    La variable to_add représentera la valeur ajoutée/soustraite //
//      à la valeur de la position y de la balle. Cette variable   //
//   sera donc modifiée au fur et à mesure du saut. On teste donc  //
//      ici la bonne hauteur du saut ainsi que la valeur de mvty.  //
//=================================================================//
//=================================================================//

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

    BOOST_CHECK(player.getMvty() == 0);
}



