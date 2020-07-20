#pragma once
#include "../../m3diaLibCI/sprite.hpp"
#include "../MenuItem.hpp"

/**
	@brief The SpriteMenuItem is a combination of a m3dCI::Sprite and a MenuItem
**/
class SpriteMenuItem : public m3dCI::Sprite, public MenuItem
{
public:
	/**
		@brief Creates a blank SpriteMenuItem
	**/
	SpriteMenuItem();
	
	/**
		@brief Creates a SpriteMenuItem from a SpriteSheet given an ID and SpriteSheet Location
		@param t_spriteSheet Location of SpriteSheet
		@param t_imageId ID of the specific Sprite inside the SpriteSheet
	**/
	SpriteMenuItem(const std::string& t_spriteSheet, int t_imageId);
	
	/**
		@brief Creates a SpriteMenuItem using an existing Sprite
		@param sprite Sprite Object to use.
	**/
	SpriteMenuItem(Sprite& sprite);

	/**
		@brief Deonstructor for SpriteMenuItem.
		Responsible for deleting all needed children.
	**/
	~SpriteMenuItem();

	/**
		@brief Function responsible for determining Intersection between the object and a specific XY Coordinate
	**/
	bool PointIntersection(int px, int py);
};