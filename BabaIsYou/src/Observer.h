#ifndef OBSERVER_H
#define OBSERVER_H

class Observer{
    public:
        inline virtual void update();
        ~Observer() = default;
}

#endif // OBSERVER_H
