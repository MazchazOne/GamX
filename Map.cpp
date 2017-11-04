#include "Map.h"
#include "constants.h"
#include <fstream>
#include<iostream>
#include <SFML/Graphics.hpp>
//Map::map
std::vector<MapCell*> Map::map = {};
char Map::mapChar[width*height * 4] = {};
char Map::GetElement(int index)
{
	return mapChar[index];
}
/*void Map::SetElement(int index, char value)
{
	map[index] = value;
}*/// ÝÒÎÒ ÎÒÑÒÎÉ ÓÁÐÀÒÜ È ÑÄÅËÀÒÜ ÍÎÐÌÀËÜÍÅ ÎÁÐÀÙÅÍÈÅ
Map::Map(std::string name)
{
	GetMapfromFile(name);
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
	for (int i = 0; i < width*height * 4; i++) 
	{
		if (mapChar == "1")
			map[i] = new MapCell(new StoneBlock(), i);
	}
}