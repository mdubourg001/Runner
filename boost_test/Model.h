#ifndef _MODEL_
#define _MODEL_
#include "main.h"
#include "Player.h"
#include "AnimatedSprite.h"
#include "Coin.h"
#include "Counter.h"
#include "Diamond.h"
#include "Bonus.h"
#include "Obstacle.h"

enum BonusType //énumération définissant le type d'un bonus
{
    no,
    magnet, //attire les pièces vers le joueur
    randombonus, //bonus random parmis tout ces autres
    shield, //octroie un bouclier au joueur
    health, //rend des pv au joueur
    star, //insensible aux obstacles pendant un certain temps
    feather, //permet de voler et de flotter en l'air
    hourglass, //ralentit le jeu
    redcoin //octroie 100 pièces
};

class Model
{
protected:
    int _w, _h;
    Player _player; //la balle
    std::vector<Coin*> _coins; //vecteur des pièces couramment dans les limites de l'écran
    std::vector<Diamond*> _diamonds; //vecteur des diamants couramment dans les limites de l'écran
    std::vector<Bonus*> _bonus; //vecteur des bonus couramment dans les limites de l'écran
    std::vector<Obstacle*> _obstacles; //vecteur des obstacles couramment dans les limites de l'écran

    Counter _coin_counter; //compteur de pièces ramassées
    Counter _score_counter; //score obtenu lors de la partie courante
    Counter _diamond_counter; //compteur de diamants ramassés
    int _framecpt; //compteur de frame
    bool _canpop; //indique si un animated sprite peut apparaitre (afin d'éviter l'empilement)
    bool _magnetpicked; //indique si le bonus magnet est ramassé
    int _magnetcpt;

    BonusType bt; //voir ci-dessus

    sf::RectangleShape _healthRect; //barre de vie courante
    sf::RectangleShape _backhealthRect; //background de la barre de vie
    sf::RectangleShape _shieldRect; //vie donnée par le bouclier
    sf::Font _font;
    sf::Text _healthText;

public:
    Model(int w, int h);
    ~Model();

    void nextStep();
    Player* getPlayer();
    std::vector<Coin *> *Coins();
    std::vector<Diamond *> *Diamonds();
    std::vector<Bonus *> *Awards();
    std::vector<Obstacle*>* Obstacles();

    void getPlayerPosition(int &x, int &y);
    void setPlayerDirection(direction d);
    void movePlayer();
    void addCoin(); //ajoute une pièce au vecteur de pièces
    void addDiamond();
    void addBonus();
    void addObstacle();
    void drawInterface(sf::RenderWindow *w); //dessine les élements relatifs à la vie et les compteurs
};
#endif
