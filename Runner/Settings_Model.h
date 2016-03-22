#ifndef _SETTINGS_MODEL_
#define _SETTINGS_MODEL_
#include "main.h"

class Settings_View;

class Settings_Model {
private:
    int _w, _h;



public:

    Settings_Model(int w, int h);
    ~Settings_Model();



    void nextStep();

};
#endif
