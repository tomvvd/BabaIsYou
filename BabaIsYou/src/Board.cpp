#include "Board.h"

Board::Board(int height, int width) : height_{height}, width_{width}, entities_{} {
    entities_.resize(height);
    for (int i = 0; i < height; ++i) {
        entities_[i].resize(width);
    }
}

int Board::getHeight() const{
    return height_;
}

int Board::getWidth() const{
    return width_;
}

vector<Entity> Board::getEntities(Position pos){
    return entities_.at(pos.getRow())
            .at(pos.getColumn());
}

void Board::addEntity(Position pos, Entity entity){
    entities_.at(pos.getRow())
            .at(pos.getColumn())
            .push_back(entity);
}

void Board::dropEntity(Position pos, Entity entity){
    //si je fais ça , c'est parce que le vector n'est pas une référence comme en java, si on l'assigne , une copie est créée

    bool stop {false};
    for (int i = 0; i < entities_.at(pos.getRow()).at(pos.getColumn()).size() && !stop; ++i) {
        if(entities_.at(pos.getRow()).at(pos.getColumn()).at(i).getNature() == entity.getNature()
                && entities_.at(pos.getRow()).at(pos.getColumn()).at(i).getType() == entity.getType()){
            entities_.at(pos.getRow()).at(pos.getColumn()).erase(entities_.at(pos.getRow()).at(pos.getColumn()).begin() + i);
            --i;
            stop = true;
        }
    }
}
