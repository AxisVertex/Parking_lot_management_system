#include "Vehicle.h"

Vehicle::Vehicle() {
    plateNumber = Generate_Plate_Number();
}

std::string Vehicle::Get_Plate_Number() {
    return plateNumber;
}

void Vehicle::AssignPosition(int x, int y) {
    posX = x;
    posY = y;
}

std::string Vehicle::Generate_Plate_Number() {
    const char letters[] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z'};
    const char numbers[] = {'1', '2', '3', '4', '5', '6', '7', '8', '9', '0'};
    std::string newPlateNumber;

    // adding 4 numbers in the plate number
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::mt19937 generator(seed); // Mersenne Twister engine


    // Define the range for random numbers
    std::uniform_int_distribution<int> distributionAlphabets(0, 25); // Random integers between 0 and 25
    // adding 3 letters in the plate number
    for (int i = 0; i <= 2; i++) {
        int randomNumber = distributionAlphabets(generator);
        newPlateNumber.push_back(letters[randomNumber]);
    }

    newPlateNumber += "-";

    // Define the range for random numbers
    std::uniform_int_distribution<int> distributionDigits(0, 9); // Random integers between 0 and 3
    // Generate and print random numbers
    for (int i = 0; i <= 3; ++i) {
        int randomNumber = distributionDigits(generator);
        newPlateNumber.push_back(numbers[randomNumber]);
    }

    return newPlateNumber;
}

int Vehicle::GetXPos() {
    return posX;
}

int Vehicle::GetYPos() {
    return posY;
}