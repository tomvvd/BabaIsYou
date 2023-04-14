#ifndef ENTITY_H
#define ENTITY_H

#include "EntityNature.h"
#include "EntityType.h"

class Entity {
    EntityNature nature_;
    EntityType type_;

public:
    inline Entity(EntityNature nature, EntityType type);
    inline EntityNature getNature() const;
    inline EntityType getType() const;
};

Entity::Entity(EntityNature nature, EntityType type) : nature_{nature}, type_{type} {}

EntityNature Entity::getNature() const{
    return this->nature_;
}

EntityType Entity::getType() const{
    return this->type_;
}

#endif // ENTITY_H
