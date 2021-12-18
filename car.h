#ifndef STACKPATH_CAR_H
#define STACKPATH_CAR_H

#include "station.h"

#include <memory>
class Station;
class Car {

private:
    int _fillUps = 0;

public:
    Car();
    Car(const Car&) noexcept;
    void Fill(Station*);
    int FillUps();
};

#endif //STACKPATH_CAR_H
