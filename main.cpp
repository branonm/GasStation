#include "car.h"
#include "station.h"

#include <thread>
#include <iostream>
#include <vector>
#include <memory>

int main() {
    const int numCars = 10;
    std::vector<Car*> cars;
    for (int x = 0; x < numCars; ++x) {
        cars.push_back(new Car);
    }
    Station gasStation;

    for (Car * car : cars){
        gasStation.GetInLine(car);
    }
    std::thread t(&Station::DoFill, &gasStation);
    int fillTime = 30;
    std::cout << "Filling Cars for " << fillTime << " seconds" << std::endl;

    for (int x = 0; x < fillTime; x++){
        std::cout << "." << std::flush;
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
    std::cout << std::endl;
    gasStation.StopFill();
    t.join();

    int carNum = 0;
    for(auto car : cars){
       std::cout << "Car " << carNum << " Fill count: " << car->FillUps() << std::endl;
       delete car;
       carNum++;
    }
    cars.clear();

    std::cout << "Pump 1: " << gasStation.fills[0] << ", Pump 2: " << gasStation.fills[1] << std::endl;

    return 0;
}
