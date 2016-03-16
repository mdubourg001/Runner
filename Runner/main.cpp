#include "View.h"
#include "Model.h"
#include "main.h"
#include "Intro_View.h"
#include "Intro_Model.h"
#include "Menu_Model.h"
#include "Menu_View.h"

int main()
{
    srand(time(NULL));

    /*Model model(SCREEN_WIDTH, SCREEN_HEIGHT);
    View view(SCREEN_WIDTH, SCREEN_HEIGHT);
    view.setModel(&model);

    while(view.treatEvents())
    {
        model.nextStep();
        view.draw();
    }*/

    Intro_Model intro_model(SCREEN_WIDTH, SCREEN_HEIGHT);
    Intro_View intro_view(SCREEN_WIDTH, SCREEN_HEIGHT);
    intro_view.setModel(&intro_model);

    while(intro_view.treatEvents())
    {
        intro_view.draw();
    }

    /*Menu_Model menu_model(SCREEN_WIDTH, SCREEN_HEIGHT);
    Menu_View menu_view(SCREEN_WIDTH, SCREEN_HEIGHT);
    menu_view.setModel(&menu_model);

    while(menu_view.treatEvents())
    {
        menu_model.nextStep();
        menu_view.draw();
    }*/


    return EXIT_SUCCESS;
}
