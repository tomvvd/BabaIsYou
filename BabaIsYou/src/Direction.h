#ifndef DIRECTION_H
#define DIRECTION_H

class Direction {
    private:
        enum Directions {DOWN,UP,RIGHT,LEFT};
        int dRow;
        int dColumn;
    public:
        inline Direction(Directions dir);
        inline int getDeltaRow();
        inline int getDeltaColumn();
};
Direction::Direction(Directions dir){
    switch(dir){
        case Directions::DOWN:
            this->dRow = 1;
            this->dColumn = 0;
            break;
        case Directions::UP:
            this->dRow = -1;
            this->dColumn = 0;
            break;
        case Directions::RIGHT:
            this->dRow = 0;
            this->dColumn = 1;
            break;
        case Directions::LEFT:
            this->dRow = 0;
            this->dColumn = -1;
            break;
    }
}
int Direction::getDeltaRow(){
    return this->dRow;
}
int Direction::getDeltaColumn(){
    return this->dColumn;
}


#endif // DIRECTION_H
