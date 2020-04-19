#ifndef _Puzzle
#define _Puzzle

#include <iostream>
#include <vector>
#include <string>

class Puzzle {
private: 
	std::vector<int> puzzle;						// Stores starting state
	std::vector<int> goalPuzzle;				// Stores the Goal state

public:
	void dispPuzzle();				//displays the current puzzle board

	Puzzle();									//Constructor
	Puzzle(Puzzle &);							//Copy Constructor
	~Puzzle(){}									//Destructor

	void resetPuzzle();							//clears the Puzzle
	void easyPuzzle();							//make the board with "Easy" config
	void mediumPuzzle();						//make the board with "Medium" config
	void hardPuzzle();							//make the board with "hard" config
	void worstPuzzle();							//make the board with "Worst" config

	int getBlankInd();							//Returns the index of the empty tile
	int manDist();								//Returns the manhattan distances of the Board
	int mispTiles();							//Returns the number of tiles that are misplaced as compared to goal state

	std::string puzzToStr();					//Turns the tile arrangement into a single string. Later used to check for repeats

	bool isSolved();							//Checks if current Board == goal state
	Puzzle moveTile(int index, int destination);  //Move a tiles from specified index to specified destination
};


#endif
