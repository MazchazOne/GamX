#include "StoneBlock.h"
sf::Texture StoneBlock::texture;
StoneBlock::StoneBlock()
{		
	sprite.setTexture(this->texture);		
}
StoneBlock::~StoneBlock()
{
}
