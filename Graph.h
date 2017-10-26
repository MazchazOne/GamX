#pragma once
#include"GraphEdge.h"
class Graph {
public:
	vector<GraphEdge*>Edges;
	int width;
	int height;
	Graph(int map[], int xI, int yI);
	stack<int>FindPath(int startIndex, int endIndex);
};