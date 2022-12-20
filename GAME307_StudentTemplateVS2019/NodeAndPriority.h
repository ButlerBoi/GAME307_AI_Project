#ifndef NODEANDPRIORITY_H
#define NODEANDPRIORITY_H

#include "Node.h"

class NodeAndPriority
{
public:
	int node;
	float priority;

	int getNode() { return node; }

	inline NodeAndPriority(int node_, float priority_) {
		node = node_;
		priority = priority_;
	}
};
#endif
