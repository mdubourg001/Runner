#ifndef _MENU_MODEL_
#define _MENU_MODEL_
#include "main.h"

class Menu_Model {
private:
    int _w, _h;

public:

    Menu_Model(int w, int h);
    ~Menu_Model();

    void nextStep();
};
#endif
