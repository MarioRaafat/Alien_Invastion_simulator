//	This is an updated version of code originally
//  created by Frank M. Carrano and Timothy M. Henry.
//  Copyright (c) 2017 Pearson Education, Hoboken, New Jersey.

/** ADT stack: Array-based implementation.
 @file ArrayStack.h */

#ifndef ARRAY_STACK_
#define ARRAY_STACK_
#include <iostream>
#include "StackADT.h"
#include <type_traits>

//Unless spesificed by the stack user, the default size is 100
template<typename T>
class ArrayStack : public StackADT<T>
{
    enum { MAX_SIZE = 1000 };
private:
    T items[MAX_SIZE];		// Array of stack items
    int top;                   // Index to top of stack


public:
    void print() const {
        for (int i = top; i >= 0; i--) {
            if (std::is_pointer<T>::value) {
                items[i]->print();
            }
            else {
                std::cout << items[i] << " ";
            }
        }
        std::cout << std::endl;
    }
    friend ostream& operator<<(ostream& os, const ArrayStack<T>& stack) {
        os << "[";
        for (int i = stack.top; i >= 0; i--) {
            if (std::is_pointer<T>::value) {
                os << *stack.items[i];
            }
            else {
                os << stack.items[i];
            }
            if (i != 0) {
                os << " ";
            }

        }
        os << "]\n";
        return os;
    }

    int getTop() const {
        return top + 1;
    }

    ArrayStack()
    {
        top = -1;
    }  // end default constructor

    bool isEmpty() const
    {
        return top == -1;
    }  // end isEmpty

    bool push(const T& newEntry)
    {
        if (top == MAX_SIZE - 1) return false;	//Stack is FULL

        top++;
        items[top] = newEntry;
        return true;
    }  // end push

    bool pop(T& TopEntry)
    {
        if (isEmpty()) return false;

        TopEntry = items[top];
        top--;
        return true;
    }  // end pop

    bool peek(T& TopEntry) const
    {
        if (isEmpty()) return false;

        TopEntry = items[top];
        return true;
    }  // end peek

}; // end ArrayStack

#endif