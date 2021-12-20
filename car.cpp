#include "car.h"

#include <thread>

/**
 * Constructor
 */
Car::Car(){

}
/**
 * Fills a Car
 * @param Station* pointer to the station that will fill the car
 */
void Car::Fill(Station *station) {
    bool filled = false;
    while(!filled) {
        for (int x = 0; x < 2; x++) {
            if (station->pumpMutexes[x].try_lock()) {
                std::this_thread::sleep_for(std::chrono::microseconds(30));
                _fillUps++;
                station->IncrementFills(x);
                filled = true;
                station->pumpMutexes[x].unlock();
                station->Requeue(this);
                station->NotifyQueue();
                break;
            }
        }
    }
}

/**
 * Retrieves the number of times a car is filled
  */
int Car::FillUps() {
    return _fillUps;
}