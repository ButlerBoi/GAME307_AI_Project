#include "Graph.h"

Graph::Graph()
{
}

Graph::~Graph()
{
}

bool Graph::onCreate(vector<Node*> nodes)
{
	int numNodes = nodes.size();
	cost.resize(numNodes);

	for (int i = 0; i < numNodes; i++) {
		node[i] = nodes[i];

		cost[i].resize(numNodes);

		for (int j = 0; j < numNodes; j++) {
			cost[i][j] = 0.0f;
		}
	}

	return true;
}

int Graph::numNodes()
{
	return node.size();
}

void Graph::addWeightConnection(int fromNode, int toNode, float weight)
{
	cost[fromNode][toNode] = weight;
}

vector<int> Graph::neighbours(int fromNode)
{
	vector<int> result = {};

	for (int j = 0; j < numNodes(); j++) {
		if (cost[fromNode][j] > 0.0f) {
			result.push_back(j);
		}
	}
	return result;
}

vector<int> Graph::Dijkstra(int startNode, int goalNode)
{
	float new_cost;

	NodeAndPriority* currentNodeAndPriority;
	currentNodeAndPriority = new NodeAndPriority(startNode, 0.0f);

	priority_queue<NodeAndPriority, deque<NodeAndPriority>, ComparePriority> frontier;
	frontier.push(*currentNodeAndPriority);

	vector<int> currentPath;

	vector<int> came_from;
	came_from.resize(numNodes());

	map<int, float> cost_so_far;
	cost_so_far[startNode] = 0.0f;

	while (!frontier.empty()) {
		int current = frontier.top().node;
		frontier.pop();

		float newCost;

		if (current == goalNode) {
			printf("goal reached\n");

			int i = goalNode;
			currentPath.push_back(goalNode);

			while (came_from[i] != startNode) {
				currentPath.insert(currentPath.begin(), came_from[i]);
				i = came_from[i];
			}
			currentPath.insert(currentPath.begin(), came_from[i]);

			return StraightPath(currentPath);
		}

		/*for (auto n : Graph::GetNeighbours(current)) {
			newCost = cost_so_far[current] + cost[current][n];
			if (cost_so_far[n] == 0.0f || newCost < cost_so_far[n]) {
				cost_so_far[n] = newCost;
				float priority = newCost + Heuristic(n, goalNode);
				frontier.push(NodeAndPriority(sceneNodes[n], priority));
				came_from[n] = current;
			}
		}*/
	}
	return came_from;
}

int Graph::NodeSearch(int label_)
{
	for (int n : sceneNodes) {
		if (n == label_) {
			return n;
		}
	}
	printf("label error");
	return 0;
}

vector<int> Graph::GetNeighbours(int currentNode_)
{
	vector<int> result = {};
	vector<int> toNodes = cost[currentNode_];

	for (int i = 0; 0 < toNodes.size(); i++) {
		if (cost[currentNode_][i] > 0.0f) {
			result.push_back(NodeSearch(i));
		}
	}
	return result;
}

vector<int> Graph::StraightPath(vector<int> inPath)
{
	if (inPath.size() <= 2) {
		return inPath;
	}

	vector<int> outPath;
	outPath.push_back(inPath[0]);

	int toPath = 2;
	int fromPath = 0;

	while (toPath < inPath.size()) {
		if (inPath[fromPath] == inPath[toPath]) {
			toPath++;
		}
		else {
			outPath.push_back(inPath[toPath - 1]);
			fromPath = toPath - 1;
			toPath++;
		}
	}
	outPath.push_back(inPath[toPath - 1]);
	return outPath;
}

float Graph::Heuristic(int node, int goalNode)
{
	float D = 1.0f;

	float d = abs(node - goalNode);

	return D * d;
}
