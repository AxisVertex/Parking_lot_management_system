#pragma once
#include "../Includes.h"

struct QueueNode {
    Vehicle car;
    QueueNode* nextNode;
};

class Queue {

private:
    QueueNode* front;
    QueueNode* rear;

    int maxCapacity;
    int currentSize;

    bool IsEmpty();
    bool IsFull();

public:
    Queue();
    ~Queue();

    void Enqueue(Vehicle car);
    Vehicle Dequeue();

    void DisplayAll();

};