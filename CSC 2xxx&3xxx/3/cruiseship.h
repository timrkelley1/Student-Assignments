// Name: Timothy Rexx Kelley

#include "ship.h"

#ifndef CRUISESHIP_H
#define CRUISESHIP_H

class CruiseShip : public Ship
{
    public:
        // Constructor - uses parent Ship constructor for name and fuel,
        // and sets percLux, percUpper, and percLower
        CruiseShip(std::string, double, double, double, double);
        
        // Overrides parent sail function to output name and passengers
        // on each deck.
        void sail() override;

        // Calculates the distribution of passengers to decks
        // using associated percentages 
        void load(int) override;

    private:
        int passLux, passUpper, passLower; // represents the passengers on each deck
        double percLux, percUpper, percLower; // percentages for distrubition of passengers
                                              // to each deck
};

#endif