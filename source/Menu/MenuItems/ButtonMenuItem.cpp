#include "ButtonMenuItem.hpp"

#include "../../util.hpp"

//Creates a Rectangle to take the form of a button
ButtonMenuItem::ButtonMenuItem(int px, int py, int pw, int ph, m3d::Color p_innerColor, m3d::Color p_borderColor, int p_borderWidth = 3)
	: m3dCI::Button(px, py, pw, ph, p_innerColor, p_borderColor, p_borderWidth), MenuItem()
{
	m3d::Color iC = p_innerColor;
	m3d::Color darker = m3d::Color((int)(iC.getRed() * 0.9f), (int)(iC.getGreen() * 0.9f), (int)(iC.getBlue() * 0.9f), iC.getAlpha());
	SetOnTouch([&, p_innerColor, darker](int a, int b)
	{
		setInnerColor(darker);
	});
	
	SetOnHeldEnter([&,p_innerColor, darker](int a, int b)
	{
		setInnerColor(darker);
	});

	SetOnHeldLeave([&,p_innerColor](int a, int b)
	{
		setInnerColor(p_innerColor);
	});
}

//Creates a Sprite from a specific texture to take the form of a button
ButtonMenuItem::ButtonMenuItem(int px, int py, m3d::Texture& t_texture)
	: m3dCI::Button(px, py, t_texture), MenuItem()
{

}

//Uses a Sprite to take the form of a button
ButtonMenuItem::ButtonMenuItem(int px, int py, m3dCI::Sprite* psprite)
	: m3dCI::Button(px, py, psprite), MenuItem()
{

}

//Creates a Circle to take the form of a button
ButtonMenuItem::ButtonMenuItem(int px, int py, int pr, m3d::Color p_innerColor, m3d::Color p_borderColor, int p_borderWidth = 3)
	: m3dCI::Button(px, py, pr, p_innerColor, p_borderColor, p_borderWidth), MenuItem()
{

}

//Default Destructor. Objects that must be deleted when this object is deleted. Delete(nullptr) is fail-safe.
ButtonMenuItem::~ButtonMenuItem()
{

}

//Determine if a point intersects the Button
bool ButtonMenuItem::PointIntersection(int px, int py)
{
	if (buttonType == m3dCI::Rectangle || buttonType == m3dCI::SpriteObject)
		return getBoundingBox().intersects(m3d::BoundingBox(px, py, 1, 1));
	else if (buttonType == m3dCI::Circle)
	{ 
		//Circle bounding box is a box based at the center, but does not contain the bottom of the circle.
		//Therefore, a custom implementation was needed.

		int xDiff = x + (r)-px;
		int yDiff = y + (r)-py;
		
		if (pow(xDiff, 2) + pow(yDiff, 2) <= pow(r, 2))
		{
			return true;
		}
	}

	return false;
}

void ButtonMenuItem::SetActive(bool state)
{
	m3d::Color change = state?innerColor:m3d::Color(innerColor.getRed() * 0.6, innerColor.getGreen() * 0.6, innerColor.getBlue() * 0.6, innerColor.getAlpha());
	if (innerRectangle != nullptr)
		innerRectangle->setColor(change);
	if (innerCircle != nullptr)
		innerCircle->setColor(change);

	if (sprite != nullptr)
		sprite->setTint(m3d::Color(0, 0, 0, state?0:100));

	isActive = state;
}