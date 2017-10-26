#include "Unit.h"
#include <SFML/Graphics.hpp>
#include "constants.h"
#include "Path.h"
Unit::Unit(std::string pathForTexture)
{
	unitImage.loadFromFile(pathForTexture);
	unitTexture.loadFromImage(unitImage);
	unitSprite.setTexture(unitTexture);
	unitSprite.setPosition(0, 0);
	ActualPositionRect = sf::FloatRect(0, 0, 40, 40);
	FolowingTarget = false;
}
void Unit::SetTarget(int x, int y) //Target for movement
{
	TargetPositionPoint = sf::FloatRect(x, y, 1, 1);//zadat' netochnost'
	FolowingTarget = true;
}
void Unit::Step(float time, char* map)
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
void Unit::CollisionOnY(char* map)
{

	for (int j = ActualPositionRect.top / blockSize; j < (ActualPositionRect.top + ActualPositionRect.height) / blockSize; j++)
		for (int i = ActualPositionRect.left / blockSize; i < (ActualPositionRect.left + ActualPositionRect.width) / blockSize; i++)
		{
			if (map[i + width*j] == blockChar)
			{
				if (Dy > 0)
				{
					ActualPositionRect.top = j * blockSize - ActualPositionRect.height;  Dy = 0;
				}
				else if (Dy < 0)
				{
					ActualPositionRect.top = j*blockSize + blockSize;   Dy = 0;
				}
			}
		}
}
void Unit::CollisionOnX(char* map)
{

	for (int j = ActualPositionRect.top / blockSize; j < (ActualPositionRect.top + ActualPositionRect.height) / blockSize; j++)
		for (int i = ActualPositionRect.left / blockSize; i < (ActualPositionRect.left + ActualPositionRect.width) / blockSize; i++)
		{
			if (map[i + width*j] == blockChar)
			{
				if (Dx > 0)
				{
					ActualPositionRect.left = i * blockSize - ActualPositionRect.width; Dx = 0;
				}
				else if (Dx < 0)
				{
					ActualPositionRect.left = i * blockSize + blockSize; Dx = 0;
				}
			}
		}
}

