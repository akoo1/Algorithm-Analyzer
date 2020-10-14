#include "Search.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <chrono>

// Constructor, default is DFS using adjacency list
Search::Search() {

	currentMode = "DFS_LIST_ITERATIVE";
	sourceNodeIdSearch = -1;
	destinationNodeIdSearch = -1;
}

// Destructor
Search::~Search() {

	map<int, Node *>::iterator it;
	for (it = adjacencyList.begin(); it != adjacencyList.end(); it++)
		delete it->second;
}

// Set the start and end of search
void Search::setSourceAndDestinationIds(int sourceId, int destinationId) {

	sourceNodeIdSearch = sourceId;
	destinationNodeIdSearch = destinationId;
}

// Load the data to both the adjacency list and matrix
// The provided filename is ignored. This project requires 3 files
void Search::load(const string& filename) {

	// Load the graph as an adjacency list
	ifstream graphFile("../../Data/large50/largeGraph.txt");
	string line;

	while (getline(graphFile, line)) {

		stringstream ss(line);

		// Get the source node
		string token;
		getline(ss, token, ',');
		int sourceId = toInt(token);
		Node* sourceNode = NULL;

		// Find or create a source node
		if (adjacencyList.find(sourceId) == adjacencyList.end()) {

			sourceNode = new Node();
			sourceNode->id = sourceId;
			adjacencyList[sourceId] = sourceNode;   // adjacencyList = {1 : Node(1)}
		}
		else {
			sourceNode = adjacencyList[sourceId];
		}

		// Get the destination nodes from the source node
		while (getline(ss, token, ',')) {

			int destinationId = toInt(token);
			Node* destinationNode = NULL;

			// Find or create the destination node
			if (adjacencyList.find(destinationId) == adjacencyList.end()) {

				destinationNode = new Node();
				destinationNode->id = destinationId;
				adjacencyList[destinationId] = destinationNode;
			}
			else {
				destinationNode = adjacencyList[destinationId];
			}

			// Connect source to destination, we initially put 1 as a weight
			// but will load the weight later on
			sourceNode->neighborNodeIds[destinationId] = 0;
		}
	}

	graphFile.close();

	// Load the weights of the matrix
	ifstream weightsFile("../../Data/large50/largeWeights.txt");

	while (getline(weightsFile, line)) {

		stringstream ss(line);

		// Get the source node
		string token;
		getline(ss, token, ',');
		Node *sourceNode = adjacencyList[toInt(token)];

		// Get the destination node
		getline(ss, token, ',');
		int destinationNodeId = toInt(token);

		// Get the weight
		getline(ss, token, ',');
		double weight = toDouble(token);

		// Connect...
		sourceNode->neighborNodeIds[destinationNodeId] = weight;
	}

	weightsFile.close();

	// Load the positions of the matrix
	ifstream positionsFile("../../Data/large50/largePositions.txt");

	while (getline(positionsFile, line)) {

		stringstream ss(line);

		// get the node
		string token;
		getline(ss, token, ',');
		Node *sourceNode = adjacencyList[toInt(token)];

		// Get the x, y, and z position
		getline(ss, token, ',');
		sourceNode->x = toDouble(token);

		getline(ss, token, ',');
		sourceNode->y = toDouble(token);

		getline(ss, token, ',');
		sourceNode->z = toDouble(token);
	}

	positionsFile.close();

	// Load the graph as a matrix
	int highestNodeId = -1;

	// Find the highest node id so we know how many rows x column we need to create
	map<int, Node *>::iterator it;
	for (it = adjacencyList.begin(); it != adjacencyList.end(); it++)
		if (it->second->id > highestNodeId)
			highestNodeId = it->second->id;

	// Create the matrix
	for (int r = 0; r <= highestNodeId; r += 1) {

		adjacencyMatrix.push_back(vector<double>());

		// The content of the matrix is the weight between two nodes
		// initially we put -1 to indicate that there are no connection
		for (int c = 0; c <= highestNodeId; c += 1)
			adjacencyMatrix[r].push_back(-1);
	}

	// Then we fill the matrix with the right weights
	for (it = adjacencyList.begin(); it != adjacencyList.end(); it++) {

		map<int, double>::iterator itWeight;

		for (itWeight = it->second->neighborNodeIds.begin(); itWeight != it->second->neighborNodeIds.end(); itWeight++)
			adjacencyMatrix[it->first][itWeight->first] = itWeight->second;
	}

}

