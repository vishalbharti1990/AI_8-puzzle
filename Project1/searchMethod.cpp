#include "searchMethod.h"
#include <vector>

/*-----------------------------------------------------/
To Find all possible nodes that could be derived from
the parent node and save them as parent node's Children
/----------------------------------------------------*/

void searchMethod::expand(Node *parent) {
	if (parent->zeroIndex % 3 == 0)				//finds all possible childs if zero tile is in column 0
		parent->children.push_back(new Node(parent->depth + 1, parent->puzz.moveTile(parent->zeroIndex, parent->zeroIndex + 1), parent->zeroIndex + 1, parent));
	else if (parent->zeroIndex % 3 == 1) {		//finds all possible childs if zero tile is in column 1
		parent->children.push_back(new Node(parent->depth + 1, parent->puzz.moveTile(parent->zeroIndex, parent->zeroIndex - 1), parent->zeroIndex - 1, parent));
		parent->children.push_back(new Node(parent->depth + 1, parent->puzz.moveTile(parent->zeroIndex, parent->zeroIndex + 1), parent->zeroIndex + 1, parent));
	}
	else                                        //finds all possible childs if zero tile is in column 2 
		parent->children.push_back(new Node(parent->depth + 1, parent->puzz.moveTile(parent->zeroIndex, parent->zeroIndex - 1), parent->zeroIndex - 1, parent));

	if (parent->zeroIndex < 3)				//finds all possible childs if zero tile is in row 0
		parent->children.push_back(new Node(parent->depth + 1, parent->puzz.moveTile(parent->zeroIndex, parent->zeroIndex + 3), parent->zeroIndex + 3, parent));
	else if (parent->zeroIndex < 6) {		//finds all possible childs if zero tile is in row 1
		parent->children.push_back(new Node(parent->depth + 1, parent->puzz.moveTile(parent->zeroIndex, parent->zeroIndex - 3), parent->zeroIndex - 3, parent));
		parent->children.push_back(new Node(parent->depth + 1, parent->puzz.moveTile(parent->zeroIndex, parent->zeroIndex + 3), parent->zeroIndex + 3, parent));
	}
	else                                    //finds all possible childs if zero tile is in column 2
		parent->children.push_back(new Node(parent->depth + 1, parent->puzz.moveTile(parent->zeroIndex, parent->zeroIndex - 3), parent->zeroIndex - 3, parent));
}


/*------------------------------------------------------/
Checks if the current arrangement of tiles is a
			repetition or not
/------------------------------------------------------*/

bool searchMethod::isRepeat(std::string puzzle) {
	if (repMap.find(puzzle) != repMap.end())
		return true;
	return false;
}


/*-----------------------------------------------------/
Backtracks from Current-state to the starting state and 
prints the path from starting state to the current state
/----------------------------------------------------*/

void searchMethod::showSteps() {
	if (answerNode != NULL) {
		std::vector<Node *> path;
		Node *tmp = answerNode;
		while (tmp != NULL) {
			path.push_back(tmp);
			tmp = tmp->parent;
		}

		for (int i = path.size() - 1; i >= 0; --i)
			(path[i]->puzz).dispPuzzle();
	}
}


/*----------------------------------------------------------/
Prints the max nodes, time taken and depth of tree for each
Method
/----------------------------------------------------------*/

void searchMethod::showStats(int depth, double time, int maxHeld) {
	printf("The solution was found at depth %i. \nThe time taken to find the solution was %.0f milliseconds.\nThe number of nodes expanded : %i nodes.\n\n", depth, time, maxHeld);
}


/*--------------------------------------------------/
Clears the unordered map used to check for repeats
/--------------------------------------------------*/

void searchMethod::rMapClear() {
	repMap.clear();
}


/*-----------------------------------------------------------------------------/
								A* Search
							Heuristics : Misplaced Tiles
/-----------------------------------------------------------------------------*/

void searchMethod::AStarMT(Puzzle puzz) {
	start = clock();		//start the timer

	std::priority_queue<Node *, std::vector<Node *>, comp> q;		//priority queue sorted according to condition comp i.e. a->f > b->f then b has higher priority

	Node *node = new Node(0, puzz, puzz.getBlankInd());			//Creates a board with the given puzzle config
	node->cost = node->puzz.mispTiles() + node->depth;			//Calculate the cost of parent node or the start state Node

	q.push(node);	//Push to the front of the queue

	maxNodes = 1;	//To store the max Nodes expanded

	repMap.insert(std::pair<std::string, Node *>((node->puzz).puzzToStr(), node));		//insert the parent node to the unordered map for checking repeats

	while (!q.empty()) {		//continue while q is not empty
		node = q.top();			//extract the node on top of the priority queue, i.e. one with least cost
		q.pop();				//pop the node from the queue

		if ((node->puzz).isSolved()) {     //check if node being examined is the answer
			answerNode = node;			//saves answer's pointer to print out later

			finish = clock();			//Captures the finish time
			totalTime = (finish - start) * 1000.0 / CLOCKS_PER_SEC;	//Calculates the time taken for the process to finish
			showStats(node->depth, totalTime, maxNodes);			//reports statistics.

			return;
		}

		expand(node);		//expands the Node and generates the children nodes, i.e. the puzzle states resulting by making valid tile moves.
		maxNodes++;			// Max Nodes expanded ++

		for (unsigned int i = 0; i < (node)->children.size(); ++i) {	//look at all of the saved node's children
			if (!isRepeat((node->children[i])->puzz.puzzToStr())) {	//If the child was not the answer, check to make sure it is not a repeat
				repMap.insert(std::pair<std::string, Node *>((node->children[i])->puzz.puzzToStr(), node->children[i])); //Since it is not a repeat, add it to the has-seen map
				(node->children[i])->cost = (node->children[i])->puzz.mispTiles() + (node->children[i])->depth;	//f(x) = g(x) + h(x). f(x) (cost) = misplaced Tiles + depth of child Node
				q.push(node->children[i]);	//Push onto the priority queue
			}
		}
	}
	printf("Could not find a solution.\n");
}

