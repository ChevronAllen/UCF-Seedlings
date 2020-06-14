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
	
    class Button: public m3d::Drawable
	{
		private:
			ButtonType buttonType;
			
			m3d::Rectangle* innerRectangle;
			m3d::Rectangle* outerRectangle;
			m3d::Circle* innerCircle;
			m3d::Circle* outerCircle;

			m3dCI::Sprite* sprite;

			m3dCI::Text* text;

			m3d::Color innerColor, outerColor;

			int x, y, borderWidth, w, h, r;
			
			void SetDefaults();

			void UpdateShape();
		public:
			//Destructor: Objects that must be deleted when this object is deleted. Delete(nullptr) is fail-safe.
			virtual ~Button();

			//Creates a Rectangle to take the form of a button
			Button(int px, int py, int pw, int ph, m3d::Color p_innerColor, m3d::Color p_borderColor, int p_borderWidth);
			
			//Creates a Circle to take the form of a button
			Button(int px, int py, int pr, m3d::Color p_innerColor, m3d::Color p_borderColor, int p_borderWidth);

			Button(int px, int py, m3d::Texture& t_texture);
			Button(int px, int py, const std::string& t_spriteSheet, int t_imageId);
			
			//The function which is called when the touch event is touched over the button.
			// Called if a single touch is over the button and the touch happened on the same frame
			void (*OnTouch)(Button*);
			
			//The function which is called when the touch event is released over the button.
			// Called when a touch is released over a button.
			void (*OnRelease)(Button*);
			
			//The function which is called when the touch event is held over the button.
			// Called when a touch is over a button, but the initial touch did not happen on the frame being called
			void (*OnHeld)(Button*);
			
			//Check if a point intersects with the button
			bool PointIntersects(int x, int y);
			
			//How to draw the button object
			void draw(m3d::RenderContext t_context);
			
			void SetText(std::string txt);
			void SetTextColor(m3d::Color color);

			/*
			
				The following functions are all child functions of Rectangle/Circle objects which are used here.
			
			*/
			void setXPosition (int t_x);			 
			int getXPosition ();			 
			void setYPosition (int t_y);			 
			int getYPosition ();			 
			void setPosition (int t_x, int t_y);
			void setRadius (int t_radius);
			int getRadius();
			void setWidth (int t_width);
			int getWidth ();
			void setHeight (int t_height);
			int getHeight ();	 
			m3d::BoundingBox getBoundingBox ();
			void setInnerColor(m3d::Color t_color);
			void setBorderColor(m3d::Color t_color);
			m3d::Color getInnerColor();
			m3d::Color getBorderColor();
	};
}