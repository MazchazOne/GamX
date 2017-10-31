#include <iostream>
#include "constants.h"
#include "Unit.h"
#include "Path.h"
#include "Map.h"
#include "Graph.h"
//#include"GraphEdge.h"
void main() 
{
	Map *zap = new Map();	//create map
	////////TEST PATH
	//Path pathTest;	
	//pathTest.InitPMap(zap->map);
	//
	//std::cout << pathTest.fortest;
	//////////TEST PATH
	Graph::LoadMap(zap->map);
	double deleteme = 1;
	int delay =300;														//time delay for next step
	sf::RenderWindow window(
		sf::VideoMode(width*blockSize, height*blockSize), "SFML works!");//create window
	sf::Clock clock;														
	Unit unit("images/sqad.png");										//create mainPerson
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


////

		if (event.type == sf::Event::MouseButtonPressed&&event.mouseButton.button == sf::Mouse::Right&&deleteme>=1)//let coordinateRight click to current unit
		{
			int x = sf::Mouse::getPosition().x - window.getPosition().x - 7;
			int y = sf::Mouse::getPosition().y - window.getPosition().y - 31;
			unit.SetTarget(x, y);	
			//deleteme=-160;
			Graph::LoadMap(zap->map);
		}	
		deleteme += 0.5;
		unit.Step(time);					//here array with all units...they will do their step /// now just 1 unit
		window.clear();		
		/////////DRAW MAP//////// затоклнуть в метод карты...
		for (int j = 0; j < height; j++)
		{
			for (int i = 0; i < width; i++)				
				if ( zap->GetElement(i + j*width)== '1')
				{
					static sf::RectangleShape Rectangle(sf::Vector2f(blockSize, blockSize));
					Rectangle.setPosition(sf::Vector2f(i*blockSize, j*blockSize));
					window.draw(Rectangle);
				}
		}
		///////////////////////
		window.draw(unit.unitSprite);// win will draw all units from array.. now just 1 		
		static sf::RectangleShape circle1(sf::Vector2f(2, 2));											//
		circle1.setPosition(sf::Vector2f(unit.TargetPositionPoint.left, unit.TargetPositionPoint.top));	// draw current unit's target as red circle
		circle1.setFillColor(sf::Color::Red);															//
		window.draw(circle1);						
		window.display();
		window.clear();
		




		//TEST Path///
		/*while (1!=0)
		for (int z = 1000; z > 500; z -= 5)
		{
			for (int j = 0; j < height; j++)
			{
				for (int i = 0; i < width; i++)
					if (pathTest.PMap[i + j*width] >= z)
					{
						sf::RectangleShape Rectangle(sf::Vector2f(blockSize, blockSize));
						Rectangle.setPosition(sf::Vector2f(i*blockSize, j*blockSize));
						Rectangle.setFillColor(sf::Color(pathTest.PMap[i + j*width],0.0,0.0));
						window.draw(Rectangle);}
					
					else if (pathTest.PMap[i + j*width] <= 0)
					{
						sf::RectangleShape Rectangle(sf::Vector2f(blockSize, blockSize));
						Rectangle.setPosition(sf::Vector2f(i*blockSize, j*blockSize));
						Rectangle.setFillColor(sf::Color::Color(0.0, 0.0, 0.21*pathTest.PMap[i + j*width]));
						window.draw(Rectangle);
					}
			}window.display();
			window.clear();
		}*/

		////////////
	}

};