#include "menu/menuItems/RectangleMenuItem.hpp"

//Creates a Rectangle to take the form of a button

RectangleMenuItem::RectangleMenuItem(int x, int y, int w, int h, m3d::Color color) :
	m3d::Rectangle(x, y, w, h, color), MenuItem()
{
	
}

//Destructor: Objects that must be deleted when this object is deleted. Delete(nullptr) is fail-safe.
RectangleMenuItem::~RectangleMenuItem()
{

}

bool RectangleMenuItem::PointIntersection(int px, int py)
{
	return getBoundingBox().intersects(m3d::BoundingBox(px, py, 1, 1));
}