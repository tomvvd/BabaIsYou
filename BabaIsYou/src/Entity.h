#ifndef ENTITY_H
#define ENTITY_H

#include <string>
#include "EntityNature.h"
#include "EntityType.h"

using namespace std;

class Entity {
    EntityNature nature_;
    EntityType type_;

public:
    inline Entity(EntityNature nature, EntityType type);
    inline EntityNature getNature() const;
    inline EntityType getType() const;
    inline string to_string() const;
};

Entity::Entity(EntityNature nature, EntityType type) : nature_{nature}, type_{type} {}

EntityNature Entity::getNature() const{
    return this->nature_;
}

EntityType Entity::getType() const{
    return this->type_;
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
            return "W";
        }
        else if (nature_ == EntityNature::WATER) {
            res = "#";
        }
    }
    else {
        if (nature_ == EntityNature::BABA) {
            res = "tB";
        }
        else if (nature_ == EntityNature::FLAG) {
            res = "tF";
        }
        else if (nature_ == EntityNature::GRASS) {
            res = "tG";
        }
        else if (nature_ == EntityNature::METAL) {
            res = "tM";
        }
        else if (nature_ == EntityNature::ROCK) {
            res = "tR";
        }
        else if (nature_ == EntityNature::WALL) {
            res = "tW";
        }
        else if (nature_ == EntityNature::WATER) {
            res = "t#";
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

#endif // ENTITY_H
