#pragma once
#include "MapObject.h"
#include "ResourseBlock.h"
class StoneBlock :
	public ResourseBlock
{
public:
	static sf::Texture texture;	
 	StoneBlock();
	~StoneBlock();
};