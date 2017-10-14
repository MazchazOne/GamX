#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <fstream>
using namespace sf;
const int width = 68, height = 35,blockSize=20;//êàðòà
const char blockChar = '1'; char nothingChar = '0';

class Path
{public:
	static void ChangedCoordForNextStep(float*x, float* y, sf::FloatRect currentCoordIn, sf::FloatRect targetCoord)
	{
		sf::FloatRect currentCoord(currentCoordIn);
		currentCoord.left += currentCoord.width/2;
		currentCoord.top += currentCoord.height / 2;
		currentCoord.height = 4;
		currentCoord.width = 4;
		if (currentCoord.intersects(targetCoord))
		{
			*x = 0;
			*y = 0;
			return;
		}

		int Dx = abs(currentCoord.left - targetCoord.left);
			int Dy = abs(currentCoord.top - targetCoord.top);
			if (Dx > Dy)
			{
				if (currentCoord.left < targetCoord.left)
					*x += 0.05;
				else if (currentCoord.left > targetCoord.left)
					*x -= 0.05;
				else *x = 0;
				if (currentCoord.top < targetCoord.top)
					*y += 0.05;
				else if (currentCoord.top > targetCoord.top)
					*y -= 0.05;
				else *y = 0;
			}
			else
			{
				if (currentCoord.top < targetCoord.top)
					*y += 0.05;
				else if (currentCoord.top > targetCoord.top)
					*y -= 0.05;
				else *y = 0;
				if (!(currentCoord.intersects(targetCoord)) && (currentCoord.left < targetCoord.left))
					*x += 0.05;
				else if (currentCoord.left > targetCoord.left)
					*x -= 0.05;	
				else *x = 0;
			}
			
	}
};
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
	sf::FloatRect TargetPositionPoint;
	bool FolowingTarget = false;
	sf::FloatRect ActualPositionRect;
	float currentFrame;
	float Dx = 0, Dy=0;//set get 

	Unit(std::string pathForTexture)//?
	{
		unitImage.loadFromFile(pathForTexture);
		unitTexture.loadFromImage(unitImage);
		unitSprite.setTexture(unitTexture);
		unitSprite.setPosition(0,0);
		ActualPositionRect=sf::FloatRect(0, 0, 40, 40);
		FolowingTarget = false;
	}
	void SetTarget(int x,int y) 
	{
		TargetPositionPoint = sf::FloatRect(x, y, 1, 1);//zadat' netochnost'
		FolowingTarget = true;
	}
	void Step(float time,char* map) 
	{
		Path::ChangedCoordForNextStep(&Dx, &Dy, ActualPositionRect, TargetPositionPoint);
		//unitSprite.setPosition(unitSprite.getPosition().x + time*Dx,unitSprite.getPosition().y+Dy);	
		if (ActualPositionRect.intersects(TargetPositionPoint))
			FolowingTarget = false;
		if (FolowingTarget == true)
		{
			ActualPositionRect.top += time*Dy;
			CollisionOnY(map);
			ActualPositionRect.left += time*Dx;
			CollisionOnX(map);//time?;
			unitSprite.setPosition(ActualPositionRect.left, ActualPositionRect.top);
			Dx = 0; Dy = 0;			
		}
	}
	void CollisionOnY(char* map)
	{

		for (int j = ActualPositionRect.top / blockSize; j<(ActualPositionRect.top + ActualPositionRect.height) / blockSize; j++)
			for (int i = ActualPositionRect.left / blockSize; i<(ActualPositionRect.left + ActualPositionRect.width) / blockSize; i++)
			{
				if (map[i+width*j] == blockChar)
				{
					if (Dy>0)
					{
						ActualPositionRect.top = j * blockSize - ActualPositionRect.height;  Dy = 0;
					}
					else if (Dy<0)
					{
						ActualPositionRect.top = j*blockSize+ blockSize;   Dy = 0;
					}					
				}				
			}
	}
	void CollisionOnX(char* map)
	{

		for (int j = ActualPositionRect.top / blockSize; j<(ActualPositionRect.top + ActualPositionRect.height) / blockSize; j++)
			for (int i = ActualPositionRect.left / blockSize; i<(ActualPositionRect.left + ActualPositionRect.width) / blockSize; i++)
			{
				if (map[i + width*j] == blockChar)
				{				
					if (Dx>0)
					{
						ActualPositionRect.left = i * blockSize - ActualPositionRect.width; Dx = 0;
					}
					else if (Dx<0)
					{
						ActualPositionRect.left = i * blockSize + blockSize; Dx = 0;
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
		if (event.type == sf::Event::MouseButtonPressed&&event.mouseButton.button == sf::Mouse::Right/*&&timerForLeftMouseButton<=0*/)
		{
			int x = sf::Mouse::getPosition().x - window.getPosition().x - 7;
			int y = sf::Mouse::getPosition().y - window.getPosition().y - 31;
			unit.SetTarget(x, y);
			/*std::cout << sf::Mouse::getPosition().x-window.getPosition().x-7<<"   "<< sf::Mouse::getPosition().y-window.getPosition().y-31<<endl;
			cout << x / blockSize + width*y / blockSize<<"="<<x/blockSize<< width*(y / blockSize);*/
			
			//timerForLeftMouseButton = 20;
		}
		
		/*if (Keyboard::isKeyPressed(Keyboard::Right))
			unit.Dx = speed;
		if (Keyboard::isKeyPressed(Keyboard::Left))
			unit.Dx = -speed;
		if (Keyboard::isKeyPressed(Keyboard::Up))
			unit.Dy = -speed;
		if (Keyboard::isKeyPressed(Keyboard::Down))
			unit.Dy = speed;*/
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
		/*static sf::RectangleShape circle(sf::Vector2f(40, 40));
		circle.setPosition(sf::Vector2f(unit.ActualPositionRect.left, unit.ActualPositionRect.top));
		window.draw(circle);*/
		static sf::RectangleShape circle1(sf::Vector2f(2, 2));
		circle1.setPosition(sf::Vector2f(unit.TargetPositionPoint.left, unit.TargetPositionPoint.top));
		circle1.setFillColor(sf::Color::Red);
		window.draw(circle1);
		window.display();
	}

}