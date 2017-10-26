#pragma once
#include <SFML/Graphics.hpp>
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
	float Dx = 0, Dy = 0;//set get 

	Unit(std::string pathForTexture);
	void SetTarget(int x, int y); //Target for movement
	void Step(float time, char* map);
	void CollisionOnY(char* map);
	void CollisionOnX(char* map);
};


