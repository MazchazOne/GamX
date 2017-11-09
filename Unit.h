#pragma once
#include <SFML/Graphics.hpp>
#include"Path.h"
#include <stack>
#include "Object.h"
class Unit
{
public:
	struct backpack
	{
		double maxWeidth;//!!
		double currentWeidth;
		std::vector<Object*> content;
	};
	sf::Texture unitTexture;	
	sf::Sprite unitSprite;	
	sf::FloatRect TargetPositionPoint;
	bool FolowingTarget = false;
	sf::FloatRect ActualPositionRect;
	sf::FloatRect UnitCenter;//средний 	
	//float currentFrame;
	float Dx = 0, Dy = 0;//set get 
	Path path;//stack points fpr steps here	
	
	Unit(std::string pathForTexture);
	void SetTarget(int x, int y); //Target for movement
	void Step(float time);
	void CollisionOnY();
	void CollisionOnX();
};


