#include "Unit.h"

Unit::Unit(std::string pathForTexture)
{
	unitImage.loadFromFile(pathForTexture);
	unitTexture.loadFromImage(unitImage);
	unitSprite.setTexture(unitTexture);
	unitSprite.setPosition(0, 0);
	ActualPositionRect = sf::FloatRect(0,0, 20, 20);
	UnitCenter = sf::FloatRect(ActualPositionRect.left, ActualPositionRect.top, 1, 1);
		//sf::FloatRect(ActualPositionRect.left + ActualPositionRect.width / 4,
	//	ActualPositionRect.top + ActualPositionRect.height / 4,
	//	/*ActualPositionRect.width/2*/1, /*ActualPositionRect.height/2*/1);
	FolowingTarget = false;
}
//stack<int>Unit::GetPath() {}
void Unit::SetTarget(int x, int y) //Target for movement
{
	int startBlockIndex=(int)UnitCenter.top/blockSize*width+(int)UnitCenter.left / blockSize;
	int endBlockIdex=y/blockSize*width+x/blockSize;
	path.FindPath(startBlockIndex,endBlockIdex);	
	TargetPositionPoint = sf::FloatRect(x, y, 1, 1);//zadat' netochnost'
	FolowingTarget = true;
}
void Unit::Step(float time)
{
	//handler for all path and create current chaging coord
	/*if (UnitCenter.intersects(TargetPositionPoint))
	{
		FolowingTarget = false;
	}*/
	if (FolowingTarget == true&&path.stepsStack.size()>=1)				//if unit out from target zone // start movement
	{

		path.ChangedCoordForNextStep(&Dx, &Dy, &UnitCenter, time);
		ActualPositionRect.left = UnitCenter.left;
		ActualPositionRect.top = UnitCenter.top;
		UnitCenter.top += Dy;	//move	y	
		CollisionOnY();					//collision y handler
		UnitCenter.left += Dx;//move x
		CollisionOnX();//time?;			//colision x handler		
		ActualPositionRect.left = UnitCenter.left;
		ActualPositionRect.top = UnitCenter.top;

		/*UnitCenter.left = ActualPositionRect.left + ActualPositionRect.width / 4;
		UnitCenter.top = ActualPositionRect.top + ActualPositionRect.height / 4;*/
			 
		/*	ActualPositionRect.width / 2, ActualPositionRect.height / 2);*/
		unitSprite.setPosition(ActualPositionRect.left, ActualPositionRect.top);//new coordinate for unit's sprite
		Dx = 0; Dy = 0;
	}
}
void Unit::CollisionOnY(/*char* map*/)
{	
	for (int j = ActualPositionRect.top / blockSize; 
		j < (ActualPositionRect.top + ActualPositionRect.height) / blockSize; j++)
		for (int i = ActualPositionRect.left / blockSize; 
			i < (ActualPositionRect.left + ActualPositionRect.width) / blockSize; i++)
		{
			if (Graph::map[i + width*j] == blockChar)
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
void Unit::CollisionOnX()
{	
	for (int j = ActualPositionRect.top / blockSize;
		j < (ActualPositionRect.top + ActualPositionRect.height) / blockSize; j++)
		for (int i = ActualPositionRect.left / blockSize; 
			i < (ActualPositionRect.left + ActualPositionRect.width) / blockSize; i++)
		{
			if (Graph::map[i + width*j] == blockChar)
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