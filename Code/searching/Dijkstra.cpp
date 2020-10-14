#include "Dijkstra.h"
#include <climits>
#include <algorithm>


// Search the path using dijkstra iterative algorithm
bool Dijkstra::searchList(map<int, Node *> &adjacencyList, int startNodeId, int destinationNodeId, vector<int>& pathIds, int& numExploredNodes) const {

	// Check the existence of the nodes in the list
	if (adjacencyList.find(startNodeId) == adjacencyList.end()
		|| adjacencyList.find(destinationNodeId) == adjacencyList.end())
		return false;

	// List where to store all visited nodes
	map<int, int> parentNodeIds;
	map<int, double> weights;

	// Put max weights on all vertices
	// Each node will have no parent path initially
	vector<int> unvisited;

	map<int, Node *>::iterator it;
	for (it = adjacencyList.begin(); it != adjacencyList.end(); it++) {

		parentNodeIds[it->first] = -1;
		weights[it->first] = INT_MAX;
		unvisited.push_back(it->first);
	}

	// The weight of the starting node will always be zero, the rest are infinite
	weights[startNodeId] = 0;

	// Calculate all shortest path from starting node to all other nodes
	while (!unvisited.empty()) {

		// Find the next node that has the lowest weight
		int lowestNodeId;
		int lowestNodeIdIndex = -1;

		for (int i = 0; i < unvisited.size(); i += 1) {
			int nodeId = unvisited[i];

			if (i == 0 || weights[nodeId] < weights[lowestNodeId]) {

				lowestNodeId = nodeId;
				lowestNodeIdIndex = i;
			}
		}


		unvisited.erase(unvisited.begin() + lowestNodeIdIndex);
		numExploredNodes++;
		
		if (lowestNodeId == destinationNodeId)
			break;

		// Stop if no connection found left
		if (weights[lowestNodeId] == INT_MAX)
			return false;

		// Calculate the distance to other neighbors considering to choose
		// the lowest cost
		map<int, double>::iterator neighborIt;

		for (neighborIt = adjacencyList[lowestNodeId]->neighborNodeIds.begin();
			neighborIt != adjacencyList[lowestNodeId]->neighborNodeIds.end();
			neighborIt++) {

			double adjacentDistance = weights[lowestNodeId] + neighborIt->second;

			if (adjacentDistance < weights[neighborIt->first]) {

				weights[neighborIt->first] = adjacentDistance;
				parentNodeIds[neighborIt->first] = lowestNodeId;
			}
		}
	}

	// Build the path if found
	int currentNodeId = destinationNodeId;
	pathIds.push_back(currentNodeId);

	while (currentNodeId != startNodeId) {

		currentNodeId = parentNodeIds[currentNodeId];
		pathIds.insert(pathIds.begin(), currentNodeId);
	}

	return true;
}

// Search the path using dijkstra 
bool Dijkstra::searchMatrix(vector< vector<double> > &adjacencyMatrix, int startNodeId, int destinationNodeId, vector<int> &pathIds, int &numExplored) {

	// Check the existence of the nodes in the list
	if (startNodeId < 0 || startNodeId >= adjacencyMatrix.size()
		|| destinationNodeId < 0 || destinationNodeId >= adjacencyMatrix.size())
		return false;

	// List where to store all visited nodes
	map<int, int> parentNodeIds;
	map<int, double> weights;

	// Put max weights on all vertices
	// Each node will have no parent path initially
	vector<int> unvisited;

	map<int, Node *>::iterator it;
	for (int nodeId = 0; nodeId < adjacencyMatrix.size(); nodeId++) {

		parentNodeIds[nodeId] = -1;
		weights[nodeId] = INT_MAX;
		unvisited.push_back(nodeId);
	}

	// The weight of the starting node will always be zero, the rest are infinite
	weights[startNodeId] = 0;

	// Calculate all shortest path from starting node to all other nodes
	while (!unvisited.empty()) {

		// Find the next node that has the lowest weight
		int lowestNodeId;
		int lowestNodeIdIndex = -1;

		for (int i = 0; i < unvisited.size(); i += 1) {
			int nodeId = unvisited[i];

			if (i == 0 || weights[nodeId] < weights[lowestNodeId]) {

				lowestNodeId = nodeId;
				lowestNodeIdIndex = i;
			}
		}

		unvisited.erase(unvisited.begin() + lowestNodeIdIndex);
		numExplored++;

		if (lowestNodeId == destinationNodeId)
			break;

		// Stop if no connection found left
		if (weights[lowestNodeId] == INT_MAX)
			continue;

		// Calculate the distance to other neighbors considering to choose
		// the lowest cost
		for (int neighborNodeId = 0; neighborNodeId < adjacencyMatrix.size(); neighborNodeId += 1) {

			if (adjacencyMatrix[lowestNodeId][neighborNodeId] != -1) {
				double adjacentDistance = weights[lowestNodeId] + adjacencyMatrix[lowestNodeId][neighborNodeId];

				if (adjacentDistance < weights[neighborNodeId]) {

					weights[neighborNodeId] = adjacentDistance;
					parentNodeIds[neighborNodeId] = lowestNodeId;
				}
			}
		}
	}

	if (parentNodeIds[destinationNodeId] == -1)
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