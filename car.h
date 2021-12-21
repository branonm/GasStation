#ifndef STACKPATH_CAR_H
#define STACKPATH_CAR_H

#include "station.h"

#include <memory>

// Forward declaration
class Station;

// A Car is an abstraction for a motor vehicle
class Car {
private:
    int _fillUps = 0;

public:
    Car();

    bool Fill(Station*);
    int FillUps();
};

#endif //STACKPATH_CAR_H
