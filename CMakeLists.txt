cmake_minimum_required(VERSION 3.29)
project(Alien_Invastion_simulator)

set(CMAKE_CXX_STANDARD 14)

include_directories(containers)

add_executable(Alien_Invastion_simulator
        containers/PriorityQueue/PriorityQueue.h
        containers/PriorityQueue/PriorityQueue.cpp
#        //containers/Dequeue/Dequeue.cpp)
)
