#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
using namespace sf;

class Map 
{	public:

	Map(std::string name) 
	{}
	void GetMapfromFile(String name)
	{}
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
		window.draw(unit.unitSprite);
		window.display();
	}

}