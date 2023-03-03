#ifndef POSITION_H
#define POSITION_H

#include "Direction.h"

class Position {

private:
    int row;
    int column;

public:
    inline Position(int row, int column);
    inline int getRow() const;
    inline int getColumn() const;
    inline Position next(Direction dir);
};

Position::Position(int row, int column) : row{row} , column{column} {}

int Position::getRow() const{
    return this->row;
}

int Position::getColumn() const{
    return this->column;
}

Position Position::next(Direction dir){
    if(Direction::DOWN == dir){
        return Position{this->row+1,this->column};
    }
    else if(Direction::UP == dir){
        return Position{this->row-1,this->column};
    }
    else if(Direction::LEFT == dir){
        return Position{this->row,this->column-1};
    }
    else{
        return Position{this->row,this->column+1};
    }
}

#endif // POSITION_H
