#pragma once
#include "text.hpp"
#include <citro2d.h>
#include <string>
#include <3ds.h>
#include <m3dia.hpp>
#include <cmath>
#include <algorithm>

namespace m3dCI
{
    /**
		@brief A Item displaying a type of CommandObject
		Based off of m3d::Drawable
     */
	class commandListerItem
	{
	private:
		m3d::Rectangle* backgroundRectangle = nullptr;
		m3dCI::Text* commandTextObject = nullptr;

	public:
		/** @brief Create a CommandListerItem.
			@param x X position
			@param y Y position
			@param w Width of CommandListerItem
			@param h Height of CommandListerItem
			@param command Title of command
			@param selected Is this the selected command (scrapped)
		**/
		commandListerItem(int x, int y, int w, int h, std::string command, bool selected);
		
		/**
			@brief Deconstructor for CommandListerItem.
			Responsible for deleting all needed children.
		**/
		~commandListerItem();

		/**
			@brief Draw the CommandListerItem
			@param t_context The context to draw in
		**/
		void draw(m3d::RenderContext t_context);
		
		/**
			@brief Sets the background color of the CommandListerItem
			@param color Background Color
		**/
		void setBackgroundColor(m3d::Color color);
		
		/**
			@brief Sets the position of the CommandListerItem
			@param x X position
			@param y Y position
		**/
		void setPosition(int x, int y);
	};
}