#include "station.h"
#include <thread>

/**
 * Constructor
 */
Station::Station() {
    for (int x = 0; x < numPumps; x++) {
        this->_fills[x] = 0;
    }
}

/**
 * Fill cars.
 */
void Station::DoFill() {
    this->_doFill = true;
    while (this->_doFill) {
        if (!_carQueue.empty()) {
            Car *car;
            _carQueue.try_pop(car);
            std::thread t(&Car::Fill, car, this);
            t.detach();
        } else {
            std::unique_lock<std::mutex> lk(_quetex);
            _cv.wait(lk);
        }
    }
}

/**
 * Queue a car to be filled
 * @param car The car to be filled
 */
void Station::GetInLine(Car *car) {
    _carQueue.push(car);
}

/**
 * Gets the number of fills for a pump
 * @param pump The pump to retieve fill count for
 */
int Station::GetFills(int pump) {
    if (pump < numPumps) {
        return _fills[pump];
    }
    return -1;
}

/**
 * Wrapper for incrementing fills per pump
 */
void Station::IncrementFills(int pump) {
    if (pump < numPumps) {
        this->_fills[pump]++;
    }
}

/**
* Wrapper for notifying the internal condition variable
 */
void Station::NotifyQueue() {
    _cv.notify_one();
}

/**
 * Requeue the car for filling. Don't queue
 * if _doFill isn't true
 * @param car The car to requeue
 */
void Station::Requeue(Car *car) {
    if (this->_doFill) {
        _carQueue.push(car);
    }
}

/**
 * Stop filling Cars. Drain the queue
 */
void Station::StopFill() {
    this->_doFill = false;
    while (!_carQueue.empty()) {
        Car *car;
        _carQueue.try_pop(car);
    }
}