/*-----------------------------------------------------------------------------/
									A* Search
							Heuristics : Manhattan Distance
/-----------------------------------------------------------------------------*/

void searchMethod::AStarManDis(Puzzle puzz) {
	start = clock();			//start the timer

	std::priority_queue<Node *, std::vector<Node *>, comp> q;		//Priority queue that stores the Nodes in order of their Cost

	Node *node = new Node(0, puzz, puzz.getBlankInd());				//Creates a board with the given puzzle config
	node->cost = node->puzz.manDist() + node->depth;				//Calculate the cost of parent node or the start state Node

	q.push(node);	//Push to the front of the queue

	maxNodes = 1;	//To store the max Nodes expanded

	repMap.insert(std::pair<std::string, Node *>((node->puzz).puzzToStr(), node));		//insert the parent node to the unordered map for checking repeats

	while (!q.empty()) {	//continue while q is not empty
		node = q.top();		//extract the node on top of the priority queue, i.e. one with least cost
		q.pop();			//pop the node from the queue

		if ((node->puzz).isSolved()) {     //check if node being examined is the answer
			answerNode = node;			//saves answer's pointer to print out later

			finish = clock();			//Captures the finish time
			totalTime = (finish - start) * 1000.0 / CLOCKS_PER_SEC;	//Calculates the time taken for the process to finish
			showStats(node->depth, totalTime, maxNodes);			//reports statistics.

			return;
		}
		expand(node);		//expands the Node and generates the children nodes, i.e. the puzzle states resulting by making valid tile moves.
		maxNodes++;			// Max Nodes expanded ++

		for (unsigned int i = 0; i < (node)->children.size(); ++i) {	//look at all of the saved node's children
			if (!isRepeat((node->children[i])->puzz.puzzToStr())) {	//If the child was not the answer, check to make sure it is not a repeat
				repMap.insert(std::pair<std::string, Node *>((node->children[i])->puzz.puzzToStr(), node->children[i])); //Since it is not a repeat, add it to the has-seen map
				(node->children[i])->cost = (node->children[i])->puzz.manDist() + (node->children[i])->depth;	//f(x) = g(x) + h(x). f(x) (cost) = manhattan Distance + depth of child Node
				q.push(node->children[i]);	//Push onto the priority queue
			}
		}
	}
	printf("Could not find a solution.\n");
}


/*-----------------------------------------------------------------------------/
						 DFS branch and bound Search
						 Heuristics : Manhattan Distance
/-----------------------------------------------------------------------------*/

