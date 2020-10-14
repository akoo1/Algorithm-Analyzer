#ifndef search_h
#define search_h

#include <string>
#include <vector>
#include <map>
#include "Algorithm.h"
#include "Node.h"
#include "DFS.h"
#include "BFS.h"
#include "Dijkstra.h"
#include "AStar.h"

using namespace std;

// A Search object that performs graph search algorithms, this uses the strategy pattern
class Search : public Algorithm {

public:

	// Constructor, default is DFS using adjacency list
	Search();

	// Destructor
	~Search();

	// Set the start and end of search
	void setSourceAndDestinationIds(int sourceId, int destinationId);

	// Load the data to both the adjacency list and matrix
	// The provided filename is ignored. This project requires 3 files
	void load(const string& filename);

	// Execute the search
	void execute();

	// Display results
	void display();

	// Change the type
	void select(const string& selection);

	// Write the results to a file
	void save(const string& filename);

	// Print the stats to output
	void stats();

private:

	double elapsedTime;
	int numExploredNodes;

	// To be provided before searching
	int sourceNodeIdSearch;
	int destinationNodeIdSearch;

	// For results
	vector<int> resultPathIds;
	bool pathFound;

	// Mode is DFS_LIST_RECURSIVE, DFS_LIST_ITERATIVE,
	// DFS_MATRIX_RECURSIVE, DFS_MATRIX_ITERATIVE, 
	// BFS_LIST, BFS_MATRIX,
	// DIJKSTRA_LIST, DIJKSTRA_MATRIX, 
	// or A_STAR_LIST, A_STAR_MATRIX
	string currentMode;

	// The adjacency list is a dictionary that maps a node_id to a Node object
	map<int, Node *> adjacencyList;
	// The adjacency matrix is a 2D vector
	vector< vector<double> > adjacencyMatrix;

	// Composition strategy
	DFS dfs;
	BFS bfs;
	Dijkstra dijkstra;
	AStar aStar;

	// Convert a string to integer
	int toInt(const string &str) const;

	// Convert a string to double
	double toDouble(const string &str) const;
	
	// Arrange the output as string
	string arrangeOutput();
};

#endif
