#pragma once
#include"GraphEdge.h"
#include"constants.h"
class Graph {
public:
	static vector<GraphEdge*>Edges;
	/*int width;
	int height;*/
	//Graph(char map[]);
	static char map[];
	static void LoadMap(char map[]);
	static void ReloadMap();	
	// in progress
	static stack<int>FindPath(int startIndex, int endIndex);
};
