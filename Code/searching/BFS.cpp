#include "BFS.h"
#include <algorithm>


// Perform a breadth first search using adjacency list iterative algorithm
bool BFS::searchListIterative(map<int, Node *>& adjacencyList, int startNodeId, int destinationNodeId, vector<int>& pathIds, int& numExploredNodes) const {

	// Check the existence of the nodes in the list
	if (adjacencyList.find(startNodeId) == adjacencyList.end()
		|| adjacencyList.find(destinationNodeId) == adjacencyList.end())
		return false;

	// List where to store all visited nodes
	map<int, int> parentNodeIds;

	// Each node will have no parent path initially
	map<int, Node *>::iterator it;
	for (it = adjacencyList.begin(); it != adjacencyList.end(); it++)
		parentNodeIds[it->first] = -1;

	vector<int> visited;
	queue<int> theQueue;

	visited.push_back(startNodeId);
	theQueue.push(startNodeId);

	bool pathFound = false;

	while (!theQueue.empty()) {

		int nodeId = theQueue.front();
		theQueue.pop();

		numExploredNodes++;

		// Stop if we found the target path
		if (nodeId == destinationNodeId) {

			pathFound = true;
			break;
		}

		// Move to the next unvisited neighbor
		Node* currentNode = adjacencyList[nodeId];
		map<int, double>::iterator itNeighbors;

		for (itNeighbors = currentNode->neighborNodeIds.begin(); itNeighbors != currentNode->neighborNodeIds.end(); itNeighbors++) {

			if (find(visited.begin(), visited.end(), itNeighbors->first) == visited.end()) {

				parentNodeIds[itNeighbors->first] = nodeId;
				visited.push_back(itNeighbors->first);
				theQueue.push(itNeighbors->first);
			}
		}
	}

	if (!pathFound)
		return false;

	// Build the path if found
	int currentNodeId = destinationNodeId;
	pathIds.push_back(currentNodeId);

	while (currentNodeId != startNodeId) {

		currentNodeId = parentNodeIds[currentNodeId];
		pathIds.insert(pathIds.begin(), currentNodeId);
	}

	return true;
}

// Perform a breadth first search using adjacency list recursive algorithm
bool BFS::searchListRecursive(map<int, Node *> &adjacencyList, int startNodeId, int destinationNodeId, vector<int> &pathIds, int &numExploredNodes) const {

	// Check the existence of the nodes in the list
	if (adjacencyList.find(startNodeId) == adjacencyList.end()
		|| adjacencyList.find(destinationNodeId) == adjacencyList.end())
		return false;

	// List where to store all visited nodes
	map<int, int> parentNodeIds;

	// Each node will have no parent path initially
	map<int, Node *>::iterator it;
	for (it = adjacencyList.begin(); it != adjacencyList.end(); it++)
		parentNodeIds[it->first] = -1;

	vector<int> visited;
	queue<int> theQueue;

	visited.push_back(startNodeId);
	theQueue.push(startNodeId);

	if (!searchListRecursiveHelper(adjacencyList, destinationNodeId, theQueue, visited, parentNodeIds, numExploredNodes))
		return false;

	// Build the path if found
	int currentNodeId = destinationNodeId;
	pathIds.push_back(currentNodeId);

	while (currentNodeId != startNodeId) {

		currentNodeId = parentNodeIds[currentNodeId];
		pathIds.insert(pathIds.begin(), currentNodeId);
	}

	return true;
}

// Perform a breadth first search using matrix iterative algorithm
bool BFS::searchMatrixIterative(vector< vector<double> >& adjacencyMatrix, int startNodeId, int destinationNodeId, vector<int>& pathIds, int& numExploredNodes) const {

	// Check the existence of the nodes in the list
	if (startNodeId < 0 || startNodeId >= adjacencyMatrix.size()
		|| destinationNodeId < 0 || destinationNodeId >= (int)adjacencyMatrix.size())
		return false;

	// List where to store all visited nodes
	map<int, int> parentNodeIds;

	// Each node will have no parent path initially
	for (int nodeId = 0; nodeId < adjacencyMatrix.size(); nodeId += 1)
		parentNodeIds[nodeId] = -1;

	vector<int> visited;
	queue<int> theQueue;

	visited.push_back(startNodeId);
	theQueue.push(startNodeId);

	bool pathFound = false;

	while (!theQueue.empty()) {

		int nodeId = theQueue.front();
		theQueue.pop();

		numExploredNodes++;

		// Stop if we found the target path
		if (nodeId == destinationNodeId) {

			pathFound = true;
			break;
		}

		// Move to the next unvisited neighbor
		for (int i = 0; i < adjacencyMatrix.size(); i += 1) {

			if (adjacencyMatrix[nodeId][i] != -1 && find(visited.begin(), visited.end(), i) == visited.end()) {

				parentNodeIds[i] = nodeId;
				visited.push_back(i);
				theQueue.push(i);
			}
		}
	}

	if (!pathFound)
		return false;

	// Build the path if found
	int currentNodeId = destinationNodeId;
	pathIds.push_back(currentNodeId);

	while (currentNodeId != startNodeId) {

		currentNodeId = parentNodeIds[currentNodeId];
		pathIds.insert(pathIds.begin(), currentNodeId);
	}

	return true;
}

