#ifndef VIEW_H
#define VIEW_H

#include "Game.h"
#include <iomanip>
#include <iostream>
#include <sstream>

class View{
    Game & game;
public:
    inline View(Game & game);
    inline void showBoard();
    inline void showTitle();
    inline void showInstructions();
    inline void askDirection();
};

View::View(Game & game) : game{game} {}

void View::showBoard(){
    for (int i = 0; i < game.getBoardWidth()*6; i++) {
        std::cout << "-";
    }
    cout << endl;
    for (int i = 0; i < game.getBoardHeight(); ++i) {
        cout << "|";
        for (int j = 0; j < game.getBoardWidth(); ++j) {
            Position pos{i,j};
            vector<Entity> entities{game.getBoardEntities(pos)};
            stringstream ss;
            for (const Entity & ent : entities) {
                ss << ent.to_string();
            }
            cout << setw(5) <<ss.str();
            cout << "|";
        }
        cout << endl;
        for (int i = 0; i < game.getBoardWidth()*6; i++) {
            std::cout << "-";
        }
        cout << endl;
    }
}

void View::showTitle(){
    cout << "-------------------------------------------" << endl;
    cout << "Welcome to the BabaIsYou game !!!" << endl;
    cout << "-------------------------------------------" << endl;
}

void View::showInstructions(){
    cout << "To move the player, enter these commands :" << endl;
    cout << "RIGHT : r" << endl;
    cout << "LEFT : l" << endl;
    cout << "UP : u" << endl;
    cout << "DOWN : d" << endl;
    cout << endl;
    cout << "To exit the game : exit" << endl;
    cout << "-------------------------------------------" << endl;
}

void View::askDirection(){
    cout << "Where do you want to go ? " << endl;
}


#endif // VIEW_H
