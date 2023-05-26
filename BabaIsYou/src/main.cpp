#include <iostream>
#include "console/Controller.h"
#include "gui/mwbaba.h"
#include <QApplication>


using namespace std;

int main(int argc, char * argv[])
{
    //Console
    /*Game game {};
    View view{game};
    game.registerObserver(&view);
    Controller controller{game,view};
    controller.start();*/

    //GUI
    QApplication application(argc,argv);

    Game game {};
    MWBaba window{game};
    window.show();
    return application.exec();
}
