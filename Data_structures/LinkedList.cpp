#include "LinkedList.h"

LinkedList::LinkedList() {
    head = nullptr;
}

LinkedList::~LinkedList() {
    
    while (head != nullptr) {
        LinkedListNode* temp = head->nextNode;

        delete head;

        head = temp;
    }

}

void LinkedList::InsertAtBeginning(Vehicle car) {
    LinkedListNode* newNode = new LinkedListNode();
    newNode->car = car;
    newNode->nextNode = head;
    head = newNode;
}

void LinkedList::InsertAtEnd(Vehicle car) {
    LinkedListNode* newNode = new LinkedListNode();
    newNode->car = car;
    newNode->nextNode = nullptr;

    // check if the head is empty (if it is assign it to head)
    if (!head) 
        head = newNode;
    else {
        // go through the end of the list
        LinkedListNode* nodeHolder = head;
        while(nodeHolder->nextNode) {
            nodeHolder = nodeHolder->nextNode;
        }

        nodeHolder->nextNode = newNode;
    }
}


NodePos LinkedList::Remove(std::string plateNumber) {
    // do this later
    bool plateNumberFound = false;

    LinkedListNode* prevNode = head;
    LinkedListNode* nodeHolder = head->nextNode;

    if (head->car.Get_Plate_Number() == plateNumber)
        plateNumberFound = true;

    while (nodeHolder) {        
        if (nodeHolder->car.Get_Plate_Number() == plateNumber || prevNode->car.Get_Plate_Number() == plateNumber) {
            plateNumberFound = true;
            break;
        }

        prevNode = nodeHolder;
        nodeHolder = nodeHolder->nextNode;
    }

    NodePos posHolder;

    if (plateNumberFound) {
        if (head->car.Get_Plate_Number() == plateNumber) {
            posHolder.x = head->car.GetXPos();
            posHolder.y = head->car.GetYPos();

            if (nodeHolder != nullptr) {
                LinkedListNode* temp = head;
                head = nodeHolder;
                delete temp;
            }
            else {
                delete head;
                head = nullptr;
            }
        }
        else if (nodeHolder->car.Get_Plate_Number() == plateNumber) {
            posHolder.x = nodeHolder->car.GetXPos();
            posHolder.y = nodeHolder->car.GetYPos();

            prevNode->nextNode = prevNode->nextNode->nextNode;
            delete nodeHolder;
        }
    }
    else {
        posHolder.x = -1;
        posHolder.y = -1;
    }

    return posHolder;
}


void LinkedList::DisplayAll() {
    if (!head) {
        std::cout << "There are no parked vehicles." << std::endl;
    }
    else {
        LinkedListNode* nodeHolder = head;
        
        std::cout << "List of parked vehicles: ";
        while (nodeHolder) {
            std::cout << "["<< nodeHolder->car.Get_Plate_Number() << "] ";
            nodeHolder = nodeHolder->nextNode;
        }
        std::cout << std::endl;
    }
}