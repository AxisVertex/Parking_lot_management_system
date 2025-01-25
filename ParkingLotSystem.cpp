#include "ParkingLotSystem.h"

void ParkingLotSystem::RecordLog(int type, std::string plateNumber, int x = -1, int y = -1) {

    std::ofstream logActivity;
    logActivity.open("parking_log.txt", std::ios_base::app);

    // PARK, RETRIEVE, QUEUE
    switch(type) {
        case 1: { // PARK
            logActivity << "[PARK] Plate number: " << plateNumber << " | Position: (" << x << ", " << y << ")\n";
            break;
        }
        case 2: { // RETRIEVE
            logActivity << "[RETRIEVE] Plate number: " << plateNumber << " | Position: (" << x << ", " << y << ")\n";
            break;
        }
        case 3: { // QUEUE
            logActivity << "[QUEUE] Plate number: " << plateNumber << "\n";
        }
    }

    logActivity.close();
}

ParkingLotSystem::ParkingLotSystem() {
    // initializing the 2D array
    for (int row = 0; row <= 3; row++) {
        for (int column = 0; column <= 14; column++) {
            recentAvailableSpots.Push(row, column);
            parkingLotSpots[row][column] = ' ';
        }
    }

    availableSpots = 60;
    availableQueueSpot = 10;
    inQueue = 0;
    programIsRunning = true;
}

ParkingLotSystem::~ParkingLotSystem() {}

void ParkingLotSystem::AssignVehicle() {
    if (availableSpots > 0) { // assign to a parking spot
        NodePos nodePos = recentAvailableSpots.Pop();

        Vehicle newVehicle;
        newVehicle.AssignPosition(nodePos.x, nodePos.y);

        UpdateParkingLot(nodePos.x, nodePos.y, true);
        vehicleList.InsertAtEnd(newVehicle);

        availableSpots -= 1;
        RecordLog(1, newVehicle.Get_Plate_Number(), nodePos.x, nodePos.y);
    }
    else { // Assign to queue line
        if (availableQueueSpot > 0) {
            Vehicle newVehicle;
            queueLine.Enqueue(newVehicle);
            inQueue += 1;
            availableQueueSpot -= 1;
            RecordLog(3, newVehicle.Get_Plate_Number());
        }
        else {
            std::cout << "Assignment failed, no spaces left in the spot and the queue line." << std::endl;
        }
    }
}

void ParkingLotSystem::RetrieveVehicle() {
    if (availableSpots < 60) { // check if there are parked vehicles ( less than 60 means there are cars parked)
        std::cout << "Enter vehicle plate number: ";
        std::string plateNumber;
        std::getline(std::cin, plateNumber);

        // returns back the position if its found / if its not found returns x = -1 and y = -1
        NodePos posFound = vehicleList.Remove(plateNumber);

        if (posFound.x != -1 && posFound.y != -1) {
            recentAvailableSpots.Push(posFound.x, posFound.y);

            UpdateParkingLot(posFound.x, posFound.y, false);
            availableSpots += 1;
            RecordLog(2, plateNumber, posFound.x, posFound.y);
        }
        else {
            std::cout << "Vehicle not found." << std::endl;
        }

        // check if there are vehicles waiting in the queue line
        for (int vehicleInQueue = 1; vehicleInQueue <= inQueue; vehicleInQueue++) {
            if (availableSpots > 0) { // assign to a parking spot
                NodePos nodePos = recentAvailableSpots.Pop();

                Vehicle newVehicle = queueLine.Dequeue();
                newVehicle.AssignPosition(nodePos.x, nodePos.y);

                UpdateParkingLot(nodePos.x, nodePos.y, true);
                vehicleList.InsertAtEnd(newVehicle);

                availableSpots -= 1;
                inQueue -=1;
                RecordLog(1, newVehicle.Get_Plate_Number(), nodePos.x, nodePos.y);
            }
            else {
                break;
            }
        }

    }
    else {
        std::cout << "There are no currently parked vehicles" << std::endl;
    }
}

void ParkingLotSystem::DisplayParkingLot() {

    // add the visual for the queue line here

    std::cout << "   -------------         --------------" << std::endl;
    std::cout << "  |                                   |" << std::endl;

    for (int row = 3; row >= 0; row--) {

        std::cout << "  |  |";
        for (int column = 14; column >= 0; column--) {
            std::cout << parkingLotSpots[row][column] << "|";
        }
        std::cout << "  |" << std::endl;

        if (row == 2)
            std::cout << "  |                                   |" << std::endl;
        else if (row == 3 || row == 1)
            std::cout << "  |  |-----------------------------|  |" << std::endl;

    }

    std::cout << "  |                                   |" << std::endl;
    std::cout << "   ------------------------------------" << std::endl;

    std::cout << "Vehicles in queue line: [" << inQueue << "/10]" << std::endl;

}

void ParkingLotSystem::DisplayMenu() {
    std::cout << "-----------------------------------------" << std::endl;
    std::cout << "Welcome to Parking Lot Management System!" << std::endl;
    std::cout << "-----------------------------------------" << std::endl;

    std::cout << "Choose an option: " << std::endl;
    std::cout << "[1] Assign a vehicle to the nearest spot." << std::endl;
    std::cout << "[2] Retrive a vehicle via plate number." << std::endl;
    std::cout << "[3] Display all plate numbers." << std::endl;
    std::cout << "[4] Turn off program." << std::endl;
}

void ParkingLotSystem::DisplayAllParkedVehicles() {
    vehicleList.DisplayAll();
}

std::string ParkingLotSystem::TakeUserChoice() {

    while (true) {
        std::cout << "> ";
        int userChoice;
        std::cin >> userChoice;
        std::cin.ignore();

        // makes sure the input is integer
        if (std::cin.fail()) {
            // Clear the failbit and ignore the remaining
            // input
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
        }

        switch (userChoice) {
            // Assign
            case 1: {
                return "Assign";
            }
            // Retrieve
            case 2: {
                return "Retrieve";
            }
            case 3: {
                return "DisplayParkedVehicles";
            }
            // Turn off
            case 4: {
                return "Off";
            }

            default: {
                std::cout << "Invalid input, try again." << std::endl;
                std::cin.clear();
                continue;
            }
        } 
    }

} 

void ParkingLotSystem::UpdateParkingLot(int x, int y, bool allocate) {
    if (allocate)
        parkingLotSpots[x][y] = '0';
    else {
        parkingLotSpots[x][y] = ' ';
    }
}

void ParkingLotSystem::Start() {

    while (programIsRunning) {
        DisplayParkingLot();
        DisplayMenu();

        std::string choice = TakeUserChoice();

        if (choice == "Assign") 
            AssignVehicle();
        else if (choice == "Retrieve") 
            RetrieveVehicle();
        else if (choice == "DisplayParkedVehicles")
            DisplayAllParkedVehicles();
        else if (choice == "Off") 
            programIsRunning = false;
        
    }

    std::cout << "Closing program..." << std::endl; 

}