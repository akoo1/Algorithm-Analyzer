#ifndef bfs_h
#define bfs_h

#include <map>
#include <vector>
#include <queue>
#include "Node.h"

using namespace std;


class BFS {

public:

	// Perform a breadth first search using adjacency list iterative algorithm
	bool searchListIterative(map<int, Node *>& adjacencyList, int startNodeId, int destinationNodeId, vector<int>& pathIds, int& numExploredNodes) const;

	// Perform a breadth first search using adjacency list recursive algorithm
	bool searchListRecursive(map<int, Node *>& adjacencyList, int startNodeId, int destinationNodeId, vector<int>& pathIds, int& numExploredNodes) const;

	// Perform a breadth first search using matrix iterative algorithm
	bool searchMatrixIterative(vector< vector<double> >& adjacencyMatrix, int startNodeId, int destinationNodeId, vector<int>& pathIds, int& numExploredNodes) const;

	// Perform a breadth first search using matrix recursive algorithm
	bool searchMatrixRecursive(vector< vector<double> >& adjacencyMatrix, int startNodeId, int destinationNodeId, vector<int>& pathIds, int& numExploredNodes) const;

private:

	// Recursively traverse the graph using breadth first search until the destination node is found
	bool searchListRecursiveHelper(map<int, Node *>& adjacencyList, int destinationNodeId,
		queue<int>& theQueue, vector<int>& visited, map<int, int>& parentNodeIds, int& numExploredNodes) const;

	// Recursively traverse the graph using breadth first search until the destination node is found
	bool searchMatrixRecursiveHelper(vector< vector<double> >& adjacencyMatrix, int destinationNodeId,
		queue<int>& theQueue, vector<int>& visited, map<int, int>& parentNodeIds, int& numExploredNodes) const;
};

#endif
