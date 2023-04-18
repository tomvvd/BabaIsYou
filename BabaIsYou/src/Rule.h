#include "EntityNature.h"
#include "Position.h"
#include <vector>
#include <string>
#include <sstream>

#ifndef RULE_H
#define RULE_H

using namespace std;

class Rule{
    private:
        EntityNature subject;
        EntityNature operation;
        EntityNature object;
    public:
        inline Rule(EntityNature subject, EntityNature operation, EntityNature object);
        inline EntityNature getSubject();
        inline EntityNature getOperation();
        inline EntityNature getObject();
        inline string to_string();
};

Rule::Rule(EntityNature subj, EntityNature oper, EntityNature obj):subject {subj}, operation{oper}, object {obj}{}

EntityNature Rule::getSubject(){
    return this->subject;
}
EntityNature Rule::getOperation(){
    return this->operation;
}
EntityNature Rule::getObject(){
    return this->object;
}



#endif // RULE_H
