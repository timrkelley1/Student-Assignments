// Name: Timothy Rexx Kelley

#include <iostream>
#include <string>
#include "ship.h"

// Constructor for Ship Object, sets name and fuelOnBoard equal to parameters
Ship::Ship(std::string _name, double fAmount)
{
    name = _name;
    fuelOnBoard = fAmount;
}

//Outputs the name and fuelOnBoard to cout
void Ship::fuel()
{
    std::cout << name << " " << fuelOnBoard << std::endl;
}

// Outputs name and "sailing" to incidcate polymorphism
void Ship::sail()
{
    std::cout << name << " sailing" << std::endl; 
}
