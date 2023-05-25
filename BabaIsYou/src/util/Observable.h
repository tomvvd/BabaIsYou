#ifndef OBSERVABLE_H
#define OBSERVABLE_H


#include <set>

class Observer;

class Observable
{
public:
    Observable();
    virtual void registerObserver(Observer * observer) final;
    virtual void unregisterObserver(Observer * observer) final;
    void notifyObservers() const;

private:
    std::set<Observer *> _observers;
};


#endif // OBSERVABLE_H
