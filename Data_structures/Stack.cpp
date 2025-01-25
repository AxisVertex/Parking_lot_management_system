#include "Stack.h"

// REDO THIS

Stack::Stack() {
    top = nullptr;
    maxCapacity = 60;
    currentSize = 0;
}

Stack::~Stack() {
    while (top != nullptr) {
        StackNode* temp = top->nextNode;

        delete top;

        top = temp;
    }
}

void Stack::Push(int x, int y) {

    if (!IsFull()) {
        StackNode* newNode = new StackNode();
        newNode->x = x;
        newNode->y = y;
        newNode->nextNode = top;

        top = newNode;
        currentSize += 1;
    }
    else {
        std::cout << "Stack is full" << std::endl;
    }
}

NodePos Stack::Pop() {
    if (!IsEmpty()) {
        NodePos posHolder;
        posHolder.x = top->x;
        posHolder.y = top->y;

        StackNode* prevTop = top;
        top = prevTop->nextNode;

        delete prevTop;

        currentSize -= 1;
        
        return posHolder;
    }
    else {
        std::cout << "Container empty" << std::endl;
    }
    // fix warning here later
}

bool Stack::IsFull() {
    return (currentSize > maxCapacity);
}

bool Stack::IsEmpty() {
    return (top == nullptr);
}

void Stack::DisplayAll() {
    if (!top) {
        std::cout << "There are no spots." << std::endl;
    }
    else {

        StackNode* topNode = top;
        while (topNode) {
            std::cout << "[" << topNode->x << ", " << topNode->y << "]" <<" -> ";
            topNode = topNode->nextNode;
        }
        std::cout << "NULL" << std::endl;
    }
}

