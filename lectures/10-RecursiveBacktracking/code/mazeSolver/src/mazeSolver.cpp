// This program builds and solves text-based mazes
// By: Chris Gregg
// Date: October 16, 2016
// The maze creation code was modified from:
// http://azerdark.wordpress.com/2009/03/29/588/
// and http://www.mazeworks.com/mazegen/mazetut/index.htm

#include <iostream>
#include "console.h"
#include "simpio.h"
#include "grid.h"

using namespace std;

const int MAXCELL = 900; // 30 x 30
const int WALL = 1;
const int PATH = 0;

// prototypes
void initMaze(Grid<int> &maze, int sideLength);

// generate maze
void generateMaze(Grid <int> &maze, int sideLength);
void mazeGenerator(int index, int backtrackX[],
        int backtrackY[], int x, int y, int n, int visited, Grid<int> &grid);
int isClosed(int x, int y, Grid<int> &maze);

// solve maze
void solveMazeRecursive(Grid<int> &maze);
bool solveMazeRecursive(int row, int col, Grid <int> &maze);

// solve maze and print as we go
void solveMazeRecursivePrint(Grid<int> &maze);
bool solveMazeRecursivePrint(int row, int col, Grid <int> &maze);

// for printing
void humanReadableMaze(Grid <int> &maze);
void printMaze(Grid <int> &maze);

int main() {
    Grid<int> maze;
    int sideLength=0;
    while (sideLength < 2 || sideLength > 30) {
        sideLength = getInteger("Please enter a size (2-30): ", "Size must be an integer.");
    }
    initMaze(maze,sideLength);
    generateMaze(maze, sideLength);

    cout << "Original Maze:" << endl;
    printMaze(maze);

    //solveMazeRecursive(maze); // the maze starts at 1,1

    // uncomment to print details of algorithm
    // (and comment out solveMazeRecursive(maze) above
    solveMazeRecursivePrint(maze);

    cout << "Solved Maze:" << endl;
    printMaze(maze);
    return 0;
}

// solveMaze should be passed a human-readable maze
// with a start and finish, and a start position of 1,1
// dead-end paths that have been tested should be marked
// with lowercase x
// The correct path should be marked with periods, .
void solveMazeRecursive(Grid<int> &maze) {
    solveMazeRecursive(1,1,maze);
    maze[1][1] = 'S'; // replace start, which is removed during solving stage
}

bool solveMazeRecursive(int row, int col, Grid<int> &maze) {
    // be careful! 2d arrays seem backwards and upside down
    // compared to cartesian coordinates:
    // maze[0][0] == top left
    // maze[1][0] == one down, zero to the right
    // maze[0][1] == zero down, one to the right
    // maze[row][col] == row down and col to the right

    if (maze[row][col] == 'X') {
        return false;
    }

    if (maze[row][col] == '.') {
        return false;
    }

    if (maze[row][col] == 'F') {
        return true;
    }

    maze[row][col] = '.';

    // Recursively call solveMazeRecursive(row,col)
    // for north, east, south, and west
    // If one of the positions returns true, then return true

    // north
    if (solveMazeRecursive(row-1,col,maze)) {
        return true;
    }

    // east
    if (solveMazeRecursive(row,col+1,maze)) {
        return true;
    }

    // south
    if (solveMazeRecursive(row+1,col,maze)) {
        return true;
    }

    // west
    if (solveMazeRecursive(row,col-1,maze)) {
        return true;
    }

    maze[row][col] = 'b';
    return false;
}

void solveMazeRecursivePrint(Grid<int> &maze) {
    solveMazeRecursivePrint(1,1,maze);
    maze[1][1] = 'S'; // replace start, which is removed during solving stage
}

bool solveMazeRecursivePrint(int row, int col, Grid<int> &maze) {
    cout << "row=" << row << " and col=" << col << ", ";
    // be careful! 2d arrays seem backwards and upside down
    // compared to cartesian coordinates:
    // maze[0][0] == top left
    // maze[1][0] == one down, zero to the right
    // maze[0][1] == zero down, one to the right
    // maze[row][col] == row down and col to the right

    // if the outside edges of our maze was not a wall,
    // we would need the following
    /*if (row < 0 || row >= maze.numRows() ||
            col < 0 || col >= maze.numCols()) {
        cout << "Hit edge of maze!";
        return false;
    }*/

    if (maze[row][col] == 'X') {
        cout << "Hit wall!";
        return false;
    }

    if (maze[row][col] == '.') {
        cout << "We came from here!";
        return false;
    }

    if (maze[row][col] == 'F') {
        cout << "Found the Finish!\n";
        return true;
    }

    maze[row][col] = '.';
    cout << "Marking with period (.) ";
    //print_maze(); // uncomment to debug

    // Recursively call solveMazeRecursivePrint(row,col)
    // for north, east, south, and west
    // If one of the positions returns true, then return true

    // north
    cout << "\nTrying north, ";
    if (solveMazeRecursivePrint(row-1,col,maze)) {
        return true;
    }
    cout << " Back at row=" << row << " and col=" << col << ",";

    // east
    cout << "\nTrying east, ";
    if (solveMazeRecursivePrint(row,col+1,maze)) {
        return true;
    }
    cout << " Back at row=" << row << " and col=" << col << ",";


    // south
    cout << "\nTrying south, ";
    if (solveMazeRecursivePrint(row+1,col,maze)) {
        return true;
    }
    cout << " Back at row=" << row << " and col=" << col << ",";

    // west
    cout << "\nTrying west, ";
    if (solveMazeRecursivePrint(row,col-1,maze)) {
        return true;
    }
    cout << " Back at row=" << row << " and col=" << col << ",";

    cout << "\nFailed. Marking bad path with b.";
    maze[row][col] = 'b';
    return false;
}
void initMaze(Grid<int> &maze, int sideLength) {
    maze.resize(sideLength*2+1,sideLength*2+1); // room for walls
    for(int a = 0; a < maze.numRows(); a++)
    {
        for(int b = 0; b < maze.numCols(); b++)
        {
            if(a % 2 == 0 || b % 2 == 0)
                maze[a][b] = 1;
            else
                maze[a][b] = PATH;
        }
    }
}

