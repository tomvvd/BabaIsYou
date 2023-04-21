#include "Rule.h"

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
