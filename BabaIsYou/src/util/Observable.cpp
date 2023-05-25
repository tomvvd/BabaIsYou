#include "Observable.h"
#include "Observer.h"

Observable::Observable()
{

}

void Observable::registerObserver(Observer * observer)
{
    _observers.insert(observer);
}

void Observable::unregisterObserver(Observer * observer)
{
    _observers.erase(observer);
}

void Observable::notifyObservers() const
{
    for (Observer * observer : _observers)
    {
        observer->update(this);
    }
}

