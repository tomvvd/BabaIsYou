#ifndef BOARD_H
#define BOARD_H

#include <vector>
#include "Entity.h"
#include "Position.h"

using namespace std;

class Board{
    int height_;
    int width_;
    vector<vector<vector<Entity>>> entities_;

public:
    Board(int height, int width);
    int getHeight() const;
    int getWidth() const;
    vector<Entity> getEntities(Position pos);
    void addEntity(Position pos, Entity entity);
    void dropEntity(Position pos, Entity entity);
};

#endif // BOARD_H
