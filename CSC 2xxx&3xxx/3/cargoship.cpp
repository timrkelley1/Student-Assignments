// Name: Timothy Rexx Kelley

#include <iostream>
#include "cargoship.h"

// Derived constructor - sets maxCapacity and percForward,
// and allocated tonForward and tonAft, both initialized to 0
CargoShip::CargoShip(std::string _name, double fuelLoad, double forwPerc, int cargoCap) : Ship(_name, fuelLoad)
{
    maxCapacity = cargoCap;
    percForward = forwPerc;

    tonForward = new double;
    tonAft = new double;

    *tonForward = *tonAft = 0.0;
}

// Destructor - deallocates tonForward and tonAft
CargoShip::~CargoShip()
{
    delete tonForward;
    delete tonAft;
    tonForward = tonAft = nullptr;
}

// Uses parent fuel function and outputs name and fuelPoint afterwards
void CargoShip::fuel(int fuelPoint)
{
    Ship::fuel();
    std::cout << name << " " << fuelPoint << std::endl;
}

// The load function will simulate the CargoShip distributing
// cargoTons to the forward and aft bays. 
void CargoShip::load(int cargoTons)
{
    //Add the percentage of cargoTons (based on percForward) to
    //the forward bay, and add the remainder to the aftBay 
    *tonForward += percForward * cargoTons;
    *tonAft += cargoTons - (percForward * cargoTons);

    //If forward or aft bay is beyond max capacity of its values
    //(caluclated by maxCapicity*percForward), top out the bay
    //at its max value of tons 
    if(*tonForward > maxCapacity * percForward)
        *tonForward = maxCapacity * percForward;
    if(*tonAft > maxCapacity * (1-percForward))
        *tonAft = maxCapacity * (1-percForward);

    //Output name, tons on forward bay, and tons on aft bay
    std::cout << name << " " << *tonForward 
              << " " << *tonAft << std::endl;
}