cmake_minimum_required(VERSION 3.28.1)
project(Alien_Invastion_simulator)

set(CMAKE_CXX_STANDARD 14)

include_directories(Armies/AlienArmy)
include_directories(Armies/EarthArmy)
include_directories(containers/Array)
include_directories(containers/ArrayStack)
include_directories(containers/Dequeue)
include_directories(containers/LinkedQueue)
include_directories(containers/PriorityQueue)
include_directories(Game_Generator/Game)
include_directories(Game_Generator/Generator)
include_directories(Units/Alien)
include_directories(Units/ArmyUnit)
include_directories(Units/Earth)

add_executable(Alien_Invastion_simulator
        Units/Alien/AlienArmy.cpp
        Units/Alien/AlienArmy.h
        Units/Earth/EarthArmy.cpp
        Units/Earth/EarthArmy.h
        containers/Array/Array.cpp
        containers/Array/Array.h
        containers/ArrayStack/ArrayStack.cpp
        containers/ArrayStack/ArrayStack.h
        containers/ArrayStack/StackAdt.h
        containers/Dequeue/Dequeue.cpp
        containers/Dequeue/Dequeue.h
        containers/LinkedQueue/LinkedQueue.cpp
        containers/LinkedQueue/LinkedQueue.h
        containers/LinkedQueue/Node.h
        containers/LinkedQueue/QueueADT.h
        containers/PriorityQueue/LinkedQueue.cpp
        containers/PriorityQueue/PriorityQueue.cpp
        containers/PriorityQueue/PriorityQueue.h
        Game.cpp
        Game.h
        Generator.cpp
        Generator.h
        Units/Alien/AlienDrone.cpp
        Units/Alien/AlienDrone.h
        Units/Alien/AlienMonster.cpp
        Units/Alien/AlienMonster.h
        Units/Alien/AlienSoldier.cpp
        Units/Alien/AlienSoldier.h
        Units/ArmyUnit.cpp
        Units/ArmyUnit.h
        Units/Earth/EarthGunnery.cpp
        Units/Earth/EarthGunnery.h
        Units/Earth/EarthSoldier.cpp
        Units/Earth/EarthSoldier.h
        Units/Earth/EarthTank.cpp
        Units/Earth/EarthTank.h
        main.cpp)