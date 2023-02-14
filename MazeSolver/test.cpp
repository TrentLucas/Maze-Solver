// test.cpp
// test file for homework04
//////////////////////////////

#include <iostream>
#include <fstream>
#include "maze.h"



int setArray( int * myArray, const char * pfilename) {
	int length = 0; 
	int x;

	std::fstream myfile;
	myfile.open( pfilename);

	while (myfile >> x) {
		myArray[length] = x;
		length++;
	}

	return (length);
}



int main () {
	char file_name[100];
	int array[4];
	int length;


	// file request
	std::cout << "Enter file name to read: ";
	std::cin >> file_name;
	std::cout << std::endl;

	// read first line to get row, col, and start coordinates
	length = setArray(array, file_name);

	// initialize maze object with row, col, start coordinates, and file
	Maze a1(array[0], array[1], array[2], array[3], file_name);

	// test for maze.cpp
	a1.solve();
}

