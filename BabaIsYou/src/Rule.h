#include "EntityNature.h"
#include "Position.h"
#include <vector>

#ifndef RULE_H
#define RULE_H

using namespace std;

class Rule{
    private:
        vector<Position> positions;
        EntityNature subject;
        EntityNature operation;
        EntityNature object;
        int priority;
    public:
        inline Rule(EntityNature subject, EntityNature operation, EntityNature object);
        inline EntityNature getSubject();
        inline EntityNature getOperation();
        inline EntityNature getObject();
        inline int getPriority();
        inline vector<Position> getPositions();
};

Rule::Rule(EntityNature subj, EntityNature oper, EntityNature obj):subject {subj}, operation{oper}, object {obj}{};
EntityNature Rule::getSubject(){
    return this->subject;
}
EntityNature Rule::getOperation(){
    return this->operation;
}
EntityNature Rule::getObject(){
    return this->object;
}
int Rule::getPriority(){
    return this->priority;
}
vector<Position> Rule::getPositions(){
    return this->positions;
}


#endif // RULE_H
