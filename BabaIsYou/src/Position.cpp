#include "Position.h"

Position::Position(int row, int column) : row_{row} , column_{column} {}

int Position::getRow() const{
    return this->row_;
}

int Position::getColumn() const{
    return this->column_;
}

Position Position::next(Direction dir){
    if(Direction::DOWN == dir){
        return Position{this->row_+1,this->column_};
    }
    else if(Direction::UP == dir){
        return Position{this->row_-1,this->column_};
    }
    else if(Direction::LEFT == dir){
        return Position{this->row_,this->column_-1};
    }
    else{
        return Position{this->row_,this->column_+1};
    }
}
