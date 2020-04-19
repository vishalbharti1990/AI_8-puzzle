#include <iostream>
#include <queue>
#include "searchMethod.h"
#include "Puzzle.h"
#include <vector>

using namespace std;

int main() {
	Puzzle p;
	searchMethod sM;
	char ans;

	int diff, search;
	bool inputDifficulty = true, inputSearch = true;

	while (inputDifficulty) {

		printf("Select the difficulty level of puzzle : \n1) Easy\n2) Medium\n3) Hard\n4) Worst\nSelect your answer: ");
		std::cin >> diff;
		printf("\n");
		while (diff < 1 || diff > 4) {
			printf("Please input a valid response.\nSelect the difficulty level of puzzle : \n1) Easy\n2) Medium\n3) Hard\n4) Worst\nSelect your answer: ");
			std::cin >> diff;
		}
		printf("\n");
		switch (diff) {
		case 1: p.easyPuzzle(); break;
		case 2: p.mediumPuzzle(); break;
		case 3: p.hardPuzzle(); break;
		case 4: p.worstPuzzle(); break;
		}
		inputSearch = true;

		while (inputSearch) {
			printf("Select the search method to use :\n1) A* Search (tiles out of place heuristic)\n2) A* Search (Manhattan Block Heuristic)\n3) Depth first Branch and Bound\n4) Iterative Deepening A*\n5) Return to Previous Menu.\n6) Exit\nEnter your choice : ");
			std::cin >> search;
			printf("\n");

			while (search < 1 || search > 7) { 
				printf("\nEnter a valid response....\nSelect the search method to use : \n1) A* Search(tiles out of place heuristic)\n2) A* Search(Manhattan Block Heuristic)\n3) Depth first Branch and Bound\n4) Iterative Deepening A*\n5) Return to Previous Menu.\n6) Exit\nEnter your choice : ");
				std::cin >> search;
				printf("\n");
			}
			sM.rMapClear();

			switch (search) {
			case 1: sM.AStarMT(p); break;
			case 2: sM.AStarManDis(p); break;
			case 3: sM.DFSBNB(p); break;
			case 4: sM.IDAStar(p); break;
			case 5: inputSearch = false; break;
			case 6: return 0;
			}

			if (inputSearch == true) {
				printf("Show steps ('Y'||'y'(yes)/'N'||'n'(no)) : ");
				std::cin >> ans;
				if(ans == 'Y' || ans == 'y')
					sM.showSteps();
			}

			inputSearch = false;
		}
	}
	return 0;
}