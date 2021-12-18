#ifndef STACKPATH_STATION_H
#define STACKPATH_STATION_H

#include "car.h"
#include "concurrent_queue.h"

#include <condition_variable>
#include <mutex>

class Car;
const int numPumps = 2;
class Station {
private:
    concurrent_queue<Car*> _carQueue;
    bool _doFill;
    std::condition_variable _cv;
    std::mutex _quetex;

public:
    Station();

    void DoFill();
    void GetInLine(Car*);
    void NotifyQueue();
    void Requeue(Car*);
    void StopFill();

    std::mutex pumpMutexes[numPumps];
    int fills[numPumps];
};


#endif //STACKPATH_STATION_H
