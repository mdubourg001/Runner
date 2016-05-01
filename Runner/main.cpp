#include "View.h"
#include "Model.h"
#include "main.h"
#include "Shop_Model.h"
#include "Shop_View.h"

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
            break;
        case settings:
            view.drawSettings();
            break;
        }
    }

//    Shop_Model shop_model(SCREEN_WIDTH, SCREEN_HEIGHT);
//    Shop_View shop_view(SCREEN_WIDTH, SCREEN_HEIGHT);


//    while(shop_view.treatEvents())
//    {
//        shop_model.nextStep();
//        shop_view.draw();
//        shop_view.synchronise();
//    }

    return EXIT_SUCCESS;
}
