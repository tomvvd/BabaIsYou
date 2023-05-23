#include <iostream>
#include "Controller.h"
#include "View.h"
#include "Game.h"

#include <QApplication>
#include "mainwindow.h"

using namespace std;

int main(int argc, char * argv[])
{
    /*Game game {};
    View view{game};
    game.registerObserver(&view);
    Controller controller{game,view};
    controller.start();*/

    QApplication application(argc,argv);
    MainWindow myWindow;
    myWindow.show();
    return application.exec();
}
