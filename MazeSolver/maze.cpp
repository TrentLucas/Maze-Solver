// maze.cpp
// constructors, destructors, and functions for MazeElement and Maze
///////////////////////

#include "maze.h"
#include <iostream>
#include <fstream>
#include <climits>



///////////////////////////////////////////////////////
//  				          	     //
//                 MazeElement Class                 //
//                                                   //
///////////////////////////////////////////////////////



// Constructor: empty cell
MazeElement::MazeElement() {
	distance = 0;
	visited = false;
	isWall = false;
	isEnd = false;
}

//////////////////////////////////////////
// *value* setter and getter
//////////////////////////////////////////
void MazeElement::setValue( char val) { 
	value = val;

	if (value == '#') {
		isWall = true;
	}

	else if (value == 'o') {
		isEnd = true;
	}
}

char MazeElement::getValue() const { 
	return value;
}

//////////////////////////////////////////
// *visited* setter and getter
//////////////////////////////////////////
void MazeElement::setVisited() {
	visited = true;
}

bool MazeElement::getVisited() const {
	return visited;
}

//////////////////////////////////////////
// *distance* setters and getter
//////////////////////////////////////////
void MazeElement::setDistance(int dist) {
	distance = dist;
}

int MazeElement::getDistance() const {
	return distance;
}

//////////////////////////////////////////
// *isWall* getter
//////////////////////////////////////////
bool MazeElement::getIsWall() const {
	return isWall;
}

//////////////////////////////////////////
// *isEnd* getter
//////////////////////////////////////////
bool MazeElement::getIsEnd() const {
	return isEnd;
}



///////////////////////////////////////////////////////
//  			                  	     //
//                    Maze Class                     //
//                                                   //
///////////////////////////////////////////////////////



// Constructor
Maze::Maze(int tempRow, int tempCol, int tempSRow, int tempSCol, const char * pfilename) {

	// create empty 2D maze array
	maze = new MazeElement*[tempRow];
	for (int i = 0; i < tempRow; i++) {

		maze[i] = new MazeElement[tempCol];
	}
	
	// set variables
	row = tempRow;
	col = tempCol;
	startRow = tempSRow;
	startCol = tempSCol;

	readMaze(pfilename);
}

// Destructor
Maze::~Maze() {

	// delete all elements in 2D maze array
	for (int i = 0; i < row; i++) {

		delete [] maze[i];
	}

	delete [] maze;
}

//////////////////////////////////////////
// read all of the lines in the input file
// besides the first row. put each character
// into the maze[][].
//////////////////////////////////////////
void Maze::readMaze(const char * pfilename) {
	int x;
	std::string line = " ";

	std::fstream myfile;
	myfile.open( pfilename);
	
	// skip first line
	getline(myfile, line);

	// read each character in file and 
	// assign to correct spot in 2D maze array
	for (int i = 0; i < row; i++) {
		getline(myfile, line);

		for (int j = 0; j < col; j++) {
			maze[i][j].setValue(line [j]);
		}
	}

	findEnd();
}

//////////////////////////////////////////
// find the end cell
// if there is no end cell 
// return and end run time
//////////////////////////////////////////
void Maze::findEnd() {

	// check through 2D maze array for 'o'
	for (int i = 0; i < row; i++) {

		for (int j = 0; j < col; j++) {

			if (maze[i][j].getIsEnd()) {
				endRow = i;
				endCol = j;

				return;
			}
		}
	}

	std::cout << "No end cell found" << std::endl;
}

//////////////////////////////////////////
// print the entire maze
//////////////////////////////////////////
void Maze::print() {

	// print each row in 2D maze array
	for (int i = 0; i < row; i++) {

		for (int j = 0; j < col; j++) {
			std::cout << maze[i][j].getValue();
		}

		std::cout << std::endl;
	}

	std::cout << std::endl;
}

