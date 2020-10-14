#include "DFS.h"
#include <stack>
#include <algorithm>


// Perform a depth first search using adjacency list iterative algorithm
bool DFS::searchListIterative(map<int, Node *> &adjacencyList, int startNodeId, int destinationNodeId, vector<int>& pathIds, int& numExploredNodes) const
{
	// Check the existence of the nodes in the list
	if (adjacencyList.find(startNodeId) == adjacencyList.end()
		|| adjacencyList.find(destinationNodeId) == adjacencyList.end())
		return false;

	// List where to store all visited nodes
	stack<int> theStack;
	theStack.push(startNodeId);

	while (!theStack.empty()) {

		int nodeId = theStack.top();
		theStack.pop();

		numExploredNodes++;

		if (find(pathIds.begin(), pathIds.end(), nodeId) == pathIds.end())
			pathIds.push_back(nodeId);

		// Stop if we found the target path
		if (nodeId == destinationNodeId)
			return true;

		// Move to the next unvisited neighbor
		Node* currentNode = adjacencyList[nodeId];
		map<int, double>::iterator itNeighbors;

		for (itNeighbors = currentNode->neighborNodeIds.begin(); itNeighbors != currentNode->neighborNodeIds.end(); itNeighbors++)
			if (find(pathIds.begin(), pathIds.end(), itNeighbors->first) == pathIds.end())
				theStack.push(itNeighbors->first);
	}

	return false;
}

// Perform a depth first search using adjacency list recursive algorithm
bool DFS::searchListRecursive(map<int, Node *>& adjacencyList, int startNodeId, int destinationNodeId, vector<int>& path, int& numExploredNodes) const {
	// Check the existence of the nodes in the list
	if (adjacencyList.find(startNodeId) == adjacencyList.end()
		|| adjacencyList.find(destinationNodeId) == adjacencyList.end())
		return false;

	vector<int> visited;
	return searchListRecursiveHelper(adjacencyList, startNodeId, destinationNodeId, path, visited, numExploredNodes);
}

// Perform a depth first search using adjacency matrix iterative algorithm
bool DFS::searchMatrixIterative(vector< vector<double> >& adjacencyMatrix, int startNodeId, int destinationNodeId, vector<int>& pathIds, int& numExploredNodes) const {

	// Check the existence of the nodes in the list
	if (startNodeId < 0 || startNodeId >= (int)adjacencyMatrix.size()
		|| destinationNodeId < 0 || destinationNodeId >= (int)adjacencyMatrix.size())
		return false;

	// List where to store all visited nodes
	stack<int> theStack;
	theStack.push(startNodeId);

	while (!theStack.empty()){

		int nodeId = theStack.top();
		theStack.pop();

		numExploredNodes++;

		if (find(pathIds.begin(), pathIds.end(), nodeId) == pathIds.end())
			pathIds.push_back(nodeId);

		// Stop if we found the target path
		if (nodeId == destinationNodeId)
			return true;

		// Move to the next unvisited neighbor
		for (int i = 0; i < adjacencyMatrix.size(); i += 1)
			if (adjacencyMatrix[nodeId][i] != -1 && find(pathIds.begin(), pathIds.end(), i) == pathIds.end())
				theStack.push(i);

	}

	return false;
}

// Perform a depth first search using adjacency matrix recursive algorithm
bool DFS::searchMatrixRecursive(vector< vector<double> >& adjacencyMatrix, int startNodeId, int destinationNodeId, vector<int>& pathIds, int& numExploredNodes) const {

	// Check the existence of the nodes in the list
	if (startNodeId < 0 || startNodeId >= adjacencyMatrix.size()
		|| destinationNodeId < 0 || destinationNodeId >= adjacencyMatrix.size())
		return false;

	vector<int> visited;
	return searchMatrixRecursiveHelper(adjacencyMatrix, startNodeId, destinationNodeId, pathIds, visited, numExploredNodes);
}

// Helper method to do DFS on adjacency list recursive
bool DFS::searchListRecursiveHelper(map<int, Node *>& adjacencyList, int currentNodeId, int destinationNodeId, vector<int>& path, vector<int>& visited, int& numExploredNodes) const {

	visited.push_back(currentNodeId);

	numExploredNodes++;

	// Stop if we found the path
	if (currentNodeId == destinationNodeId) {

		path.push_back(destinationNodeId);
		return true;
	}

	Node* currentNode = adjacencyList[currentNodeId];
	map<int, double>::iterator itNeighbors;

	for (itNeighbors = currentNode->neighborNodeIds.begin(); itNeighbors != currentNode->neighborNodeIds.end(); itNeighbors++){

		if (find(visited.begin(), visited.end(), itNeighbors->first) == visited.end()) {

			if (searchListRecursiveHelper(adjacencyList, itNeighbors->first, destinationNodeId, path, visited, numExploredNodes)){

				path.insert(path.begin(), currentNodeId);
				return true;
			}
		}
	}

	return false;
}

// Helper method to do DFS on matrix list recursive
bool DFS::searchMatrixRecursiveHelper(vector< vector<double > >& adjacencyMatrix, int currentNodeId, int destinationNodeId, vector<int>& path, vector<int>& visited, int& numExploredNodes) const {

	visited.push_back(currentNodeId);

	numExploredNodes++;

	// Stop if we found the path
	if (currentNodeId == destinationNodeId) {

		path.push_back(destinationNodeId);
		return true;
	}

	for (int i = 0; i < adjacencyMatrix.size(); i += 1) {

		if (adjacencyMatrix[currentNodeId][i] != -1 && find(visited.begin(), visited.end(), i) == visited.end()) {

			if (searchMatrixRecursiveHelper(adjacencyMatrix, (int)i, destinationNodeId, path, visited, numExploredNodes)) {
				path.insert(path.begin(), currentNodeId);
				return true;
			}
		}
	}

	return false;
}
