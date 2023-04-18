#ifndef VIEW_H
#define VIEW_H

#include "Board.h"
#include <iomanip>
#include <iostream>
#include <sstream>

class View{

public:
    static void showBoard(Board board){
        for (int i = 0; i < board.getWidth()*6; i++) {
            std::cout << "-";
        }
        cout << endl;
        for (int i = 0; i < board.getHeight(); ++i) {
            cout << "|";
            for (int j = 0; j < board.getWidth(); ++j) {
                Position pos{i,j};
                vector<Entity> entities{board.getEntities(pos)};
                stringstream ss;
                for (const Entity & ent : entities) {
                    ss << ent.to_string();
                }
                cout << setw(5) <<ss.str();
                cout << "|";
            }
            cout << endl;
            for (int i = 0; i < board.getWidth()*6; i++) {
                std::cout << "-";
            }
            cout << endl;
        }
    }
};

#endif // VIEW_H
