#include "MapCell.h"
#include"constants.h"



MapCell::MapCell(MapObject *v,int c)
{
	value = v;	
	coordinate.left= (int)c%width*blockSize;  
	coordinate.top = (int)c / width*blockSize;
	value->sprite.setPosition(coordinate.left, coordinate.top);
}

void MapCell::ChooseObject(MapObject*v)
{
	value = v;
	value->sprite.setPosition(coordinate.left, coordinate.top);
}
sf::Sprite MapCell::GetSprite()
{	
	return value->sprite;
}

MapCell::~MapCell()
{
}