// Perform a breadth first search using matrix recursive algorithm
bool BFS::searchMatrixRecursive(vector< vector<double> >& adjacencyMatrix, int startNodeId, int destinationNodeId, vector<int>& pathIds, int& numExploredNodes) const {

	// Check the existence of the nodes in the list
	if (startNodeId < 0 || startNodeId >= adjacencyMatrix.size()
		|| destinationNodeId < 0 || destinationNodeId >= adjacencyMatrix.size())
		return false;

	// List where to store all visited nodes
	map<int, int> parentNodeIds;

	// Each node will have no parent path initially
	for (int nodeId = 0; nodeId < adjacencyMatrix.size(); nodeId += 1)
		parentNodeIds[nodeId] = -1;

	vector<int> visited;
	queue<int> theQueue;

	visited.push_back(startNodeId);
	theQueue.push(startNodeId);

	if (!searchMatrixRecursiveHelper(adjacencyMatrix, destinationNodeId, theQueue, visited, parentNodeIds, numExploredNodes))
		return false;

	// Build the path if found
	int currentNodeId = destinationNodeId;
	pathIds.push_back(currentNodeId);

	while (currentNodeId != startNodeId) {

		currentNodeId = parentNodeIds[currentNodeId];
		pathIds.insert(pathIds.begin(), currentNodeId);
	}

	return true;
}

// Recursively traverse the graph using breadth first search until the destination node is found
bool BFS::searchListRecursiveHelper(map<int, Node *>& adjacencyList, int destinationNodeId,
	queue<int>& theQueue, vector<int>& visited, map<int, int>& parentNodeIds, int& numExploredNodes) const {

	if (theQueue.empty())
		return false;

	int nodeId = theQueue.front();
	theQueue.pop();

	numExploredNodes++;

	// Stop if we found the target path
	if (nodeId == destinationNodeId)
		return true;

	// Move to the next unvisited neighbor
	Node* currentNode = adjacencyList[nodeId];
	map<int, double>::iterator itNeighbors;

	for (itNeighbors = currentNode->neighborNodeIds.begin(); itNeighbors != currentNode->neighborNodeIds.end(); itNeighbors++) {

		if (find(visited.begin(), visited.end(), itNeighbors->first) == visited.end()) {

			parentNodeIds[itNeighbors->first] = nodeId;
			visited.push_back(itNeighbors->first);
			theQueue.push(itNeighbors->first);
		}
	}

	return searchListRecursiveHelper(adjacencyList, destinationNodeId, theQueue, visited, parentNodeIds, numExploredNodes);
}

// Recursively traverse the graph using breadth first search until the destination node is found
bool BFS::searchMatrixRecursiveHelper(vector< vector<double> > &adjacencyMatrix, int destinationNodeId,
	queue<int> &theQueue, vector<int> &visited, map<int, int> &parentNodeIds, int &numExploredNodes) const {

	if (theQueue.empty())
		return false;

	int nodeId = theQueue.front();
	theQueue.pop();

	numExploredNodes++;

	// Stop if we found the target path
	if (nodeId == destinationNodeId)
		return true;

	// Move to the next unvisited neighbor
	for (int i = 0; i < adjacencyMatrix.size(); i += 1) {

		if (adjacencyMatrix[nodeId][i] != -1 && find(visited.begin(), visited.end(), i) == visited.end()) {

			parentNodeIds[i] = nodeId;
			visited.push_back(i);
			theQueue.push(i);
		}
	}

	return searchMatrixRecursiveHelper(adjacencyMatrix, destinationNodeId, theQueue, visited, parentNodeIds, numExploredNodes);
}
