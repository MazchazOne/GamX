#pragma once
#include "constants.h"
#include <fstream>
#include <iostream>
#include <SFML/Graphics.hpp>
#include "BlocksHeader.h"
class Map
{
public:
	static char mapChar[width*height * 4];	
	static std::vector<MapCell*> map;
	static char GetElement(int index);		
	Map(std::string name = "MAP.txt");	
	static void GetMapfromFile(std::string name = "MAP.txt");	
	static void CreateMapFromCharMap();	
};