#pragma once
#include <vector>
#include <queue>
#include <unordered_set> 
#include <iostream>
#include<stack>
using namespace std;
class GraphEdge {
public:
	vector<GraphEdge*>neighbors;
	GraphEdge *PreviousEdge;
	int Coordinate;
	GraphEdge();
	GraphEdge(int input);
	GraphEdge(const GraphEdge &input);
	stack<int>CreatePath(GraphEdge* start, GraphEdge* end);
};

