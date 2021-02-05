/*
    This program attempts to solve a maze (in a 10x10 2D array)
    recursively. The maze data is held in mazedata.txt.
*/

#include "maze.h"
#include <iostream>
#include <fstream>

using namespace std;

int main()
{
    ifstream inFile ("mazedata.txt");  
    Maze maze (inFile);     //Maze constructor, receives data from mazedata.txt
    bool exitFound = false; //was the exit found?

    maze.Print();                   //Print the initial state of the maze
    maze.FindExit(1,1,exitFound);   //Recursively start to explore the maze at x=1 and y=1

    //Print whether or not the exit was found
    if(exitFound)   
        cout << "Found exit!" << endl; 
    else
        cout << "No exit!" << endl;
    
    return 0;
}
