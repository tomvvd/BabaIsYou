#include <iostream>
#include "Controller.h"
#include "View.h"
#include "Game.h"

using namespace std;

int main()
{
    Game game {};
    View view{game};
    game.registerObserver(&view);
    Controller controller{game,view};
    controller.start();
}