// generates a maze
void generateMaze(Grid <int> &maze, int sideLength){
    int index = 0;
    int backtrackX[MAXCELL];
    int backtrackY[MAXCELL];
    backtrackX[index] = 1;
    backtrackY[index] = 1;
    mazeGenerator(index, backtrackX, backtrackY, 1, 1, sideLength,
                   1, maze);
    // make human readable
    humanReadableMaze(maze);
}

void mazeGenerator(int index, int backtrackX[MAXCELL],
        int backtrackY[MAXCELL],
        int x, int y, int n, int visited, Grid<int> &maze)
{
    if(visited < n * n)
    {
        int neighbourValid = -1;
        int neighbourX[4];
        int neighbourY[4];
        int step[4];

        int xNext;
        int yNext;

        if(x - 2 > 0 && isClosed(x - 2, y,maze))  // upside
        {
            neighbourValid++;
            neighbourX[neighbourValid]=x - 2;;
            neighbourY[neighbourValid]=y;
            step[neighbourValid]=1;
        }

        if(y - 2 > 0 && isClosed(x, y - 2, maze))  // leftside
        {
            neighbourValid++;
            neighbourX[neighbourValid]=x;
            neighbourY[neighbourValid]=y - 2;
            step[neighbourValid]=2;
        }

        if(y + 2 < n * 2 + 1 && isClosed(x, y + 2, maze))  // rightside
        {
            neighbourValid++;
            neighbourX[neighbourValid]=x;
            neighbourY[neighbourValid]=y + 2;
            step[neighbourValid]=3;

        }

        if(x + 2 < n * 2 + 1 && isClosed(x + 2, y, maze))  // downside
        {
            neighbourValid++;
            neighbourX[neighbourValid]=x+2;
            neighbourY[neighbourValid]=y;
            step[neighbourValid]=4;
        }

        if(neighbourValid == -1)
        {
            // backtrack
            xNext = backtrackX[index];
            yNext = backtrackY[index];
            index--;
        }

        if(neighbourValid!=-1)
        {
            int randomization = neighbourValid + 1;
            int random = rand()%randomization;
            xNext = neighbourX[random];
            yNext = neighbourY[random];

            index++;
            backtrackX[index] = xNext;
            backtrackY[index] = yNext;

            int rstep = step[random];

            if(rstep == 1)
                maze[xNext+1][yNext] = PATH;
            else if(rstep == 2)
                maze[xNext][yNext + 1] = PATH;
            else if(rstep == 3)
                maze[xNext][yNext - 1] = PATH;
            else if(rstep == 4)
                maze[xNext - 1][yNext] = PATH;
            visited++;
        }

        mazeGenerator(index, backtrackX, backtrackY,xNext,yNext,
                n, visited, maze);
    }
}

void printMaze(Grid <int> &maze)
{
    for(int a = 0; a < maze.numRows(); a++)
    {
        for(int b = 0; b < maze.numCols(); b++)
        {
            cout << (char) maze[a][b];
        }
        cout << endl;
    }
    cout << endl;
}

void humanReadableMaze(Grid <int> &maze)
{
    for(int a = 0; a < maze.numRows(); a++)
    {
        for(int b = 0; b < maze.numCols(); b++)
        {
            if (a==1 && b==1)
                maze[a][b]='S'; // the start location
            else if (a==maze.numCols() - 2 &&
                    b==maze.numRows()-2){
                // the finish location
                maze[a][b]='F';
            }
            else if(maze[a][b] == WALL)
                maze[a][b]='X';
            else
                maze[a][b]=' ';
        }
    }
}

int isClosed(int x, int y, Grid<int> &maze)
{
    if(maze[x - 1][y]  == WALL
            && maze[x][y - 1] == WALL
            && maze[x][y + 1] == WALL
            && maze[x + 1][y] == WALL
    )
        return 1;

    return 0;
}
