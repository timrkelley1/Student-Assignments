// Name: Timothy Rexx Kelley

#include <string>
#include "ship.h"

#ifndef CARGOSHIP_H
#define CARGOSHIP_H

class CargoShip : public Ship
{
    private:
        double *tonForward, *tonAft;  // the amount of cargo on the forward and aft bays
        double percForward;  // distribution of cargo that goes to forward bay
        int maxCapacity;     // total capacity of cargo (on both bays) on the cargo ship

    public:
        // Constructor - uses parent constructor for name and fuelLoad,
        // and initalizes percForward, maxCapacity, and pointer variables.
        CargoShip(std::string, double, double, int);
        
        // Deallocates tonForward and tonAft 
        ~CargoShip();

        // Calls parent fuel function and outputs name and fuelPoint afterwards
        void fuel(int);

        // Simulates the distribution of cargo to the forward and aft bays using percForward
        void load(int) override;
};

#endif