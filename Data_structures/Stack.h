#pragma once

#include "../Includes.h"

// REDO THIS THING
// we use stacks to store the parking spot x and y pos

struct StackNode {
    int x;
    int y;
    StackNode* nextNode;
};

class Stack {

private:

    StackNode* top;
    int maxCapacity;
    int currentSize;

    bool IsFull();
    bool IsEmpty();

public:

    Stack();
    ~Stack();

    void Push(int x, int y);
    NodePos Pop();

    void DisplayAll();

};