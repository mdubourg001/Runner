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
        model.nextStep();
        view.draw();
    }

    return EXIT_SUCCESS;
}
