#include "Rule.h"

Rule::Rule(EntityNature subj, EntityNature oper, EntityNature obj):subject {subj}, operation{oper}, object {obj}{}

EntityNature Rule::getSubject() const {
    return this->subject;
}
EntityNature Rule::getOperation() const{
    return this->operation;
}
EntityNature Rule::getObject() const{
    return this->object;
}
