#ifndef STACKPATH_STATION_H
#define STACKPATH_STATION_H

#include "car.h"
#include "concurrent_queue.h"

#include <condition_variable>
#include <mutex>

// Forward declaration
class Car;

const int numPumps = 2;

// A Station is a gas station abstraction
class Station {
private:
    concurrent_queue<Car*> _carQueue;
    std::condition_variable _cv;
    bool _doFill;
    int _fills[numPumps];
    std::mutex _quetex;


public:
    Station();

    void DoFill();
    void GetInLine(Car*);
    int GetFills(int);
    void IncrementFills(int);
    void NotifyQueue();
    void Requeue(Car*);
    void StopFill();

    std::mutex pumpMutexes[numPumps];

};


#endif //STACKPATH_STATION_H
