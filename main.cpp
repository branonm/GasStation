#include "car.h"
#include "station.h"

#include <thread>
#include <iostream>
#include <vector>
#include <memory>

int main() {

    // Create a bunch of Cars and store
    const int numCars = 10;
    std::vector<Car*> cars;
    for (int x = 0; x < numCars; ++x) {
        cars.push_back(new Car);
    }
    Station gasStation;

    // Queue up Cars to the station
    for (Car * car : cars){
        gasStation.GetInLine(car);
    }
    // Launch the thread fill Cars from of the queue
    std::thread t(&Station::DoFill, &gasStation);

    int fillTime = 30;
    std::cout << "Filling Cars for " << fillTime << " seconds" << std::endl;

    // Give some feedback while filling
    for (int x = 0; x < fillTime; x++){
        std::cout << "." << std::flush;
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
    std::cout << std::endl;

    gasStation.StopFill();
    t.join();

    // Display each Car's fill count
    // Also cleanup
    int carNum = 0;
    for(auto car : cars){
       std::cout << "Car " << carNum << " Fill count: " << car->FillUps() << std::endl;
       delete car;
       carNum++;
    }
    cars.clear();

    // Display _fills for the pumps
    std::cout << "Pump 1: " << gasStation.GetFills(0) << ", Pump 2: " << gasStation.GetFills(1) << std::endl;

    return 0;
}
