#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE

#include <boost/test/unit_test.hpp>
#include <../Runner/Player.h>
#include <../Runner/Model.h>
#include <../Runner/Coin.h>
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


//==================TEST DE DEPLACEMENT DES PIECES/================//
//=====================DIAMANTS/OBSTACLES/BONUS====================//
//=================================================================//
//   Ici, on teste le bon fonctionnement de la méthode move de     //
//    la classe AnimatedSprite, classe dont héritent les pièces,   //
//   diamants, obstacles, bonus. Un constructeur ne traitant pas   //
//    les textures de ces objets à été mis en place pour faciliter //
//                         les tests.                              //
//=================================================================//
//=================================================================//

BOOST_AUTO_TEST_CASE(movesprite)
{
    AnimatedSprite sprite(10, SCREEN_WIDTH, 600, 50, 50); //on initialise la position du sprite en dehors de l'écran
    BOOST_CHECK(!(sprite.getPosition().x > 0 && sprite.getPosition().x < SCREEN_WIDTH));
    sprite.move(); //déplace l'objet de ms vers la gauche (soit 10 ici), l'objet est donc maintenant dans les limites de l'écran
    BOOST_CHECK((sprite.getPosition().x > 0 && sprite.getPosition().x < SCREEN_WIDTH));
    sprite.setPosition(0, 100);
    BOOST_CHECK((sprite.getPosition().x >= 0 && sprite.getPosition().x < SCREEN_WIDTH));
}


//=========TEST DE COLLISION ENTRE LA BALLE ET UNE PIECE===========//
//=================================================================//
//   Ici, on teste la collision entre la balle et une pièce. Les   //
//   collisions des pièces étant similaires à celles des bonus/    //
//  diamants/obstacles, on ne testera pas les collisions avec ces  //
//   derniers. Un constructeur ne traitant pas la texture des      //
//    pièces à été mit en place pour faciliter les tests. Une      //
//   fonction treatCollisions spéciale a été créee pour pouvoir    //
//    réaliser les tests sur un seul objet et non sur un vecteur.  //
//=================================================================//
//=================================================================//

BOOST_AUTO_TEST_CASE(collisions)
{
    Player player(300, 400, 50, 50, 20, 0); //on place la balle et la pièce de manière à ce qu'ils ne soient pas en collision

    Coin coin(0, 360, 400, 50, 50);
    player.treatCollisions(coin);
    BOOST_CHECK(!coin.isPicked());
    player.move(); //on déplace la balle (ici de 20px) vers la droite afin d'entrer en collision avec la pièce
    player.treatCollisions(coin); //on actualise la valeur du booléen _picked
    BOOST_CHECK(coin.isPicked());
}



