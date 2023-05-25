#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "../game/Game.h"
#include "View.h"

class Controller{
    Game & game;
    View & view;

    public:
    Controller(Game & game, View & view);
    void start();
};

#endif // CONTROLLER_H
