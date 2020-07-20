#pragma once
#include "../../m3diaLibCI/sprite.hpp"
#include "../../m3diaLibCI/text.hpp"
#include "../MenuItem.hpp"
#include "../../m3diaLibCI/button.hpp"

/**
	@brief The ButtonMenuItem is a combination of a m3dCI::Button and a MenuItem
**/
class ButtonMenuItem : public m3dCI::Button, public MenuItem
{
public:
	/**
		@brief Creates a ButtonMenuItem in using a two Rectangles
		@param px X position
		@param py Y position
		@param pw Width of Outer Rectangle
		@param ph Height of Outer Rectangle
		@param p_innerColor Color of Inner Rectangle
		@param p_borderColor Color of Outer Rectangle
		@param p_borderWidth Gap between the Outer and Inner Rectangles
	**/
	ButtonMenuItem(int px, int py, int pw, int ph, m3d::Color p_innerColor, m3d::Color p_borderColor, int p_borderWidth);

	/**
		@brief Creates a ButtonMenuItem using two Circles
		@param px X position
		@param py Y position
		@param pr Radius of Outer Circle
		@param p_innerColor Color of Inner Circle
		@param p_borderColor Color of Outer Circle
		@param p_borderWidth Gap between the Outer and Inner Circles
	**/
	ButtonMenuItem(int px, int py, int pr, m3d::Color p_innerColor, m3d::Color p_borderColor, int p_borderWidth);

	/**
		@brief Creates a ButtonMenuItem based off an existing m3dCI::Texture
		@param px X position
		@param py Y position
		@param t_texture Texture to use inside the Button
	**/
	ButtonMenuItem(int px, int py, m3d::Texture& t_texture);
	
	/**
		@brief Creates a ButtonMenuItem based off an existing m3dCI::Sprite
		@param px X position
		@param py Y position
		@param sprite Sprite to use inside the Button
	**/
	ButtonMenuItem(int px, int py, m3dCI::Sprite* sprite);

	/**
		@brief Deconstructor for ButtonMenuItem.
		Responsible for deleting all needed children.
	**/
	~ButtonMenuItem();

	/**
		@brief Function responsible for determining Intersection between the object and a specific XY Coordinate
	**/
	bool PointIntersection(int px, int py);


	/**
		@brief Sets the active state of this MenuItem
		@param state Activity state
	**/
	void SetActive(bool state);
};