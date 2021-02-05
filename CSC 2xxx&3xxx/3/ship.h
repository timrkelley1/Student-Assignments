// Name: Timothy Rexx Kelley

#include <string>

#ifndef SHIP_H
#define SHIP_H

class Ship 
{
    public:
        // Constructor - initializes name and fuelOnBoard
        Ship(std::string, double);

        // Outputs the name and fuelOnBoard
        void fuel();

        // Prints Ship object's name and "sailing"
        virtual void sail();

        // Simulates the ship loading some kind of quantity (cargo, passengers, etc.)
        virtual void load(int) = 0;

    protected:
        std::string name; 
        double fuelOnBoard;
};

#endif