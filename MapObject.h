#pragma once
#include "Point.h"
#include <SFML/Graphics.hpp>
class MapObject
{
public:	
	sf::Texture texture;
	sf::Sprite sprite;
	MapObject();
	~MapObject();
	//virtual operator char();
};