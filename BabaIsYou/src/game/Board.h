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
    const vector<Entity> & getEntities(const Position &pos) const;
    void addEntity(const Position &pos, const Entity& entity);
    void dropEntity(const Position &pos, const Entity& entity);
};

#endif // BOARD_H
