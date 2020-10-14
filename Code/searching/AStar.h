#ifndef astar_h
#define astar_h

#include <map>
#include <vector>
#include "Node.h"

using namespace std;


class AStar {

public:

	// Search the path using AStar iterative algorithm
	bool searchList(map<int, Node *> &adjacencyList, int startNodeId, int destinationNodeId, vector<int>& pathIds, int& numExploredNodes) const;

	// Search the path using AStar matrix,
	// NOTE: THE ADJACENCY LIST HERE IS ONLY USED FOR IDENTIFYING THE X,Y, and Z of a node AND NOT BEING USED IN THE ACTUAL ALGORITHM
	bool searchMatrix(vector< vector<double> >& adjacencyMatrix, map<int, Node *>& adjacencyList, 
		int startNodeId, int destinationNodeId, vector<int>& pathIds, int& numExploredNodes);

private:

	// Calculate distance between 2 nodes
	double euclideanDistance(Node* fromNode, Node* toNode) const;
};

#endif
