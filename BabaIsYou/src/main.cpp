#include <iostream>
#include "console/Controller.h"
#include "gui/mwbaba.h"
#include <QApplication>


using namespace std;

int main(int argc, char * argv[])
{
    //Partie console
    /*Game game {};
    View view{game};
    game.registerObserver(&view);
    Controller controller{game,view};
    controller.start();*/

    //Partie interface graphique
    QApplication application(argc,argv);

    Game game {};
    MWBaba window{game};
    window.show();
    return application.exec();
}
