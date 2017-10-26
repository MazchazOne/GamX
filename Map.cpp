#include "Map.h"
#include "constants.h"
#include <fstream>
#include<iostream>
#include <SFML/Graphics.hpp>
char Map::GetElement(int index)
{
	return map[index];
}
void Map::SetElement(int index, char value)
{
	map[index] = value;
}// ÝÒÎÒ ÎÒÑÒÎÉ ÓÁÐÀÒÜ È ÑÄÅËÀÒÜ ÍÎÐÌÀËÜÍÅ ÎÁÐÀÙÅÍÈÅ
Map::Map(std::string name)
{
	GetMapfromFile(name);
}
void Map::GetMapfromFile(std::string name )
{
	std::ifstream map1;
	map1.open(name);
	/*char input[width*height * 4];*/
	std::string newelement;
	int j = 0;
	while (!map1.eof())
	{
		map1 >> newelement;
		for (int i = 0; i < width; i++)
			map[i + j*width] = newelement[i];
		j++;
	}
	map1.close();
}
void Map::test(sf::Sprite* qwe)
{
	sf::Texture texture;
	texture.loadFromFile("images/sqad.png");

	for (int j = 0; j < height; j++)
		for (int i = 0; i < width; i++)
		{
			if (map[i + j*width] == '1')
			{
				qwe[i + j*width].setTexture(texture);//òàéë êàêîéíèòü
				qwe[i + j*width].setPosition(i*blockSize, j*blockSize);
			}

		}
}
/*bool IsBlock()
{}*/
