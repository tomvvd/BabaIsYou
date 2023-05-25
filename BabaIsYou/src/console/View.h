#ifndef VIEW_H
#define VIEW_H

#include "../game/Game.h"
#include "../util/Observer.h"
#include <iomanip>
#include <iostream>
#include <sstream>

class View : public Observer{
    Game & game;
public:
    View(Game & game);
    void showBoard();
    void showTitle();
    void showInstructions();
    void askDirection();
    void showLose();
    void showWin();
    void update(const Observable * subject) override;
};

#endif // VIEW_H
