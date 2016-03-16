#ifndef _INTRO_MODEL_
#define _INTRO_MODEL_
#include "main.h"

class Intro_Model {
private:
    int _w, _h;

public:

    Intro_Model(int w, int h);
    ~Intro_Model();

    void nextStep();
};
#endif
