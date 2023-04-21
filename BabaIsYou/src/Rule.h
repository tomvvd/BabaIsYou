#include "EntityNature.h"
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
        Rule(EntityNature subject, EntityNature operation, EntityNature object);
        EntityNature getSubject();
        EntityNature getOperation();
        EntityNature getObject();
};



#endif // RULE_H
