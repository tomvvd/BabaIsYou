#include "Observer.h"

#ifndef OBSERVABLE_H
#define OBSERVABLE_H

class Observable{
    public:
        inline virtual void registerObserver(Observer obv);
        inline virtual void removeObserver(Observer obv);
        inline virtual void notifyObservers();
        virtual ~Observable() = default;
};

#endif // OBSERVABLE_H
