#include "StoneBlock.h"



StoneBlock::StoneBlock()
{
	StoneBlock::texture.loadFromFile("images/stone.png");
	StoneBlock::sprite.setTexture(texture);		
}


StoneBlock::~StoneBlock()
{
}
