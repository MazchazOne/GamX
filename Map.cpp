#include "Map.h"
#include "constants.h"
#include <fstream>
#include <iostream>
#include <SFML/Graphics.hpp>
std::vector<MapCell*> Map::map = {};
char Map::mapChar[width*height * 4] = {};
char Map::GetElement(int index)
{
	return mapChar[index];
}
Map::Map(std::string name)
{
	GetMapfromFile(name);
	CreateMapFromCharMap();
}
void Map::GetMapfromFile(std::string name )
{
	std::ifstream mapInput;
	mapInput.open(name);
	std::string newelement;
	int j = 0;
	while (!mapInput.eof())
	{
		mapInput >> newelement;
		for (int i = 0; i < width; i++)
			mapChar[i + j*width] = newelement[i];
		j++;				
	}
	mapInput.close();
}
void Map::CreateMapFromCharMap()
{	
	for (int i = 0; i < width*height; i++) 
	{		
		if (mapChar[i] == nothingChar)
			map.push_back(new MapCell(new MapObject(), i));
		if (mapChar[i] == blockChar)
		{			
			map.push_back(new MapCell(new StoneBlock(), i));
		}
	}
}