void searchMethod::DFSBNB(Puzzle puzz) {
	start = clock();		//start the timer

	clock_t fTime;		//To store the clock time when we reach the optimum solution

	double finTime;		//To store the clock time when the algorithm terminates

	std::deque<Node *> q;	//Open list

	bool solved = false;	//To store current status of answer

	Node *tmp;				//tmp node to store state of puzzle, used while sorting child nodes based on the cost.

	Node *node = new Node(0, puzz, puzz.getBlankInd());		//Creates a board with the given puzzle config
	node->cost = node->puzz.manDist() + node->depth;		//Calculate the cost of parent node or the start state

	int best_ansCost = LONG_MAX;							//Initial cost set to infinity
	int depth;

	q.push_front(node);			//Push to the front of the queue

	maxNodes = 1;				//To store the max nodes expanded

	repMap.insert(std::pair<std::string, Node *>((node->puzz).puzzToStr(), node));		//insert the parent node to the unordered map for checking repeats

	while (!q.empty()) {		//Continue while the Open list is empty
		node = q.front();		//Extract the node currently on top of the Open list 
		q.pop_front();			//Remove the node

		if (((node->puzz).isSolved()) && (node->cost) < best_ansCost)  {     //check if node being examined is the answer
			answerNode = node;			//saves answer's pointer to print out later
			best_ansCost = node->cost;	//Update the current best cost

			finish = clock();			//Capture the finish time

			repMap.clear();				//Clear the repeat map

			totalTime = (finish - start) * 1000.0 / CLOCKS_PER_SEC;		//Calculate the time to reach the current best solution (Updated each time a new best solution reached)
			solved = true;			//Update solved status									
			depth = node->depth;	//gets the depth of the solution
		} 
		else {
			expand(node);				//expands the current node
			maxNodes++;					//Max Node Expanded ++ 

			for (unsigned int i = 0; i < (node)->children.size(); ++i) {	//look at all of the node's children		
				(node->children[i])->cost = (node->children[i])->puzz.manDist() + (node->children[i])->depth;	//f(x) = g(x) + h(x). f(x) (Cost) = manhattan Distance + depth of child Node
				if ((!(isRepeat((node->children[i])->puzz.puzzToStr()))) && ((node->children[i])->cost < best_ansCost)) {	//Checks if the child is a repeat and does not offer a better solution
						repMap.insert(std::pair<std::string, Node *>((node->children[i])->puzz.puzzToStr(), node->children[i])); //Add it to the repetition check mapper
					
					/*-----------------------------------------------------------------/
					  To store the nodes in the queue such that the one with lowest cost
					               is in the front of the Open list
					 /----------------------------------------------------------------*/
					if (i == 0)
						q.push_front(node->children[i]);	// For first child we just push it to the front of the Open list
					else if ((q.front())->cost <= (node->children[i])->cost) {	//else we check if the child has higher cost as compared to the last child
						tmp = q.front();		//store the last child as tmp node
						q.pop_front();			//pop the last node
						q.push_front(node->children[i]);	//insert the current node
						q.push_front(tmp);			//insert the last node
					}
					else
						q.push_front(node->children[i]);	//If not, just push the child to the front of the Open list
				}
			}
		}
	}
	if (solved) {
		fTime = clock();		//Capture the time for the algorithm to terminate
		finTime = (fTime - start) * 1000.0 / CLOCKS_PER_SEC;	//Calculates the time taken for the Algorithm to terminate
		showStats(depth, totalTime, maxNodes);			//reports statistics.

		printf("\nTime taken by search to terminate = %f \n", finTime);		//Prints the time taken by the algorithm
		
		return;
	}
	printf("Could not find a solution.\n");
}

/*----------------------------------------------------------------/
					Iterative Deepening A*
				Heuristics : Manhattan Distance
/----------------------------------------------------------------*/


void searchMethod::IDAStar(Puzzle puzz) {
	start = clock();		//start the timer

	std::deque<Node *> q;		//open list

	std::vector<int> lCost;		//Vector to store the cost of all nodes expanded. The vector is sorted and then the least cost is updated as the bound cost

	Node *node = new Node(0, puzz, puzz.getBlankInd());			//Creates a board with the given puzzle config
	node->cost = node->puzz.manDist() + node->depth;			//Calculate the cost of parent node or the start state

	int bound_Cost = node->cost;			//initially the bound is set to the cost of start state		

	q.push_front(node);	//Push to the front of the queue

	maxNodes = 1;		//To store the max nodes expanded

	repMap.insert(std::pair<std::string, Node *>((node->puzz).puzzToStr(), node));		//insert the parent node to the unordered map for checking repeats

	while (true) {		//Infinite loop
		node = q.front();		//Extract the node currently on top of the Open list
		q.pop_front();			//Remove the node

		if ((node->puzz).isSolved()) {     //check if node being examined is the answer
			answerNode = node;			//saves answer's pointer to print out later

			finish = clock();			//Extraxt the finish time
			totalTime = (finish - start) * 1000.0 / CLOCKS_PER_SEC;	//Calculates the time taken for the process to finish
			showStats(node->depth, totalTime, maxNodes);			//reports statistics.

			return;					//The infinite loop breaks when the solution is found
		}

		expand(node);				//expands the current node
		maxNodes++;					//Max Nodes Expanded ++

		for (unsigned int i = 0; i < (node)->children.size(); ++i) {	//look at all of the saved node's children
			(node->children[i])->cost = (node->children[i])->puzz.manDist() + (node->children[i])->depth;	//f(x) = g(x) + h(x). f(x) (cost) = manhattan Distance + depth of child Node

			if (((node->children[i])->cost) <= bound_Cost) {	
				q.push_front(node->children[i]);	//Push to the front of queue only if the cost is lessor or equal to the current best
			}
			if (((node->children[i])->cost) > bound_Cost) {		//To store cost of all children Node in lCost vector if their cost is greater than bound
				lCost.push_back((node->children[i])->cost);		//Later used to get the minimum of the cost of all children nodes, which is then updated
			}													//as new cost bound
		}

		if (q.empty()) {		//q gets empty if we finish traversing the tree for current cost bound
			node = new Node(0, puzz, puzz.getBlankInd());	//Re-creates starting state
			node->cost = node->puzz.manDist() + node->depth;	//cost of the starting state
			q.push_front(node);			//Push to the front of the queue q

			if (lCost.size()) {		//If lCost vector is not empty
				auto res = std::min_element(lCost.begin(), lCost.end());		//get the address of minimum cost in the vector of children costs
				bound_Cost = *res;				//Update bound cost
				lCost.clear();					//clear the vector
			}
		}
	}
}