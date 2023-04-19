#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "Game.h"
#include "View.h"

class Controller{
    Game & game;
    View & view;

    public:
    inline Controller(Game & game, View & view);
    inline void start();
};

Controller::Controller(Game & game, View & view) : game{game}, view{view} {}

void Controller::start(){
    view.showTitle();
    view.showInstructions();
    bool exit{false};
    while(!exit){
        view.showBoard();
        view.askDirection();
        string input;
        cin >> input;
        if(input=="l"){
            game.move(Direction::LEFT);
        }
        else if(input=="r"){
            game.move(Direction::RIGHT);
        }
        else if(input=="u"){
            game.move(Direction::UP);
        }
        else if(input=="d"){
            game.move(Direction::DOWN);
        }
        else{
            exit=true;
        }
    }
}

#endif // CONTROLLER_H
