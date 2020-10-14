#ifndef node_h
#define node_h

#include <map>

using namespace std;

// The adjacency list is a dictionary that maps a node_id to a Node object
// A node represents a vertex in a graph
struct Node {

	int id;
	double x, y, z;

	// The keys are all the neighbor nodes, and the values are the wieights of the edges
	map<int, double> neighborNodeIds;
};

#endif
