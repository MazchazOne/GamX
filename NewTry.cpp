#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <fstream>
using namespace sf;
const int width = 68, height = 35,blockSize=20;//Map
const char blockChar = '1'; char nothingChar = '0';//designations for map

class Path //PAtch handler // graphs coming soon
{public:
	const int maxPotential = 1000;
	const int minPotential = -500;
	const int aroundMin = -250;
	int PMap[height*width*4];
	int priorityDifferenceFromTarget=5;

	//ПОДУМАТЬ НАД АРГУМЕНТАМИ и конструктором И УБРАТЬ ЧАСТЬ переменных из класса 
	int fortest=0;
	bool passedPoints[height*width * 4];	
	sf::Vector2<int> targetPosition= Vector2<int>(372/blockSize,319/blockSize);///// координаты таргета 
	void qwe(sf::Vector2<int> point, int potentialForCurrentPoint)////рекурсивный метод для заполнения положительным приоритетом
	{fortest++;
		if (PMap[point.x + point.y*width] >= potentialForCurrentPoint)
			return;
		if (PMap[point.x + point.y*width] == minPotential)
			return;
		PMap[point.x + point.y*width] = potentialForCurrentPoint;//что-то нужно с этим делать по идее должно быть +=
		/*passedPoints[point.x + point.y*width] = true;
		passedPoints[point.x + (point.y - 1)*width] = true;
		passedPoints[point.x + (point.y +1)*width] = true;
		passedPoints[point.x +1+ (point.y )*width] = true;
		passedPoints[point.x -1+ (point.y )*width] = true;
		*/
		if (point.x == 0||point.x==width-1||point.y==0||point.y==height-1)
			return;
		qwe(sf::Vector2<int>(point.x-1, point.y), potentialForCurrentPoint - priorityDifferenceFromTarget);
		qwe(sf::Vector2<int>(point.x+1, point.y), potentialForCurrentPoint - priorityDifferenceFromTarget);
		qwe(sf::Vector2<int>(point.x, point.y-1), potentialForCurrentPoint - priorityDifferenceFromTarget);
		qwe(sf::Vector2<int>(point.x, point.y+1), potentialForCurrentPoint - priorityDifferenceFromTarget);

	}
	void InitPMap(char map[width*height*4]) 
	{////////assign 0 for each element from potential array 
		for (int j = 0; j < height; j++)
			for (int i = 0; i < width; i++)
				PMap[i + j*width] = 0;
		////////////

		////////////////////////assign negative potential
		for(int j=1;j<height;j++)
			for (int i = 1; i < width; i++)
			{
				if (map[i + width*j] == blockChar)
				{
					PMap[i + width*j] = minPotential;
					if (PMap[i + width*j + 1] == 0)
						PMap[i + width*j + 1] = aroundMin;
					if (PMap[i + width*j - 1] == 0)
						PMap[i + width*j - 1] = aroundMin;
					if (PMap[i + width*(j + 1)] == 0)
						PMap[i + width*(j + 1)] = aroundMin;
					if (PMap[i + width*(j - 1)] == 0)
						PMap[i + width*(j - 1)] = aroundMin;
				}
			}
		////////////////////////assign positive potential for target and block around target
		//PMap[targetPosition.x+width*targetPosition.y] = maxPotential;
		qwe(targetPosition, maxPotential);
		////////////////////////
	}
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
class Map // NEED RECREATE THIS CLASS
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
		return map;   !!!!!!!!!!!!!!!!!!!!!!!!КАК СДЕЛАТЬ ПЕРЕДАЧУ ссылку НА МАССИВ ? И\ИЛИ НОРМАЛЬНЫЙ ОПЕРАТОР []
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
	}// ЭТОТ ОТСТОЙ УБРАТЬ И СДЕЛАТЬ НОРМАЛЬНЕ ОБРАЩЕНИЕ
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
					qwe[i + j*width].setTexture(texture);//тайл какойнить
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

	Unit(std::string pathForTexture)
	{
		unitImage.loadFromFile(pathForTexture);
		unitTexture.loadFromImage(unitImage);
		unitSprite.setTexture(unitTexture);
		unitSprite.setPosition(0,0);
		ActualPositionRect=sf::FloatRect(0, 0, 40, 40);
		FolowingTarget = false;
	}
	void SetTarget(int x,int y) //Target for movement
	{
		TargetPositionPoint = sf::FloatRect(x, y, 1, 1);//zadat' netochnost'
		FolowingTarget = true;
	}
	void Step(float time,char* map) 
	{
			//handler for all path and create current chaging coord
		if (ActualPositionRect.intersects(TargetPositionPoint))		
			FolowingTarget = true;
		if (FolowingTarget == true)				//if unit out from target zone // start movement
		{
			Path::ChangedCoordForNextStep(&Dx, &Dy, ActualPositionRect, TargetPositionPoint);
			ActualPositionRect.top += time*Dy;	//move	y	
			CollisionOnY(map);					//collision y handler
			ActualPositionRect.left += time*Dx;//move x
			CollisionOnX(map);//time?;			//colision x handler
			unitSprite.setPosition(ActualPositionRect.left, ActualPositionRect.top);//new coordinate for unit's sprite
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
{
	
	Map *zap = new Map();	//create map
	////////TEST PATH
	Path pathTest;	
	pathTest.InitPMap(zap->map);
	
	std::cout << pathTest.fortest;
	////////TEST PATH


	int delay =300;														//time delay for next step
	sf::RenderWindow window(sf::VideoMode(width*blockSize, height*blockSize), "SFML works!");//create window
	Clock clock;														
	Unit unit("images/hero.png");										//create mainPerson
	while (window.isOpen())										//Game loop/main loop
	{
		float time = clock.getElapsedTime().asMicroseconds();
		time = time/delay;										//get time for other func
		clock.restart();
		sf::Event event;										
		while (window.pollEvent(event))							//event handler
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}
		//if (event.type == sf::Event::MouseButtonPressed&&event.mouseButton.button == sf::Mouse::Right)//let coordinateRight click to current unit
		//{
		//	int x = sf::Mouse::getPosition().x - window.getPosition().x - 7;
		//	int y = sf::Mouse::getPosition().y - window.getPosition().y - 31;
		//	unit.SetTarget(x, y);	
		//}			
		//unit.Step(time,zap->map);					//here array with all units...they will do their step /// now just 1 unit
		//window.clear();		
		///////////DRAW MAP//////// затоклнуть в метод карты...
		//for (int j = 0; j < height; j++)
		//{
		//	for (int i = 0; i < width; i++)				
		//		if ( zap->GetElement(i + j*width)== '1')
		//		{
		//			static sf::RectangleShape Rectangle(sf::Vector2f(blockSize, blockSize));
		//			Rectangle.setPosition(sf::Vector2f(i*blockSize, j*blockSize));
		//			window.draw(Rectangle);
		//		}
		//}
		/////////////////////////
		//window.draw(unit.unitSprite);// win will draw all units from array.. now just 1 		
		//static sf::RectangleShape circle1(sf::Vector2f(2, 2));											//
		//circle1.setPosition(sf::Vector2f(unit.TargetPositionPoint.left, unit.TargetPositionPoint.top));	// draw current unit's target as red circle
		//circle1.setFillColor(sf::Color::Red);															//
		//window.draw(circle1);						
		//window.display();
		


		//TEST Path///
		for (int j = 0; j < height; j++)
			{
				for (int i = 0; i < width; i++)				
					if ( pathTest.PMap[i + j*width]>=995)
					{
						sf::RectangleShape Rectangle(sf::Vector2f(blockSize, blockSize));
						Rectangle.setPosition(sf::Vector2f(i*blockSize, j*blockSize));
						Rectangle.setFillColor(sf::Color::Red);
						window.draw(Rectangle);
					}
					else if (pathTest.PMap[i + j*width]<=0)
					{
						sf::RectangleShape Rectangle(sf::Vector2f(blockSize, blockSize));
						Rectangle.setPosition(sf::Vector2f(i*blockSize, j*blockSize));
						Rectangle.setFillColor(sf::Color::Color(0.0, 0.0, 0.21*pathTest.PMap[i + j*width]));
						window.draw(Rectangle);
					}
			}window.display();
		////////////
	}

};