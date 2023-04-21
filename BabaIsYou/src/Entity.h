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
    Entity(EntityNature nature, EntityType type);
    EntityNature getNature() const;
    EntityType getType() const;
    void setNature(EntityNature e);
    string to_string() const;
};

#endif // ENTITY_H
