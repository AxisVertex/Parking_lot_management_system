#include "Queue.h"

Queue::Queue() {
    front = nullptr;
    rear = nullptr;
    maxCapacity = 10;
    currentSize = 0;
}

Queue::~Queue() {
    front = nullptr;
    rear = nullptr;
}

void Queue::Enqueue(Vehicle car) {
    QueueNode* newNode = new QueueNode();
    newNode->car = car;

    if (IsEmpty()) {
        front = newNode;
        rear = newNode;
        currentSize += 1;
    }
    else {
        if (!IsFull()) {
            rear->nextNode = newNode;
            rear = newNode;
            currentSize += 1;
        }
        else {
            std::cout << "Queue is full" << std::endl;
        }
    }
}

Vehicle Queue::Dequeue() {
    QueueNode* nodeHolder = nullptr;

    if (!IsEmpty()) {
        if (front == rear) {
            nodeHolder = front;
            front = nullptr;
            rear = nullptr;

            return nodeHolder->car;
        }
        else {
            nodeHolder = front;
            front = front->nextNode;
            return nodeHolder->car;
        }
        currentSize -= 1;
    }
    else {
        std::cout << "Queue empty" << std::endl;
    }
}

bool Queue::IsEmpty() {
    return (front == nullptr && rear == nullptr);
}

bool Queue::IsFull() {
    return (currentSize > maxCapacity);
}

void Queue::DisplayAll() {
    
    if (IsEmpty()) {
        std::cout << "There are no cars." << std::endl;
    }
    else {
        QueueNode* nodeHolder = front;
        std::cout << "FRONT: " << nodeHolder->car.Get_Plate_Number() << std::endl;
        while (nodeHolder) {
            std::cout << nodeHolder->car.Get_Plate_Number() << " -> ";
            nodeHolder = nodeHolder->nextNode;
        }
        std::cout << "NULL" << std::endl;
    }

}