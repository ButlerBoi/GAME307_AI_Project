#ifndef GRAPH_H
#define GRAPH_H

#include "Node.h"
#include "NodeAndPriority.h"
#include <vector>
#include <queue>
#include <deque>
#include <map>

using namespace std;

struct ComparePriority {
	bool operator() (NodeAndPriority& lhs, NodeAndPriority& rhs) {
		return lhs.priority > rhs.priority;
	}
};

class Graph{

private:
	map<int, Node*> node;
	vector<vector<int>> cost;
	vector<int> sceneNodes;

	vector<int> GetNeighbours(int currentNode_);
	vector<int> StraightPath(vector<int> inPath);
	float Heuristic(int node, int goalNode);

public:
	Graph();
	~Graph();
	bool onCreate(vector<Node*> nodes);
	int numNodes();
	Node* getNode(int label) { return node[label]; }
	void addWeightConnection(int fromNode, int toNode, float weight);
	vector<int> neighbours(int fromNode);
	vector<int> Dijkstra(int startNode, int goalNode);
	int NodeSearch(int label_);

};
#endif
