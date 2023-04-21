#include "Entity.h"

Entity::Entity(EntityNature nature, EntityType type) : nature_{nature}, type_{type} {}

EntityNature Entity::getNature() const{
    return this->nature_;
}

EntityType Entity::getType() const{
    return this->type_;
}

void Entity::setNature(EntityNature e){
    nature_ = e;
}

string Entity::to_string() const{
    string res;
    if(type_==EntityType::ELEMENT){
        if (nature_ == EntityNature::BABA) {
            res = "B";
        }
        else if (nature_ == EntityNature::FLAG) {
            res = "F";
        }
        else if (nature_ == EntityNature::GRASS) {
            res = "G";
        }
        else if (nature_ == EntityNature::METAL) {
            res = "M";
        }
        else if (nature_ == EntityNature::LIMIT) {
            res = "X";
        }
        else if (nature_ == EntityNature::ROCK) {
            res = "R";
        }
        else if (nature_ == EntityNature::WALL) {
            res = "W";
        }
        else if (nature_ == EntityNature::WATER) {
            res = "#";
        }
        else if (nature_ == EntityNature::LAVA) {
            res = "L";
        }

    }
    else {
        if (nature_ == EntityNature::BABA) {
            res = "BABA";
        }
        else if (nature_ == EntityNature::FLAG) {
            res = "FLAG";
        }
        else if (nature_ == EntityNature::GRASS) {
            res = "GRASS";
        }
        else if (nature_ == EntityNature::METAL) {
            res = "METAL";
        }
        else if (nature_ == EntityNature::ROCK) {
            res = "ROCK";
        }
        else if (nature_ == EntityNature::WALL) {
            res = "WALL";
        }
        else if (nature_ == EntityNature::WATER) {
            res = "WATER";
        }
        else if (nature_ == EntityNature::LAVA) {
            res = "LAVA";
        }
        else if (nature_ == EntityNature::IS) {
            res = "IS";
        }
        else if (nature_ == EntityNature::KILL) {
            res = "KILL";
        }
        else if (nature_ == EntityNature::PUSH) {
            res = "PUSH";
        }
        else if (nature_ == EntityNature::SINK) {
            res = "SINK";
        }
        else if (nature_ == EntityNature::STOP) {
            res = "STOP";
        }
        else if (nature_ == EntityNature::YOU) {
            res = "YOU";
        }
        else if (nature_ == EntityNature::WIN) {
            res = "WIN";
        }
    }
    return res;
}
