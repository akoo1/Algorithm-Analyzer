#ifndef dfs_h
#define dfs_h

#include <map>
#include <vector>
#include "Node.h"

using namespace std;


class DFS
{
public:

	// Perform a depth first search using adjacency list iterative algorithm
	bool searchListIterative(map<int, Node *>& adjacencyList, int startNodeId, int destinationNodeId, vector<int>& pathIds, int& numExploredNodes) const;

	// Perform a depth first search using adjacency list recursive algorithm
	bool searchListRecursive(map<int, Node *>& adjacencyList, int startNodeId, int destinationNodeId, vector<int>& path, int& numExploredNodes) const;

	// Perform a depth first search using adjacency matrix iterative algorithm
	bool searchMatrixIterative(vector< vector<double> >& adjacencyMatrix, int startNodeId, int destinationNodeId, vector<int>& pathIds, int& numExploredNodes) const;

	// Perform a depth first search using adjacency matrix recursive algorithm
	bool searchMatrixRecursive(vector< vector<double> >& adjacencyMatrix, int startNodeId, int destinationNodeId, vector<int>& pathIds, int& numExploredNodes) const;

private:

	// Helper method to do DFS on adjacency list recursive
	bool searchListRecursiveHelper(map<int, Node *>& adjacencyList, int currentNodeId, int destinationNodeId, vector<int>& path, vector<int>& visited, int& numExploredNodes) const;

	// Helper method to do DFS on matrix list recursive
	bool searchMatrixRecursiveHelper(vector< vector<double > >& adjacencyMatrix, int currentNodeId, int destinationNodeId, vector<int>& path, vector<int>& visited, int& numExploredNodes) const;
};

#endif
