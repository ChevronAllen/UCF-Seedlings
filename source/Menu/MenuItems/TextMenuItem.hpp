#pragma once
#include "../../m3diaLibCI/text.hpp"
#include "../MenuItem.hpp"

/**
	@brief The TextMenuItem is a combination of a m3dCI::Text object and a MenuItem
**/
class TextMenuItem : public m3dCI::Text, public MenuItem
{
private:

public:
	/**
		@brief Creates a TextMenuItem to display
		@param str Text to display
		@param color Font color
	**/
	TextMenuItem(std::string str, m3d::Color color = m3d::Color(255, 255, 255));

	/**
		@brief Deconstructor for TextMenuItem.
		Responsible for deleting all needed children.
	**/
	~TextMenuItem();

	/**
		@brief Function responsible for determining Intersection between the object and a specific XY Coordinate
	**/
	bool PointIntersection(int px, int py);
};