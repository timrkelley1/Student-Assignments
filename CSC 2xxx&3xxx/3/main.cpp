// Name: Timothy Rexx Kelley
// This project attempts to solve an inheritence problem.

#include <iostream>
#include <fstream>
#include <string>
#include "cargoship.h"
#include "cruiseship.h"

using namespace std;

void SailShip(Ship& ship);  // Simulates the ship object "sailing"

int main()
{
    ifstream inFile ("ships.txt");

    string name1, name2;  //names for cruise and cargo ships
    double fuel1, fuel2;  //fuel values for cruise and cargo ships
    double fperc, dperc[3]; //forward perc. for cargo and deck percentages for cruise ship
    int pass; //number of passengers for cruise ships
    int cap, tonsCargo, fuelPoint; //max capacity, cargo amount, and fuelPoint for cargo ship

    if(inFile)
    {
        //Receive all variables for cruise construstor/methods from inFile
        inFile >> name1 >> fuel1 >> dperc[0]
               >> dperc[1] >> dperc[2] >> pass;

        //Receive all variables for cargo constructor/methods from inFile
        inFile >> name2 >> fuel2 >> cap >> fperc 
               >> tonsCargo >> fuelPoint;
    }
    else
        return 1;

    // Instantiate cruise and cargo ship objects
    CruiseShip cruise (name1, fuel1, dperc[0], dperc[1], dperc[2]);  
    CargoShip cargo (name2, fuel2, fperc, cap);

    // Call fuel and load members of cruise, and call
    // SailShip using cruise as the reference argument
    cruise.fuel();
    cruise.load(pass);
    SailShip(cruise);

    // Call fuel and load members of cargo, and call
    // SailShip using cargo as the reference argument
    cargo.fuel(fuelPoint);
    cargo.load(tonsCargo);
    SailShip(cargo);

    return 0;
}

// Calls the sail method of the ship object
void SailShip(Ship& ship)
{
    ship.sail();
}
