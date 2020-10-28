#include "observer.h"

void Observable::add_observer(Observer *observer) {
    _observers.push_back(observer);
}

void Observable::notify_update() {
    int size = _observers.size();
    for (int i = 0; i < size; i++)
        _observers[i]->update();
}