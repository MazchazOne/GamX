#include "Graph.h"
Graph::Graph(char map[]) {
		for (int j = 0; j < height; j++)
			for (int i = 0; i < width; i++)
				Edges.push_back((new GraphEdge(i + j*width)));
		for (int j = 0; j < height; j++)
			for (int i = 0; i < width; i++)
			{
				if (i == 0)
					;
				else if (j == 0)
					;
				else if (i == width - 1)
					;
				else if (j == height - 1)
					;
				else
				{
					if (map[i + width*j + 1] == '0') Edges[i + j*width]->neighbors.push_back(Edges[i + width*j + 1]);
					if (map[i + width*j + -1] == '0') Edges[i + j*width]->neighbors.push_back(Edges[i + width*j - 1]);
					if (map[i + width*(j + 1)] == '0') Edges[i + j*width]->neighbors.push_back(Edges[i + width*(j + 1)]);
					if (map[i + width*(j - 1)] == '0') Edges[i + j*width]->neighbors.push_back(Edges[i + width*(j - 1)]);
				}
			}
	}
	stack<int>Graph::FindPath(int startIndex, int endIndex)
	{
		stack<int>path;
		GraphEdge* start = Edges[startIndex];
		start->PreviousEdge = start;
		//GraphEdge end(Edges[endIndex]);
		unordered_set<int> visited;
		queue<GraphEdge*> aroundEdges;
		//visited.insert(start->Coordinate);
		for (int i = 0; i < start->neighbors.size(); i++)
		{
			visited.insert(start->neighbors[i]->Coordinate);
			aroundEdges.push(start->neighbors[i]);
			start->neighbors[i]->PreviousEdge = start;
		}
		visited.insert(start->Coordinate);
		while (aroundEdges.size() != 0)
		{
			GraphEdge* current = aroundEdges.front();
			aroundEdges.pop();
			if (current == Edges[endIndex])
			{
				path = current->CreatePath(Edges[startIndex], Edges[endIndex]);
				break;
			}
			for (int i = 0; i < current->neighbors.size(); i++)
			{
				if (visited.count(current->neighbors[i]->Coordinate) == 0)
				{
					visited.insert(current->neighbors[i]->Coordinate);
					current->neighbors[i]->PreviousEdge = current;
					aroundEdges.push(current->neighbors[i]);
				}
			}
		}
		
		path.pop();
		return path;
	}