// Execute the search
void Search::execute() {

	resultPathIds.clear();
	numExploredNodes = 0;

	elapsedTime = 0;
	
	// Do search and record the sort time
	chrono::time_point<chrono::high_resolution_clock> start = chrono::high_resolution_clock::now();

	if (currentMode == "DFS_LIST_ITERATIVE")
		pathFound = dfs.searchListIterative(adjacencyList, sourceNodeIdSearch, destinationNodeIdSearch, resultPathIds, numExploredNodes);
	else if (currentMode == "DFS_LIST_RECURSIVE")
		pathFound = dfs.searchListRecursive(adjacencyList, sourceNodeIdSearch, destinationNodeIdSearch, resultPathIds, numExploredNodes);
	else if (currentMode == "DFS_MATRIX_ITERATIVE")
		pathFound = dfs.searchMatrixIterative(adjacencyMatrix, sourceNodeIdSearch, destinationNodeIdSearch, resultPathIds, numExploredNodes);
	else if (currentMode == "DFS_MATRIX_RECURSIVE")
		pathFound = dfs.searchMatrixRecursive(adjacencyMatrix, sourceNodeIdSearch, destinationNodeIdSearch, resultPathIds, numExploredNodes);
	else if (currentMode == "BFS_LIST_ITERATIVE")
		pathFound = bfs.searchListIterative(adjacencyList, sourceNodeIdSearch, destinationNodeIdSearch, resultPathIds, numExploredNodes);
	else if (currentMode == "BFS_LIST_RECURSIVE")
		pathFound = bfs.searchListRecursive(adjacencyList, sourceNodeIdSearch, destinationNodeIdSearch, resultPathIds, numExploredNodes);
	else if (currentMode == "BFS_MATRIX_ITERATIVE")
		pathFound = bfs.searchMatrixIterative(adjacencyMatrix, sourceNodeIdSearch, destinationNodeIdSearch, resultPathIds, numExploredNodes);
	else if (currentMode == "BFS_MATRIX_RECURSIVE")
		pathFound = bfs.searchMatrixRecursive(adjacencyMatrix, sourceNodeIdSearch, destinationNodeIdSearch, resultPathIds, numExploredNodes);
	else if (currentMode == "DIJKSTRA_LIST")
		pathFound = dijkstra.searchList(adjacencyList, sourceNodeIdSearch, destinationNodeIdSearch, resultPathIds, numExploredNodes);
	else if (currentMode == "DIJKSTRA_MATRIX")
		pathFound = dijkstra.searchMatrix(adjacencyMatrix, sourceNodeIdSearch, destinationNodeIdSearch, resultPathIds, numExploredNodes);
	else if (currentMode == "A_STAR_LIST")
		pathFound = aStar.searchList(adjacencyList, sourceNodeIdSearch, destinationNodeIdSearch, resultPathIds, numExploredNodes);
	else if (currentMode == "A_STAR_MATRIX")
		pathFound = aStar.searchMatrix(adjacencyMatrix, adjacencyList, sourceNodeIdSearch, destinationNodeIdSearch, resultPathIds, numExploredNodes);

	chrono::time_point<chrono::high_resolution_clock> finish = chrono::high_resolution_clock::now();

	chrono::duration<double> elapsed = finish - start;
	elapsedTime = elapsed.count();
}

// Display results
void Search::display() {

	cout << arrangeOutput();
}

// Change the type
void Search::select(const string &selection) {

	if (selection != "DFS_LIST_ITERATIVE" && selection != "DFS_LIST_RECURSIVE"
		&& selection != "DFS_MATRIX_ITERATIVE" && selection != "DFS_MATRIX_RECURSIVE"
		&& selection != "BFS_LIST_ITERATIVE"  && selection != "BFS_LIST_RECURSIVE"
		&& selection != "BFS_MATRIX_ITERATIVE" && selection != "BFS_MATRIX_RECURSIVE"
		&& selection != "DIJKSTRA_LIST" && selection != "DIJKSTRA_MATRIX"
		&& selection != "A_STAR_LIST" && selection != "A_STAR_MATRIX") {

		return;
	}

	currentMode = selection;
}

// Write the data to a file
void Search::save(const string& filename) {

	ofstream outFile(filename.c_str());
	outFile << arrangeOutput();
	outFile.close();
}

// Print the stats to output
void Search::stats() {

	cout << "STATS" << endl;
	cout << "-----" << endl;
	cout << arrangeOutput();
	cout << "EXECUTION TIME: " << elapsedTime << "s" << endl;	
	cout << endl;
}

// Convert a string to integer
int Search::toInt(const string& str) const {

	stringstream ss(str);
	int value;
	ss >> value;

	return value;
}

// Convert a string to double
double Search::toDouble(const string& str) const {

	stringstream ss(str);
	double value;
	ss >> value;

	return value;
}

// Arrange the output as string
string Search::arrangeOutput() {

	stringstream ss;
	ss << "MODE: " << currentMode << endl;
	ss << "From Node " << sourceNodeIdSearch << " to Node " << destinationNodeIdSearch << endl;

	if (!pathFound) {
		ss << "No path found." << endl;
		return ss.str();
	}

	double totalWeight = 0;

	for (int i = 0; i < resultPathIds.size(); i += 1) {

		int nodeId = resultPathIds[i];
		Node* node = adjacencyList[nodeId];

		ss << node->id << " (x: " << node->x << ", y: " << node->y << ", z: " << node->z << ")" << endl;

		if (i + 1 < resultPathIds.size())
			totalWeight += node->neighborNodeIds[resultPathIds[i + 1]];
	}

	ss << "Number of nodes in path: " << resultPathIds.size() << endl;
	ss << "Total Weight: " << totalWeight << endl;
	ss << "Number of nodes explored: " << numExploredNodes << endl;

	return ss.str();
}