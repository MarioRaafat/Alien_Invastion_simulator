//
// Created by mohse on 4/17/2024.
//

#include "ArrayStack.h"
#include <iostream>
using namespace std;

int main()
{
    ArrayStack<char> stack;
    char item;
    cout << "Pushing A, B, and C onto the stack\n";
    stack.push('A');
    stack.push('B');
    stack.push('C');

    cout << "Reverse and print the stack\n";
    while (!stack.isEmpty())
    {
        stack.pop(item);
        cout << item << endl;
    }  // end while

    cout << stack.isEmpty() << endl;
}  // end main
