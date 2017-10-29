#include "GraphEdge.h"

using namespace std;


GraphEdge::GraphEdge() { neighbors.reserve(10); }
GraphEdge::GraphEdge(int input) {
	Coordinate = input;
	neighbors.reserve(10);
	//PreviousEdge = this;
}
GraphEdge::GraphEdge(const GraphEdge &input) {
	//neighbors = input.neighbors;
	//PreviousEdge = this;
	Coordinate = input.Coordinate;
	neighbors.reserve(10);
}
stack<int>GraphEdge::CreatePath(GraphEdge* start, GraphEdge* end) {
	stack <int>Path;
	GraphEdge* current = end;
	while (current->PreviousEdge != current)
	{
		Path.push(current->Coordinate);
		current = current->PreviousEdge;
	}
	Path.push(start->Coordinate);
	return Path;
}
