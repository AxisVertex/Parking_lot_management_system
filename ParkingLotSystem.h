#pragma once
#include "Data_structures/LinkedList.cpp"
#include "Data_structures/Stack.cpp"
#include "Data_structures/Queue.cpp"

class ParkingLotSystem {

private:

    char parkingLotSpots[4][15];

    int availableSpots;
    int availableQueueSpot;
    int inQueue;
    bool programIsRunning;

     // add linked list here
    LinkedList vehicleList;
    // add queue here
    Queue queueLine;
    // add stack here
    Stack recentAvailableSpots;

    void RecordLog(int type, std::string plateNumber, int x, int y);

public:

    ParkingLotSystem();
    ~ParkingLotSystem();

    void AssignVehicle();
    
    void RetrieveVehicle();

    void DisplayParkingLot();

    void DisplayMenu();

    void DisplayAllParkedVehicles();

    std::string TakeUserChoice();

    void UpdateParkingLot(int x, int y, bool allocate);

    void Start();

};