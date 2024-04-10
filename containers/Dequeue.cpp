#include "Dequeue.h"
//Test memory leaks using valgrind
int main() {
    Dequeue<int> dq;
    int data;

    dq.push_back(1);
    dq.push_back(2);
    dq.push_back(3);
    dq.push_back(4);
    dq.push_back(5);

    std::cout << "Size: " << dq.size() << std::endl;
    while (!dq.is_empty()) {
        dq.pop_front(data);
        std::cout << data << std::endl;
    }
    std::cout << "Size: " << dq.size() << std::endl;

    dq.push_front(1);
    dq.push_front(2);
    dq.push_front(3);
    dq.push_front(4);
    dq.push_front(5);

    while (!dq.is_empty()) {
        dq.pop_back(data);
        std::cout << data << std::endl;
    }
    std::cout << "Size: " << dq.size() << std::endl;

    //Testing the copy move constructor and assigments operators
    Dequeue<int> dq1;
    dq1.push_back(1);
    dq1.push_back(2);
    dq1.push_back(3);
    dq1.push_back(4);
    dq1.push_back(5);
    Dequeue<int> dq2 = dq1;

    std::cout << "Size: " << dq2.size() << std::endl;
    while (!dq2.is_empty()) {
        dq2.pop_front(data);
        std::cout << data << std::endl;
    }
    std::cout << "Size: " << dq2.size() << std::endl;

    std::cout << "======================" << std::endl;
    //Testing d1 is not empty
    dq1.print();
    std::cout << "Size: " << dq1.size() << std::endl;
    //test the copy assignment operator
    Dequeue<int> dq3;
    dq3 = dq1;
    std::cout << "Testing the copy assignment operator" << std::endl;
    dq3.print();
    std::cout << "Size: " << dq3.size() << std::endl;


    //Testing the move constructor
    Dequeue<int> dq4 = std::move(dq1);
    std::cout << "Testing the move constructor" << std::endl;
    dq4.print();
    std::cout << "Size: " << dq4.size() << std::endl;

    std::cout << "Moved size: " << dq1.size() << std::endl;
    std::cout << dq1.size();
    dq1.print();
    dq1.push_back(1);
    dq1.pop_front(data);

    //Testing the move assignment operator
    std::cout << "======================" << std::endl;
    Dequeue<int> dq5;
    dq5 = std::move(dq4);
    dq5.print();
    std::cout << "Size: " << dq5.size() << std::endl;
    dq5.pop_front(data);
    dq5.print();
    dq5.pop_back(data);
    dq5.print();
    std::cout << "Size: " << dq5.size() << std::endl;

    std::cout << "Testing the move assignment operator" << std::endl;
    std::cout << dq4.size() << std::endl;
    dq4.print();
    dq4.push_back(1);
    dq4.pop_front(data);
    return 0;
}
