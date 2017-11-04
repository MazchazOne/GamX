#pragma once
#include "constants.h"
#include <fstream>
#include<iostream>
#include <SFML/Graphics.hpp>
#include "MapCell.h"
#include "StoneBlock.h"
class Map // NEED RECREATE THIS CLASS
{
public:
	static char mapChar[width*height * 4];
	/*void DisplayMap()
	{
	for (int j = 0; j < height; j++)
	{
	for (int i = 0; i < width; i++)
	if (map[i + j*width] == '1')
	{
	static sf::RectangleShape circle(sf::Vector2f(blockSize, blockSize));
	circle.setPosition(sf::Vector2f(i*blockSize, j*blockSize));
	window.draw(circle);
	}
	}
	}*/
	/*char* getArray ()
	{
	return map;   !!!!!!!!!!!!!!!!!!!!!!!!ÊÀÊ ÑÄÅËÀÒÜ ÏÅÐÅÄÀ×Ó ññûëêó ÍÀ ÌÀÑÑÈÂ ? È\ÈËÈ ÍÎÐÌÀËÜÍÛÉ ÎÏÅÐÀÒÎÐ []
	}
	char* Array ()
	{
	return map;
	}*/
	static std::vector<MapCell*> map;
	static char GetElement(int index);	
	//void SetElement(int index, char value);
	Map(std::string name = "MAP.txt");	
	static void GetMapfromFile(std::string name = "MAP.txt");	
	void CreateMapFromCharMap();
	//void test(sf::Sprite* qwe);	
	/*bool IsBlock()
	{}*/
};