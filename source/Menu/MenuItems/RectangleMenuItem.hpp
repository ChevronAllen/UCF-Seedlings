#pragma once
#include <m3dia.hpp>
#include "../MenuItem.hpp"

/**
	@brief The RectangleMenuItem is a combination of a m3dCI::Rectangle and a MenuItem
**/
class RectangleMenuItem : public m3d::Rectangle, public MenuItem
{
public:
	/**
		@brief Creates a RectangleMenuItem to be displayed
		@param x X position
		@param y Y position
		@param w Width of Rectangle
		@param h Height of Rectangle
		@param color Color of the Rectangle
	**/
	RectangleMenuItem(int x, int y, int w, int h, m3d::Color color);

	/**
		@brief Deconstructor for RectangleMenuItem.
		Responsible for deleting all needed children.
	**/
	~RectangleMenuItem();

	/**
		@brief Function responsible for determining Intersection between the object and a specific XY Coordinate
	**/
	bool PointIntersection(int px, int py);
};