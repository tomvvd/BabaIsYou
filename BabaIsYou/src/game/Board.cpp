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

const vector<Entity>& Board::getEntities(const Position & pos) const {
    return entities_.at(pos.getRow()).at(pos.getColumn());
}

void Board::addEntity(const Position & pos, const Entity& entity){
    entities_.at(pos.getRow()).at(pos.getColumn()).push_back(entity);
}

void Board::dropEntity(const Position & pos, const Entity& entity) {
    vector<Entity>& entities = entities_.at(pos.getRow()).at(pos.getColumn());
    for (auto it = entities.begin(); it != entities.end(); ++it) {
        if (it->getNature() == entity.getNature() && it->getType() == entity.getType()) {
            entities.erase(it);
            break;
        }
    }
}







