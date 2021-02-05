#include <iostream>
#include "maze.h"

//Constructor, reads maze data from input file stream
Maze::Maze(std::ifstream & inFile)
{
    inFile >> xplor >> maxRows >> maxCols;  //Read in xplor, maxRows, and maxCols

    for(int i = 0; i <= maxRows+1; i++)     //Iteration for each row
    {
        //Place 'X' boundary on first and last column of each row (vertical boundary)
        maze[i][0] = 'X';  
        maze[i][maxCols+1] = 'X';

        for(int j = 1; j <= maxCols; j++)   //Iteration for each column
        {
            if(i == 0 || i == maxRows+1)    //If the row is the first or last place 'X' boundary 
                maze[i][j] = 'X';           //on those rows on each column (horizontal boundary)
            else
                inFile >> maze[i][j];       //If not, read in maze value from input stream
        }
    }
}

//Prints out the current state of the maze, called in FindExit
void Maze::Print()
{
    std::cout << "Maze state:" << std::endl;  

    //For each element in map, bring it out (excluding boundary)
    for(int i = 1; i <= maxRows; i++) 
    {
        for(int j = 1; j <= maxCols; j++)
            std::cout << " " << maze[i][j];
        std::cout << std::endl;
    }
}

//Recursive function that searches the maze for the exit char 'E',
//if the current spot if an acceptable position char 'O', then
//the function will call itself for each direction in the char
//order of xplor.
void Maze::FindExit(int currRow, int currCol, bool& exitFound)
{
    
    if(maze[currRow][currCol] == 'E')  //Base case: the exit is found ('E')
    {
        std::cout << "Exploring " << currRow //Log exploration of location
                  << "," << currCol << std::endl;

        exitFound = true;                    //The exit is found!
    }
    else if(maze[currRow][currCol] == 'O')   //Recursive case: explorable location ('O')
    {
        std::cout << "Exploring " << currRow //Log exploration of location
                  << "," << currCol << std::endl;
                  
        maze[currRow][currCol] = '*';        //Mark exploration of location on maze array

        Print();    //Print out the current state

        for(int i = 0; i < 4; i++)  //For each direction in xplor
        {
            std::pair<int,int> move = getMove(xplor[i]);  //Get pair of relative row-column movement from current position
            FindExit(currRow+move.first, currCol+move.second, exitFound);  //Add relative position to current position,
        }                                                                  //and recursively call to explore each position
    }                                                                      //around the next position.
}

//Returns x and y-compenent in an std::pair to represent
//whether to go left, right, up, or down in the maze array,
//used by FindExit
std::pair<int,int> Maze::getMove(char direction)
{
    int row_offset = 0, col_offset = 0;  //Assume compenents in both axes is 0

    if(direction == 'N')        //If north, go up 1 row
        row_offset = -1;
    else if(direction == 'S')   //If south, go down 1 row
        row_offset = 1;
    else if(direction == 'E')   //If east, go up 1 column
        col_offset = 1;
    else if(direction == 'W')   //If west, go down 1 column
        col_offset = -1;

    return std::make_pair(row_offset, col_offset);  //Return pair of offset values using std::make_pair
}