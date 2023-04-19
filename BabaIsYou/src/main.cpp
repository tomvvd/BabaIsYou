#include <iostream>
#include "Controller.h"
#include "View.h"
#include "Game.h"

using namespace std;

int main()
{
    Game game {};
    View view{game};
    Controller controller{game,view};
    controller.start();
}
