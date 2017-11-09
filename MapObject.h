#pragma once
#include <SFML/Graphics.hpp>
class MapObject
{
public:	
	// sf::Texture texture;
static sf::Texture texture;
sf::Sprite sprite;
	MapObject();
	~MapObject();
	//virtual operator char();
};