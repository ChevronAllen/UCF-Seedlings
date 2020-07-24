#include "menu/menuItems/SpriteMenuItem.hpp"

SpriteMenuItem::SpriteMenuItem() : m3dCI::Sprite(), MenuItem()
{

}

SpriteMenuItem::SpriteMenuItem(const std::string& t_spriteSheet, int t_imageId) : m3dCI::Sprite(t_spriteSheet, t_imageId), MenuItem()
{

}

SpriteMenuItem::SpriteMenuItem(Sprite& sprite) : m3dCI::Sprite(sprite), MenuItem()
{
	setTint(m3d::Color(0, 0, 0,  100));
}

//Destructor: Objects that must be deleted when this object is deleted. Delete(nullptr) is fail-safe.
SpriteMenuItem::~SpriteMenuItem()
{

}

bool SpriteMenuItem::PointIntersection(int px, int py)
{
	return getBoundingBox().intersects(m3d::BoundingBox(px, py, 1, 1));
}

/**
	@brief Sets the active state of this MenuItem
	@param state Activity state
**/
void SpriteMenuItem::SetActive(bool state)
{
	isActive = state;

	if (state)
		setBlend(0);
	else
		setBlend(0.4f);
}