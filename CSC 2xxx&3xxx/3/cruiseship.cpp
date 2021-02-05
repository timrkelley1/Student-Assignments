// Name: Timothy Rexx Kelley

#include <iostream>
#include "cruiseship.h"

// Derived constructor from Ship class, sets percentages of lower, lux., and upper decks
CruiseShip::CruiseShip(std::string _name, double fuel, double pLux, double pUpper, double pLower) : Ship(_name, fuel)
{
    percLux = pLux;
    percUpper = pUpper;
    percLower = pLower;
}

// Outputs name and the number of people on each deck to cout
void CruiseShip::sail()
{
    std::cout << name << " " << passLux << " " << passUpper << " " << passLower << std::endl;
}

// Calcuates the number of passengers for each deck by
// multiplying passengers by the deck's respective
// percentage.
void CruiseShip::load(int passengers)
{
    passLux = passengers * percLux;
    passUpper = passengers * percUpper;
    passLower = passengers * percLower;
}
