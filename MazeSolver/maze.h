// homework04
// maze.h
//
// In this file are constructors, destructors, and functions
// for Maze and MazeElement classes.
//
// The code iterates through the maze
// to find the shortest distance to the end.
//
// Then goes back from the end cell to the start cell 
// using the distances found travelling to each cell.
////////////////////////////////////////////////////////////////////

#ifndef MAZE_H
#define MAZE_H

class MazeElement {
	public:
		// constructors
		MazeElement();
		
		// functions
		void setValue( char val);
		char getValue() const;
		void setVisited();
		bool getVisited() const;
		void setDistance( int dist);
		int getDistance() const;
		bool getIsWall() const;
		bool getIsEnd() const;


	private:
		// variables
		bool isWall;
		bool isEnd;
		char value;
		int distance;
		bool visited;
};

class Maze {
	public:
		// constructors
		Maze(int row, int col, int startX, int startY, const char * pfilename);
		~Maze();


		// functions
		void solve();
		

	private:
		// functions
		void readMaze(const char * pfilename);
		void findEnd();
		void print();
		bool solve(int currR, int currC, int currD);
		bool solveEachDirection(int currR, int currC, int currD);
		void setPath(int currR, int currC);
		bool okToGo( int currR, int currC);

		// variables
		MazeElement ** maze;

		int row;
		int col;
		int startRow;
		int startCol;
		int endRow;
		int endCol;

	friend class MazeElement;
};

#endif
