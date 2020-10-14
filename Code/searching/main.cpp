#include <iostream>
#include <string>
#include <cstdlib>
#include <vector>
#include <fstream>
#include <ctime>
#include "Algorithm.h"
#include "Search.h"


using namespace std;

// Entry point of the program
int main(int argc, char* argv[]) {

	if (argc != 3) {
		cout << "Usage: " << argv[0] << " <source node id> <destination node id>" << endl;
		return 0;
	}

	int sourceNodeId = atoi(argv[1]);
	int destinationNodeId = atoi(argv[2]);

	Search* dfsListIterative = new Search();
	dfsListIterative->select("DFS_LIST_ITERATIVE");
	dfsListIterative->setSourceAndDestinationIds(sourceNodeId, destinationNodeId);

	Search* dfsListRecursive = new Search();
	dfsListRecursive->select("DFS_LIST_RECURSIVE");
	dfsListRecursive->setSourceAndDestinationIds(sourceNodeId, destinationNodeId);

	Search* dfsMatrixIterative = new Search();
	dfsMatrixIterative->select("DFS_MATRIX_ITERATIVE");
	dfsMatrixIterative->setSourceAndDestinationIds(sourceNodeId, destinationNodeId);

	Search* dfsMatrixRecursive = new Search();
	dfsMatrixRecursive->select("DFS_MATRIX_RECURSIVE");
	dfsMatrixRecursive->setSourceAndDestinationIds(sourceNodeId, destinationNodeId);

	Search* bfsListIterative = new Search();
	bfsListIterative->select("BFS_LIST_ITERATIVE");
	bfsListIterative->setSourceAndDestinationIds(sourceNodeId, destinationNodeId);

	Search* bfsListRecursive = new Search();
	bfsListRecursive->select("BFS_LIST_RECURSIVE");
	bfsListRecursive->setSourceAndDestinationIds(sourceNodeId, destinationNodeId);

	Search* bfsMatrixIterative = new Search();
	bfsMatrixIterative->select("BFS_MATRIX_ITERATIVE");
	bfsMatrixIterative->setSourceAndDestinationIds(sourceNodeId, destinationNodeId);

	Search* bfsMatrixRecursive = new Search();
	bfsMatrixRecursive->select("BFS_MATRIX_RECURSIVE");
	bfsMatrixRecursive->setSourceAndDestinationIds(sourceNodeId, destinationNodeId);

	Search* dijkstraList = new Search();
	dijkstraList->select("DIJKSTRA_LIST");
	dijkstraList->setSourceAndDestinationIds(sourceNodeId, destinationNodeId);

	Search* dijkstraMatrix = new Search();
	dijkstraMatrix->select("DIJKSTRA_MATRIX");
	dijkstraMatrix->setSourceAndDestinationIds(sourceNodeId, destinationNodeId);
	
	Search* aStarList = new Search();
	aStarList->select("A_STAR_LIST");
	aStarList->setSourceAndDestinationIds(sourceNodeId, destinationNodeId);

	Search* aStarMatrix = new Search();
	aStarMatrix->select("A_STAR_MATRIX");
	aStarMatrix->setSourceAndDestinationIds(sourceNodeId, destinationNodeId);

	vector<Algorithm *> algorithms;

	algorithms.push_back(dfsListIterative);
	algorithms.push_back(dfsListRecursive);
	algorithms.push_back(dfsMatrixIterative);
	algorithms.push_back(dfsMatrixRecursive);

	algorithms.push_back(bfsListIterative);
	algorithms.push_back(bfsListRecursive);
	algorithms.push_back(bfsMatrixIterative);
	algorithms.push_back(bfsMatrixRecursive);

	algorithms.push_back(dijkstraList);
	algorithms.push_back(dijkstraMatrix);

	algorithms.push_back(aStarList);
	algorithms.push_back(aStarMatrix);

	// The output files are in the same order as above
	string saveFilenames[] = { 
		"DFS_LIST_ITERATIVE.txt", 
		"DFS_LIST_RECURSIVE.txt",
		"DFS_MATRIX_ITERATIVE.txt",
		"DFS_MATRIX_RECURSIVE.txt",
		"BFS_LIST_ITERATIVE.txt",
		"BFS_LIST_RECURSIVE.txt",
		"BFS_MATRIX_ITERATIVE.txt",
		"BFS_MATRIX_RECURSIVE.txt",
		"DIJKSTRA_LIST.txt",
		"DIJKSTRA_MATRIX.txt",
		"A_STAR_LIST.txt",
		"A_STAR_MATRIX.txt"
	};

	cout << endl;
	// Run the algorithms
	for (int i = 0; i < algorithms.size(); i += 1) {

		Algorithm* algorithm = algorithms[i];

		algorithm->load("");		
		algorithm->execute();
		algorithm->stats();
		algorithm->save("../../Data/searching_outputs/" + saveFilenames[i]);
	}

	for (int i = 0; i < algorithms.size(); i += 1)
		delete algorithms[i];

	return 0;
}




