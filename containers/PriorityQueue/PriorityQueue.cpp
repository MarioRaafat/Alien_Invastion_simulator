//////#include "PriorityQueue.h"
//////#include <stdlib.h>
//////#include <random>
////////Testing the priority queue
//////
//////struct Entity
//////{
//////    int salry;
//////    int age;
////////    bool operator<(const Entity &other) const
////////    {
////////        return salry < other.salry;
////////    }
//////    Entity() = default;
//////    Entity(int salry, int age) : salry(salry), age(age) {}
//////bool operator<(const Entity &other) const
//////    {
//////        return salry < other.salry;
//////    }
//////    bool operator<(const Entity *other) const
//////    {
//////        return salry < other->salry;
//////    }
//////    bool operator>(const Entity &other) const
//////    {
//////        return salry > other.salry;
//////    }
//////    bool operator>(const Entity *other) const
//////    {
//////        return salry > other->salry;
//////    }
//////    bool operator<=(const Entity &other) const
//////    {
//////        return salry <= other.salry;
//////    }
//////    bool operator<=(const Entity *other) const
//////    {
//////        return salry <= other->salry;
//////    }
//////    bool operator>=(const Entity &other) const
//////    {
//////        return salry >= other.salry;
//////    }
//////    bool operator>=(const Entity *other) const
//////    {
//////        return salry >= other->salry;
//////    }
//////
//////};
//////template <>
//////struct std::less<Entity *> {
//////    bool operator()(const Entity *lhs, const Entity *rhs) const {
//////        return *lhs < *rhs;
//////    }
//////};
//////template <>
//////struct  std::less_equal<Entity *> {
//////    bool operator()(const Entity *lhs, const Entity *rhs) const {
//////        return *lhs <= *rhs;
//////    }
//////
//////};
//////template<>
//////struct std::greater_equal<Entity *> {
//////    bool operator()(const Entity *lhs, const Entity *rhs) const {
//////        return *lhs >= *rhs;
//////    }
//////};
//////template<>
//////struct std::greater<Entity *> {
//////    bool operator()(const Entity *lhs, const Entity *rhs) const {
//////        return *lhs > *rhs;
//////    }
//////};
//////int main()
//////{
//////    PriorityQueue<Entity> pq;
//////    PriorityQueue<Entity *> pq1;
//////    Entity *e = new Entity(202, 20);
//////    Entity *e1 = new Entity(123, 20);
//////    Entity *e2 = new Entity(123123, 20);
//////    Entity *e3 = new Entity(-101, 20);
//////    //the output should be 202 123 -101 123123
//////    //the output is -101 123123 123 202 // why is that and how to fix it
//////    //i think it is because the pointers are compared by their addresses not by the values they point to
//////
//////    pq1.push(e1);
//////    pq1.push(e3);
//////    pq1.push(e2);
//////    pq1.push(e);
//////    while (!pq1.is_empty())
//////    {
//////        Entity *e;
//////        pq1.pop(e);
//////        std::cout << e->salry << " " << e->age << "\n";
//////    }
////////    pq.push(*e);
////////    pq.push(*e1);
////////    pq.push(*e3);
////////    pq.push(*e2);
////////    while (!pq.is_empty())
////////    {
////////        Entity e;
////////        pq.pop(e);
////////        std::cout << e.salry << " " << e.age << "\n";
////////    }
////////
//////
//////}
////////    PriorityQueue<int> pq;
////////    //testing pushing
////////    for (int i = 0; i < 15; i++)
////////    {
////////        pq.push(rand() % 100);
////////    }
////////    while (!pq.is_empty())
////////    {
////////        int value;
////////        pq.pop(value);
////////        std::cout << value << " ";
////////    }
////////    std::cout << "\n";
////////    std::cout << "Size of the priority queue is: " << pq.size() << "\n";
////////    std::cout << "Capacity of the priority queue is: " << pq.capacity() << "\n";
////////    //addine values with repeated values
////////    pq.push(1);
////////    pq.push(1);
////////    pq.push(1);
////////    pq.push(123);
////////    pq.push(12);
////////    pq.push(123);
////////    pq.push(13);
////////    pq.push(14);
////////    pq.push(12);
////////    pq.push(13);
////////    pq.push(14);
////////    pq.push(12);
////////    pq.push(123);
////////    pq.push(123);
////////    pq.push(125);
////////
////////    while (!pq.is_empty())
////////    {
////////        int value;
////////        pq.pop(value);
////////        std::cout << value << " ";
////////    }
////////    std::cout << "\n";
////////    std::cout << "Size of the priority queue is: " << pq.size() << "\n";
////////    std::cout << "Capacity of the priority queue is: " << pq.capacity() << "\n";
////////
////////    //adding more than 15 elements to test the resizing
////////    std::cout << "Testing the resizing of the priority queue by adding 30 elements\n";
////////    for (int i = 0; i < 30; i++)
////////    {
////////        pq.push(rand() % 20);
////////    }
////////    std::cout << "Size of the priority queue is: " << pq.size() << "\n";
////////    std::cout << "Capacity of the priority queue is: " << pq.capacity() << "\n";
////////    while (!pq.is_empty())
////////    {
////////        int value;
////////        pq.pop(value);
////////        std::cout << value << " ";
////////    }
////////    std::cout << "Size of the priority queue is: " << pq.size() << "\n";
////////    std::cout << "Capacity of the priority queue is: " << pq.capacity() << "\n";
////////
////////    //testing peek and pop
////////    int x{} ;
////////    pq.push(1);
////////    std::cout << "Peek: " << pq.peek(x) << "\n";
////////    pq.pop(x);
////////    std::cout << "Pop: " << x << "\n";
////////    std::cout << "Chnage the value of x to 100\n";
////////    x = 100;
////////    std::cout << "Peek: " << pq.peek(x) << "\n";
////////    std::cout << "x = " << x << "\n";
////////
////////    //testing clear
////////    pq.push(1);
////////    std::cout << "Size of the priority queue is: " << pq.size() << "\n";
////////    pq.clear();
////////    std::cout << "Size of the priority queue is: " << pq.size() << "\n";
////////    pq.clear();
////////    std::cout << "Size of the priority queue is: " << pq.size() << "\n";
////////
////////
////////    //testing copy constructor and assignment operator
////////    PriorityQueue<int> pq1;
////////    pq1.push(1);
////////    pq1.push(3);
////////    pq1.push(2);
////////    pq1.push(4);
////////
////////    //copy constructor
////////    PriorityQueue<int> pq2 = pq1;
////////
////////    while (!pq2.is_empty())
////////    {
////////        int value;
////////        pq2.pop(value);
////////        std::cout << value << " ";
////////    }
////////    std::cout << "\n";
////////
////////    //assignment operator
////////    PriorityQueue<int> pq3;
////////    pq3.push(43342);
////////    pq3.push(3123);
////////    pq3.push(2);
////////
////////    pq3 = pq1;
////////
////////    while (!pq3.is_empty())
////////    {
////////        int value;
////////        pq3.pop(value);
////////        std::cout << value << " ";
////////    }
////////
////////    //testing move constructor and move assignment operator
////////    PriorityQueue<int> pq4;
////////    pq4.push(1);
////////    pq4.push(3);
////////
////////    //move constructor
////////    PriorityQueue<int> pq5 = std::move(pq4);
////////    std::cout << "====================\n";
////////    while (!pq5.is_empty())
////////    {
////////        int value;
////////        pq5.pop(value);
////////        std::cout << value << " ";
////////    }
////////    std::cout << "\n";
////////
////////    //size pq4 should be 0 and printing it should not print anything and push should not work and pop should return false
////////    std::cout << "Size of pq4: " << pq4.size() << "\n";
////////    pq4.push(1);
////////    pq4.push(2);
////////    std::cout << "Size of pq4: " << pq4.size() << "\n";
////////    int value;
////////    std::cout << "Pop: " << pq4.pop(value) << "\n";
////////    std::cout << "pekk: " << pq4.peek(value) << "\n";
////////
////////    //testing move assignment operator
////////    PriorityQueue<int> pq6;
////////    pq6.push(1);
////////    pq6.push(3);
////////    std::cout << pq6.size() << "\n";
////////
////////    PriorityQueue<int> pq7;
////////    pq7.push(1);
////////    std::cout << pq7.size() << "\n";
////////
////////    pq7 = std::move(pq6);
////////    std::cout << pq6.size() << "\n";
////////    std::cout << pq7.size() << "\n";
////////    while (!pq7.is_empty())
////////    {
////////        int value;
////////        pq7.pop(value);
////////        std::cout << value << " ";
////////    }
////////std::cout << "\n";
////////    //size pq6 should be 0 and printing it should not print anything and push should not work and pop should return false
////////    std::cout << "Size of pq6: " << pq6.size() << "\n";
////////    pq6.push(1);
////////    pq6.push(2);
////////    std::cout << "Size of pq6: " << pq6.size() << "\n";
////////    std::cout << "Pop: " << pq6.pop(value) << "\n";
////////    std::cout << "pekk: " << pq6.peek(value) << "\n";
////////
////////    //testing intializer list
////////    PriorityQueue<int> pq8 = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10,23423,123,00,2,2,3,3,300,199,123,4351523,32451,41231,11};
////////
////////    while (!pq8.is_empty())
////////    {
////////        int value;
////////        pq8.pop(value);
////////        std::cout << value << " ";
////////    }
////////    //test memory leak using valgrind
////////    int *arr = new int[100];
////////    return 0;
////////}
////
////
//#include "PriorityQueue.h"
//#include <iostream>
//struct Entity
//{
//    int salry;
//    int age;
//
//    Entity() = default;
//    Entity(int salry, int age) : salry(salry), age(age) {}
//
//    // Define custom comparison for pointers to Entity
//    bool operator>(const Entity &other) const
//    {
//        return this->salry > other.salry;
//    }
//};
//
//
//// Define custom comparison functor for pointers to Entity
//struct Compare
//{
//    bool operator()(const Entity *lhs, const Entity *rhs) const
//    {
//        return *lhs > *rhs;
//    }
//};
//
//
//
//int main()
//{
//    PriorityQueue<Entity *, Compare> pq1;
//
//    Entity *e1 = new Entity(123, 20);
//    Entity *e3 = new Entity(-101, 20);
//    Entity *ee = new Entity(202, 20);
//    Entity *e = new Entity(202, 20);
//    Entity *e2 = new Entity(123123, 20);
//    Entity *ec = new Entity(202123, 20);
//
//    pq1.push(e1);
//    pq1.push(e3);
//    pq1.push(ec);
//    pq1.push(e2);
//    pq1.push(ee);
//    pq1.push(e);
//
//    while (!pq1.is_empty())
//    {
//        Entity *e;
//        pq1.pop(e);
//        std::cout << e->salry << " " << e->age << "\n";
////        delete e;
//    }
//    return 0;
//}
