#include "menu/menuItems/TextMenuItem.hpp"

TextMenuItem::TextMenuItem(std::string str, m3d::Color color) : m3dCI::Text(str, color), MenuItem()
{

}

//Destructor: Objects that must be deleted when this object is deleted. Delete(nullptr) is fail-safe.
TextMenuItem::~TextMenuItem()
{

}

bool TextMenuItem::PointIntersection(int px, int py)
{
	return getBoundingBox().intersects(m3d::BoundingBox(px, py, 1, 1));
}