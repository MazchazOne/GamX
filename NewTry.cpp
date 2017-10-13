#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <fstream>
using namespace sf;
const int width = 68, height = 35,blockSize=20;//êàðòà

class Map 
{	public:
	char map[width*height * 4];
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
	char GetElement(int index)
	{
		return map[index];
	}
	void SetElement(int index, char value)
	{
		map[index] = value;
	}// ÝÒÎÒ ÎÒÑÒÎÉ ÓÁÐÀÒÜ È ÑÄÅËÀÒÜ ÍÎÐÌÀËÜÍÅ ÎÁÐÀÙÅÍÈÅ
	Map(std::string name= "MAP.txt")
	{
		GetMapfromFile(name);
	}
	void GetMapfromFile(std::string name="MAP.txt")
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
	/*bool IsBlock()
	{}*/
};

class Unit
{
public:	
	sf::Texture unitTexture;
	sf::Image unitImage;
	sf::Sprite unitSprite;
	Unit(std::string pathForTexture)//?
	{
		unitImage.loadFromFile(pathForTexture);
		unitTexture.loadFromImage(unitImage);
		unitSprite.setTexture(unitTexture);
		unitSprite.setPosition(0, 0);
	}


};
void main() 
{
	Map *zap= new Map();
	float speed = 0.05;
	int delay =300;
	sf::RenderWindow	 window(sf::VideoMode(800, 600), "SFML works!");
	//sf::CircleShape octagon(80, 8);
	sf::CircleShape octagon(50);
	//octagon.setPosition(20, 20);
	Clock clock;
	Unit unit("images/hero.png");

	while (window.isOpen())
	{
		float time = clock.getElapsedTime().asMicroseconds();
		time = time/delay;
		clock.restart();
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}
		/*if (Keyboard::isKeyPressed(Keyboard::Right))
			octagon.setPosition(octagon.getPosition().x+ time*speed, octagon.getPosition().y);
		if (Keyboard::isKeyPressed(Keyboard::Left))
			octagon.setPosition(octagon.getPosition().x - time*speed, octagon.getPosition().y);
		if (Keyboard::isKeyPressed(Keyboard::Up))
			octagon.setPosition(octagon.getPosition().x , octagon.getPosition().y- time*speed);
		if (Keyboard::isKeyPressed(Keyboard::Down))
			octagon.setPosition(octagon.getPosition().x, octagon.getPosition().y + time*speed);
*/

		if (Keyboard::isKeyPressed(Keyboard::Right))
			unit.unitSprite.setPosition(unit.unitSprite.getPosition().x + time*speed, unit.unitSprite.getPosition().y);
		if (Keyboard::isKeyPressed(Keyboard::Left))
			unit.unitSprite.setPosition(unit.unitSprite.getPosition().x - time*speed, unit.unitSprite.getPosition().y);
		if (Keyboard::isKeyPressed(Keyboard::Up))
			unit.unitSprite.setPosition(unit.unitSprite.getPosition().x , unit.unitSprite.getPosition().y-time*speed);
		if (Keyboard::isKeyPressed(Keyboard::Down))
			unit.unitSprite.setPosition(unit.unitSprite.getPosition().x , unit.unitSprite.getPosition().y+time*speed);
		window.clear();
		std::cout <<unit.unitSprite.getPosition().x<<"     ";
		
		
		for (int j = 0; j < height; j++)
		{
			for (int i = 0; i < width; i++)
				if ( zap->GetElement(i + j*width)== '1')
				{
					static sf::RectangleShape circle(sf::Vector2f(blockSize, blockSize));
					circle.setPosition(sf::Vector2f(i*blockSize, j*blockSize));
					window.draw(circle);
				}
		}
		window.draw(unit.unitSprite);
		window.display();
	}

}