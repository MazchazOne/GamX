#pragma once
#include "MapObject.h"
#include "Object.h"
#include <iostream>

class MapCell
{
public:
	MapObject* value;	
	sf::FloatRect coordinate;
	std::vector<Object*>itemValue;
	MapCell(MapObject* v,int c );
	sf::Sprite GetSprite();
	void ChooseObject(MapObject*v);
	Object Things[20];
	~MapCell();
};

