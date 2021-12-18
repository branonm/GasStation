cmake_minimum_required(VERSION 3.19)
project(stackPath)

set(CMAKE_CXX_STANDARD 20)
include_directories(
        /usr/local/Cellar/boost/1.76.0/include/
        )

add_executable(stackPath main.cpp station.cpp station.h car.cpp car.h concurrent_queue.h)