#pragma once
#include "MapObject.h"
#include "Object.h"
#include <iostream>
class MapCell
{
public:
	MapObject* value;	
	int coordinate;
	std::vector<Object*>itemValue;
	MapCell(MapObject *v,int c );
	~MapCell();
};

