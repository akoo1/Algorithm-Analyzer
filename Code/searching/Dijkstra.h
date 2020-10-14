#ifndef dijkstra_h
#define dijkstra_h

#include <map>
#include <vector>
#include "Node.h"

using namespace std;


class Dijkstra {

public:

	// Search the path using dijkstra iterative algorithm
	bool searchList(map<int, Node *>& adjacencyList, int startNodeId, int destinationNodeId, vector<int>& pathIds, int& numExploredNodes) const;

	// Search the path using dijkstra 
	bool searchMatrix(vector< vector<double> >& adjacencyMatrix, int startNodeId, int destinationNodeId, vector<int>& pathIds, int& numExploredNodes);

private:

};

#endif
