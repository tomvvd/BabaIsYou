#ifndef LEVELLOADER_H
#define LEVELLOADER_H

#include "Board.h"
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

using namespace std;

class LevelLoader {
    static Entity stringToEntity(string input);
    static string entityToString(Entity entity);

public:
    static Board levelLoad(int nb);
    static void saveLevel(Board board, int currentLevel);
    static pair<Board, int> reloadLevel();
};

#endif // LEVELLOADER_H
