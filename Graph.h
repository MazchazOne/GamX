#pragma once
#include"GraphEdge.h"
#include"constants.h"
class Graph {
public:
	vector<GraphEdge*>Edges;
	/*int width;
	int height;*/
	Graph(char map[]);
	stack<int>FindPath(int startIndex, int endIndex);
};