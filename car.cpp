#include "car.h"

#include <thread>

Car::Car(){

}
Car::Car(const Car &car) noexcept{
    _fillUps = car._fillUps;
}

void Car::Fill(Station *station) {
    bool filled = false;
    while(!filled) {
        for (int x = 0; x < 2; x++) {
            if (station->pumpMutexes[x].try_lock()) {
                std::this_thread::sleep_for(std::chrono::microseconds(30));
                _fillUps++;
                station->fills[x]++;
                filled = true;
                station->pumpMutexes[x].unlock();
                station->Requeue(this);
                station->NotifyQueue();
                break;
            }
        }
    }
}

int Car::FillUps() {
    return _fillUps;
}