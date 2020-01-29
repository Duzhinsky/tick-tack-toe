#ifndef OBSERVER_H
#define OBSERVER_H

#include <vector>

class Observer {
    public:
        virtual void update() = 0;
}; // class Observer
 
class Observable {
    public:
        void add_observer(Observer *observer);
        void notify_update();

    private:
        std::vector<Observer*> _observers;
}; // class Observable

#endif