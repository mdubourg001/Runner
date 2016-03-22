#ifndef _SHOP_MODEL_
#define _SHOP_MODEL_
#include "main.h"

class Shop_Model {
private:
    int _w, _h;

public:

    Shop_Model(int w, int h);
    ~Shop_Model();

    void nextStep();
};
#endif
