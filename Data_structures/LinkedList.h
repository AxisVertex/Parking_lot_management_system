#pragma once

#include "../Includes.h"

struct LinkedListNode {
    Vehicle car;
    LinkedListNode* nextNode;
};

class LinkedList {

private:

    LinkedListNode* head;
    
public:
    LinkedList();
    ~LinkedList();

    void InsertAtBeginning(Vehicle car);

    void InsertAtEnd(Vehicle car);

    NodePos Remove(std::string plateNumber); // do this later

    void DisplayAll();

};
