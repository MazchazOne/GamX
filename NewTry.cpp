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
	void test(sf::Sprite* qwe)
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
};

class Unit
{
public:	
	sf::Texture unitTexture;
	sf::Image unitImage;
	sf::Sprite unitSprite;
	int pixelsSizeX = 40;
	int pixelsSizeY = 40;
	sf::FloatRect PhisicRect;
	float currentFrame;
	float Dx = 0, Dy=0;//set get
	Unit(std::string pathForTexture)//?
	{
		unitImage.loadFromFile(pathForTexture);
		unitTexture.loadFromImage(unitImage);
		unitSprite.setTexture(unitTexture);
		unitSprite.setPosition(0,0);
		PhisicRect=sf::FloatRect(0, 0, 40, 40);
	}
	void Step(float time,char* map) 
	{	



		//unitSprite.setPosition(unitSprite.getPosition().x + time*Dx,unitSprite.getPosition().y+Dy);
		PhisicRect.left += time*Dx;
		Collision(map);

		PhisicRect.top += time*Dy;		
		Collision(map);//time?;
		unitSprite.setPosition(PhisicRect.left, PhisicRect.top);
		Dx = 0; Dy = 0;
	}
	void Collision(char* map)
	{

		for (int j = PhisicRect.top / blockSize; j<(PhisicRect.top + PhisicRect.height) / blockSize; j++)
			for (int i = PhisicRect.left / blockSize; i<(PhisicRect.left + PhisicRect.width) / blockSize; i++)
			{
				if (map[i+width*j] == '0') 
				{
					if (Dy>0)
					{
						PhisicRect.top = j * blockSize - PhisicRect.height;  Dy = 0;
					}
					else if (Dy<0)
					{
						PhisicRect.top = j*blockSize+ blockSize;   Dy = 0;
					}
					else if (Dx>0 )
					{
						PhisicRect.left = i * blockSize-PhisicRect.width;Dx=0;
					}
					else if (Dx<0 )
					{
						PhisicRect.left = i * blockSize+blockSize;Dx=0;
					}
				}				
			}

	}

};
void main() 
{	//////////test sozdat' mapy texturkoy dlya oobrabotki colizii

	//sf::Sprite test[width*height * 4];

	//////
	Map *zap= new Map();

	//zap->test(test);

	float speed = 0.05;
	int delay =300;
	sf::RenderWindow	 window(sf::VideoMode(width*blockSize, height*blockSize), "SFML works!");
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
		
		if (Keyboard::isKeyPressed(Keyboard::Right))
			unit.Dx = speed;
		if (Keyboard::isKeyPressed(Keyboard::Left))
			unit.Dx = -speed;
		if (Keyboard::isKeyPressed(Keyboard::Up))
			unit.Dy = -speed;
		if (Keyboard::isKeyPressed(Keyboard::Down))
			unit.Dy = speed;
		unit.Step(time,zap->map);
		window.clear();
		//std::cout << ;
		
		
		for (int j = 0; j < height; j++)
		{
			for (int i = 0; i < width; i++)
				/*window.draw(test[i + j*width]);*/
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