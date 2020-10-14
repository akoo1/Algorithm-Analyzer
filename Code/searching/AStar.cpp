#include "AStar.h"
#include <algorithm>
#include <climits>
#include <cmath>


// Search the path using AStar iterative algorithm
bool AStar::searchList(map<int, Node *>& adjacencyList, int startNodeId, int destinationNodeId, vector<int>& pathIds, int& numExploredNodes) const {

	// Check the existence of the nodes in the list
	if (adjacencyList.find(startNodeId) == adjacencyList.end()
		|| adjacencyList.find(destinationNodeId) == adjacencyList.end())
		return false;

	// List where to store all visited nodes
	map<int, int> parentNodeIds;
	map<int, double> gScores;
	map<int, double> fScores;

	// Put max weights on all vertices
	// Each node will have no parent path initially
	vector<int> unvisited;

	map<int, Node *>::iterator it;
	for (it = adjacencyList.begin(); it != adjacencyList.end(); it++) {

		parentNodeIds[it->first] = -1;
		gScores[it->first] = INT_MAX;
		fScores[it->first] = INT_MAX;
		unvisited.push_back(it->first);
	}

	// The weight of the starting node will always be zero, the rest are infinite
	gScores[startNodeId] = 0;

	// Weighted scores to store the assumed distance from node to destination node
	fScores[startNodeId] = euclideanDistance(adjacencyList[startNodeId], adjacencyList[destinationNodeId]);

	// Calculate all shortest path from starting node to all other nodes
	while (!unvisited.empty()) {

		// Find the next node that has the lowest fScore
		int lowestNodeId;
		int lowestNodeIdIndex = -1;

		for (int i = 0; i < unvisited.size(); i += 1) {

			int nodeId = unvisited[i];

			if (i == 0 || fScores[nodeId] < fScores[lowestNodeId]) {

				lowestNodeId = nodeId;
				lowestNodeIdIndex = i;
			}
		}

		numExploredNodes++;
		unvisited.erase(unvisited.begin() + lowestNodeIdIndex);

		if (lowestNodeId == destinationNodeId)
			break;

		// Calculate the distance to other neighbors considering to choose
		// the lowest cost
		map<int, double>::iterator neighborIt;

		for (neighborIt = adjacencyList[lowestNodeId]->neighborNodeIds.begin();
			neighborIt != adjacencyList[lowestNodeId]->neighborNodeIds.end();
			neighborIt++) {
			double tentativeScore = gScores[lowestNodeId] + neighborIt->second;

			if (tentativeScore < gScores[neighborIt->first]) {

				gScores[neighborIt->first] = tentativeScore;
				fScores[neighborIt->first] = gScores[neighborIt->first] + euclideanDistance(adjacencyList[neighborIt->first], adjacencyList[destinationNodeId]);
				parentNodeIds[neighborIt->first] = lowestNodeId;
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

// Search the path using AStar matrix,
// NOTE: THE ADJACENCY LIST HERE IS ONLY USED FOR IDENTIFYING THE X,Y, and Z of a node AND NOT BEING USED IN THE ACTUAL ALGORITHM
bool AStar::searchMatrix(vector< vector<double> >& adjacencyMatrix, map<int, Node *> &adjacencyList, int startNodeId, int destinationNodeId, vector<int>& pathIds, int& numExploredNodes) {

	// Check the existence of the nodes in the list
	if (startNodeId < 0 || startNodeId >= (int)adjacencyMatrix.size()
		|| destinationNodeId < 0 || destinationNodeId >= (int)adjacencyMatrix.size())
		return false;

	// List where to store all visited nodes
	map<int, int> parentNodeIds;
	map<int, double> gScores;
	map<int, double> fScores;

	// Put max weights on all vertices
	// Each node will have no parent path initially
	vector<int> unvisited;

	map<int, Node *>::iterator it;
	for (int nodeId = 0; nodeId < adjacencyMatrix.size(); nodeId++) {

		parentNodeIds[nodeId] = -1;
		gScores[nodeId] = INT_MAX;
		fScores[nodeId] = INT_MAX;
		unvisited.push_back(nodeId);
	}

	// The weight of the starting node will always be zero, the rest are infinite
	gScores[startNodeId] = 0;
	fScores[startNodeId] = euclideanDistance(adjacencyList[startNodeId], adjacencyList[destinationNodeId]);

	// Calculate all shortest path from starting node to all other nodes
	while (!unvisited.empty()) {

		// Find the next node that has the lowest fScore
		int lowestNodeId;
		int lowestNodeIdIndex = -1;

		for (int i = 0; i < unvisited.size(); i += 1) {

			int nodeId = unvisited[i];

			if (i == 0 || fScores[nodeId] < fScores[lowestNodeId]) {

				lowestNodeId = nodeId;
				lowestNodeIdIndex = i;
			}
		}

		numExploredNodes++;
		unvisited.erase(unvisited.begin() + lowestNodeIdIndex);

		if (lowestNodeId == destinationNodeId)
			break;

		// Stop if no connection found left
		if (gScores[lowestNodeId] == INT_MAX)
			continue;

		// Calculate the distance to other neighbors considering to choose
		// the lowest cost
		for (int neighborNodeId = 0; neighborNodeId < (int)adjacencyMatrix.size(); neighborNodeId++) {

			if (adjacencyMatrix[lowestNodeId][neighborNodeId] != -1) {

				double tentativeScore = gScores[lowestNodeId] + adjacencyMatrix[lowestNodeId][neighborNodeId];

				if (tentativeScore < gScores[neighborNodeId]) {

					gScores[neighborNodeId] = tentativeScore;
					fScores[neighborNodeId] = gScores[neighborNodeId] + euclideanDistance(adjacencyList[neighborNodeId], adjacencyList[destinationNodeId]);
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

// Calculate distance between 2 nodes
double AStar::euclideanDistance(Node *fromNode, Node *toNode) const {

	return sqrt(
		pow(fromNode->x - toNode->x, 2) +
		pow(fromNode->y - toNode->y, 2) +
		pow(fromNode->z - toNode->z, 2)
		);
}
