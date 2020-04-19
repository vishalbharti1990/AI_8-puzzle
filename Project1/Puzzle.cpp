#include "Puzzle.h"

Puzzle::Puzzle() {
	int goal[9] = { 1, 2, 3, 8, 0, 4, 7, 6, 5 };		//Puzzle goal state.

	for (int i = 0; i < 9; ++i)
		goalPuzzle.push_back(goal[i]);					//stores goal in goalPuzzle vector of puzzle class
}

Puzzle::Puzzle(Puzzle &ptmp) {
	for (int i = 0; i < 9; ++i) {
		puzzle.push_back(ptmp.puzzle[i]);
		goalPuzzle.push_back(ptmp.goalPuzzle[i]);
	}
}

/*----------------------------------------------/
		Prints board's tile layout
-----------------------------------------------*/

void Puzzle::dispPuzzle() {
	for (int i = 0; i < 9; ++i) {
		if (i % 3 == 0)
			printf("\n");
		printf("%i  ", puzzle[i]);
	}
	printf("\n\n");
}


/*-----------------------------------------------/
Converts the puzzle board layout to a string form
/-----------------------------------------------*/
std::string Puzzle::puzzToStr() {
	std::string val;
	for (int i = 0; i < 9; ++i)
		val += std::to_string(puzzle[i]);
	return val;
}


/*----------------------------------------------/
Returns the index of the blank tile
/----------------------------------------------*/

int Puzzle::getBlankInd() {
	for (int i = 0; i < 9; ++i)
		if (puzzle[i] == 0)
			return i;
	return NULL;
}\

/*-----------------------------------------------/
Returns the manhattan distances of all tiles 
on the board by comparing them to the goal state
/-----------------------------------------------*/

int Puzzle::manDist() {
	int tmp;
	int d = 0;
	for (int i = 0; i < 9; ++i) {
		tmp = goalPuzzle[i];
		for (int j = 0; j < 9; ++j) {
			if (puzzle[j] == tmp)
				d += abs(floor(i / 3) - floor(j / 3)) + abs((i % 3) - (j % 3));
		}
	}
	return d;
}


/*--------------------------------------------------/
Returns the number of tiles that are misplaced by 
comparing it to the goal state
/--------------------------------------------------*/
int Puzzle::mispTiles() {
	int misTiles = 0;

	for (int i = 0; i < 9; i++) {
		if (goalPuzzle[i] == 0)
			continue;
		if (puzzle[i] != goalPuzzle[i])
			++misTiles;
	}
	return misTiles;
}

/*-----------------------------------------------------/
				Clears the Puzzle 
/-----------------------------------------------------*/
void Puzzle::resetPuzzle() {
	if (!puzzle.empty()) {
		for (int i = 0; i < 9; ++i)
			puzzle.pop_back();
	}
}

/*----------------------------------------------------/
		Returns an easy puzzle layout
/----------------------------------------------------*/
void Puzzle::easyPuzzle() {
	resetPuzzle();
	int puzz[9] = { 1, 3, 4, 8, 6, 2, 7, 0, 5 };

	for (int i = 0; i < 9; ++i)
		puzzle.push_back(puzz[i]);
}

/*----------------------------------------------------/
		Returns an medium puzzle layout
/----------------------------------------------------*/
void Puzzle::mediumPuzzle() {
	resetPuzzle();
	int puzz[9] = { 2, 8, 1, 0, 4, 3, 7, 6, 5 };

	for (int i = 0; i < 9; ++i)
		puzzle.push_back(puzz[i]);
}

/*----------------------------------------------------/
		Returns an hard puzzle layout
/----------------------------------------------------*/
void Puzzle::hardPuzzle() {
	resetPuzzle();
	int puzz[9] = { 2, 8, 1, 4, 6, 3, 0, 7, 5 };

	for (int i = 0; i < 9; ++i)
		puzzle.push_back(puzz[i]);
}

/*----------------------------------------------------/
		Returns an worst puzzle layout
/----------------------------------------------------*/
void Puzzle::worstPuzzle() {
	resetPuzzle();
	int puzz[9] = { 5, 6, 7, 4, 0, 8, 3, 2, 1 };

	for (int i = 0; i < 9; ++i)
		puzzle.push_back(puzz[i]);
}


/*-------------------------------------------------------------/
Compares the current state to the Goal state and returns
			false if any tiles are misplaced
/-------------------------------------------------------------*/

bool Puzzle::isSolved() {
	if (puzzle == goalPuzzle)
		return true;
	return false;
}



/*--------------------------------------------------------------/
 Moves a source tile to a specified destination in the Board 
/--------------------------------------------------------------*/

Puzzle Puzzle::moveTile(int index, int destination) {
	Puzzle tmp(*this);			//makes a copy using the copy Constructor
	tmp.puzzle[index] = puzzle[destination];
	tmp.puzzle[destination] = puzzle[index];
	return tmp;
}
