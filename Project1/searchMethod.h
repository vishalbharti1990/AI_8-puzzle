#ifndef _searchMethods
#define _searchMethods

#include <vector>
#include <deque>
#include <unordered_map>
#include <queue>
#include <string>
#include <ctime>
#include "Puzzle.h"

class searchMethod {
public:
	struct Node {
		Node(int d, Puzzle p, int zIndex, Node *Par = NULL) {
			puzz = p;
			depth = d;
			parent = Par;
			zeroIndex = zIndex;
		};
		int depth;
		std::vector<Node *> children;
		Node *parent;
		Puzzle puzz;
		int zeroIndex;
		int manDist;
		int cost;
	};

	struct comp {
		bool operator()(Node *a, Node *b) {
			return a->cost > b->cost;
		}
	};

	bool isRepeat(std::string puzzle);
	void showSteps();
	void showStats(int depth, double time, int queNodes);

	void AStarMT(Puzzle puzz);
	void AStarManDis(Puzzle puzz);
	void DFSBNB(Puzzle puzz);
	void IDAStar(Puzzle puzz);

	void rMapClear();

	void expand(Node* parent);

private:
	std::unordered_map<std::string, Node *> repMap;
	Node *answerNode;

	clock_t start;
	clock_t finish;
	unsigned int maxNodes;
	double totalTime;
};

#endif
