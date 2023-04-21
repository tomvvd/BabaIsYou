#ifndef POSITION_H
#define POSITION_H

#include "Direction.h"

class Position {

private:
    int row_;
    int column_;

public:
    Position(int row, int column);
    int getRow() const;
    int getColumn() const;
    Position next(Direction dir);
};

#endif // POSITION_H
