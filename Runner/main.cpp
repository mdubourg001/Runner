#include "View.h"
#include "Model.h"
#include "main.h"

int main()
{
    srand(time(NULL));

    Model model(SCREEN_WIDTH, SCREEN_HEIGHT);
    View view(SCREEN_WIDTH, SCREEN_HEIGHT);
    view.setModel(&model);

    while(view.treatEvents())
    {
        switch(view.getGs())
        {
        case game:
            model.nextStep();
            view.synchronise();
            view.draw();
            break;
        case intro:
            view.drawIntro();
            break;
        case menu:
            view.drawMenu();
            break;
        case shop:
            view.drawShop();
            view.synchroniseShop();
            break;
        case highscores:
            view.drawHighscores();
            break;
        case settings:
            view.drawSettings();
            break;
        }
    }

    return EXIT_SUCCESS;
}