//////////////////////////////////////////
// okToGo. check if cell is in the maze boundaries
// and if the cell is a wall
//
// if in maze and not a wall: return true
// else: return false
//////////////////////////////////////////
bool Maze::okToGo(int currR, int currC) {

	// check if the cell is in the maze and not a wall
	if (currR < row && currC < col && currR >= 0 && currC >= 0 && !maze[currR][currC].getIsWall()) {
		return true;
	}

	return false;
}

//////////////////////////////////////////
// solve call from the test file
//////////////////////////////////////////
void Maze::solve() {

	if ( solve(startRow, startCol, 0)) {
		setPath(endRow, endCol);
		print();
	} 
}

//////////////////////////////////////////
// private solve function
// recursively goes through each element in the maze marking 
// the length to get to that cell from the start
// if at the end element, end recursion
//////////////////////////////////////////
bool Maze::solve(int currR, int currC, int currD) {

	if (okToGo(currR, currC)) {

		if (maze[currR][currC].getVisited() == true) {

			// if currD is less than the distance of the current maze element
				if (currD < maze[currR][currC].getDistance()) {

				// set currD as the distance of the current maze element
				maze[currR][currC].setDistance(currD);

				if (solveEachDirection(currR, currC, currD)) {
					return true;
				}	
			} 
			
			// if currD is greater than/equal to the distance of the current maze element
			else {
				--currD;
				return false;
			}
		}
		
		// if current maze element is not visited
		else {

			// mark as visited and set distance
			maze[currR][currC].setDistance(currD);
			maze[currR][currC].setVisited();

			if (solveEachDirection(currR, currC, currD)) {
				return true;
			}

		} 
		
		// if maze element is the end element
		if (maze[currR][currC].getIsEnd()) {
			return true;
		}
	}

	return false;
}


//////////////////////////////////////////
// check each direction if a path is possible
//////////////////////////////////////////
bool Maze::solveEachDirection(int currR, int currC, int currD) {
	bool north = solve(currR - 1, currC, currD + 1);
	bool east = solve(currR, currC + 1, currD + 1);
	bool south = solve(currR + 1, currC, currD + 1);
	bool west = solve(currR, currC - 1, currD + 1);

	// if there is a path possible in any direction
	if (north || east || south || west) {
		return true;
	} 

	--currD;
	return false;
		
}

//////////////////////////////////////////
// set the path through the maze starting at the end cell
// find the shortest path back to the start
// by comparing the distances of the current cell
// and the next cell
// if at the start cell, end recursion
//////////////////////////////////////////
void Maze::setPath(int currR, int currC) {

	// base case
	if (currR == startRow && currC == startCol) {
		return;
	}
	
	// check the next maze element to see if it's on the path 
	// and it's distance is currD - 1
	if (okToGo(currR - 1, currC)) {
		// north
		if (maze[currR - 1][currC].getDistance() + 1 == maze[currR][currC].getDistance() && maze[currR - 1][currC].getVisited() == true) {
			maze[currR - 1][currC].setValue('.');

			return setPath(currR - 1, currC);
		}
	}

	if (okToGo(currR, currC + 1)) {
		// east
		if (maze[currR][currC + 1].getDistance() + 1 == maze[currR][currC].getDistance() && maze[currR][currC + 1].getVisited() == true) {
			maze[currR][currC + 1].setValue('.');

			return setPath(currR, currC + 1);
		}
	}

	if (okToGo(currR + 1, currC)) {
		// south
		if (maze[currR + 1][currC].getDistance() + 1 == maze[currR][currC].getDistance() && maze[currR + 1][currC].getVisited() == true) {
			maze[currR + 1][currC].setValue('.');

			return setPath(currR + 1, currC);
		}
	}

	if (okToGo(currR, currC - 1)) {
		// west
		if (maze[currR][currC - 1].getDistance() + 1 == maze[currR][currC].getDistance() && maze[currR][currC - 1].getVisited() == true) {
			maze[currR][currC - 1].setValue('.');

			return setPath(currR, currC - 1);
		}
	}
}
