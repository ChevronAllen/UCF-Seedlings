#pragma once

#include "sprite.hpp"
#include "text.hpp"

#include <citro2d.h>
#include <string>
#include <3ds.h>
#include <m3dia.hpp>
#include <cmath>

namespace m3dCI 
{
	enum ButtonType { Rectangle, Circle, SpriteObject };
	
	/**
		@brief A Button object used for displaying "Button"-like objects from Sprites/Rectangles/Circles
		Based off the m3diaLib Drawable class
	**/
    class Button: public m3d::Drawable
	{
		protected:
			m3d::Rectangle* innerRectangle = nullptr;
			m3d::Rectangle* outerRectangle = nullptr;
			m3d::Circle* innerCircle = nullptr;
			m3d::Circle* outerCircle = nullptr;

			m3dCI::Sprite* sprite = nullptr;

			m3dCI::Text* text = nullptr;
			ButtonType buttonType;

			m3d::Color innerColor, outerColor, *disabledColor = nullptr;

			int x, y, borderWidth, w, h, r;

			void UpdateShape();
		public:
			/**
				@brief Creates a Button in using a two Rectangles
				@param px X position
				@param py Y position
				@param pw Width of Outer Rectangle
				@param ph Height of Outer Rectangle
				@param p_innerColor Color of Inner Rectangle
				@param p_borderColor Color of Outer Rectangle
				@param p_borderWidth Gap between the Outer and Inner Rectangles
			**/
			Button(int px, int py, int pw, int ph, m3d::Color p_innerColor, m3d::Color p_borderColor, int p_borderWidth);
			
			/**
				@brief Creates a Button using two Circles
				@param px X position
				@param py Y position
				@param pr Radius of Outer Circle
				@param p_innerColor Color of Inner Circle
				@param p_borderColor Color of Outer Circle
				@param p_borderWidth Gap between the Outer and Inner Circles
			**/
			Button(int px, int py, int pr, m3d::Color p_innerColor, m3d::Color p_borderColor, int p_borderWidth);

			/**
				@brief Creates a Button based off an existing m3dCI::Texture
				@param px X position
				@param py Y position
				@param t_texture Texture to use inside the Button
			**/
			Button(int px, int py, m3d::Texture& t_texture);
			
			/**
				@brief Creates a Button based off an existing m3dCI::Sprite
				@param px X position
				@param py Y position
				@param sprite Sprite to use inside the Button
			**/
			Button(int px, int py, m3dCI::Sprite* sprite);
			
			/**
				@brief Deconstructor for Button.
				Responsible for deleting all needed children.
			**/
			virtual ~Button();
			
			/** 
				@brief The function which is called when the touch event is touched over the button.
				Called if a single touch is over the button and the touch happened on the same frame
				
				SHOULD BE REPLACED BY MenuItem OnTouch
			**/
			std::function<void()> OnTouch;
			
			/** 
				@brief The function which is called when the touch event is released over the button.
				Called if a single touch is over the button and the touch happened on the same frame
				
				SHOULD BE REPLACED BY MenuItem OnRelease
			**/
			std::function<void()> OnRelease;
			
			/** 
				@brief The function which is called when the touch event is held over the button.
				Called when a touch is over a button, but the initial touch did not happen on the frame being called
				
				SHOULD BE REPLACED BY MenuItem OnHeld
			**/
			std::function<void()> OnHeld;
			
			/**
				@brief Function responsible for determining Intersection between the object and a specific XY Coordinate
				
				SHOULD BE REPLACED BY MenuItem PointIntersects
			**/
			bool PointIntersects(int x, int y);
			
			/**
				@brief Draw the Button
				@param t_context Context to draw the Button in
			**/
			void draw(m3d::RenderContext t_context);
			
			
			/**
				@brief Sets a text object's text to be displayed inside the center of the Button
				The Text objects creation/deletion is handle automatically
				@param txt The text to display
			**/
			void SetText(std::string txt);
			
			/**
				@brief Sets a text object's font color
				The Text objects creation/deletion is handle automatically
				@param color The font color
			**/
			void SetTextColor(m3d::Color color);
			
			/**
				@brief The following functions are all child functions of Rectangle/Circle/Sprite objects which are used here.
			**/
			
			/**
			 * @brief Sets the x position of the Button
			 * @param t_x The x position
			 */
			void setXPosition (int t_x);	
			
			/**
			 * @brief Returns the x position of the Button
			 * @return The x position
			 */	 
			int getXPosition ();	
			
			/**
			 * @brief Sets the y position of the Button
			 * @param t_y The y position
			 */		 
			void setYPosition (int t_y);
			
			/**
			 * @brief Returns the y position of the Button
			 * @return The y position
			 */			 
			int getYPosition ();
			
			/**
			 * @brief Sets the position of the Button
			 * @param t_x The x position
			 * @param t_y The y position
			 */
			void setPosition (int t_x, int t_y);
			
			/**
			 * @brief Sets the radius of a Circle Button
			 * @param t_radius The radius
			 */
			void setRadius (int t_radius);
			
			/**
			 * @brief Returns the radius of a circle Button
			 * @return The radius
			 */			 
			int getRadius();
			
			/**
			 * @brief Sets the width of a Rectangle Button
			 * @param t_width The width
			 */
			void setWidth (int t_width);
			
			/**
			 * @brief Returns the width of the Button
			 * @return The width
			 */
			int getWidth ();
			
			/**
			 * @brief Sets the height of a Rectangle Button
			 * @param t_height The width
			 */
			void setHeight (int t_height);
			
			/**
			 * @brief Returns the height of the Button
			 * @return The height
			 */
			int getHeight ();	 
			
			/**
			 * @brief Returns the current bounding box of the Button
			 * @return The bounding box
			 */
			m3d::BoundingBox getBoundingBox ();
			
			/**
			 * @brief Sets the color of the inner Button/Circle
			 * @param t_color The color of the inner Button/Circle
			 */
			void setInnerColor(m3d::Color t_color);
			
			/**
			 * @brief Sets the color of the outer Button/Circle
			 * @param t_color The color of the outer Button/Circle
			 */
			void setBorderColor(m3d::Color t_color);
			
			/**
			 * @brief Returns the color of the inner Button/Circle
			 * @returns The color of the inner Button/Circle
			 */
			m3d::Color getInnerColor();
			
			/**
			 * @brief Returns the color of the outer Button/Circle
			 * @returns The color of the outer Button/Circle
			 */
			m3d::Color getBorderColor();
			
			/**
			 * @brief Sets the scale of a Sprite.
			 Does not work for Rectangle/Circle buttons
			 @param x X scale
			 @param y Y Scale
			 */
			void setScale(float x, float y);
	};
}