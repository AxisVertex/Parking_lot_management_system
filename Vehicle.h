#pragma once
#include <string>
#include <cstdlib>
#include <random>

class Vehicle {

private:
    std::string plateNumber;
    int posX;
    int posY;

    std::string Generate_Plate_Number();

public:
    Vehicle();

    std::string Get_Plate_Number();

    void AssignPosition(int x, int y);

    int GetXPos();
    int GetYPos();

};

