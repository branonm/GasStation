#include "station.h"
#include <thread>

void Station::GetInLine(Car* car) {
    _carQueue.push(car);
}

void Station::Requeue(Car *car){
    if(this->_doFill){
        _carQueue.push(car);
    }
}

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

void Station::StopFill() {
    this->_doFill = false;
    while(!_carQueue.empty()){
        Car * car;
        _carQueue.try_pop(car);
    }
}

void Station::NotifyQueue() {
    _cv.notify_one();
}

Station::Station() {
    for (int x = 0; x < numPumps; x++){
        this->fills[x] = 0;
    }
}

