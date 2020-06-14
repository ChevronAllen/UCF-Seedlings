#pragma once

#include "text.hpp"

#include <m3dia.hpp>
#include <string.h>
#include <citro2d.h>

namespace m3dCI
{
	class Console : public m3d::Drawable
	{
		private:
			bool toggleState;
			m3dCI::Text consoleTextBox;
			m3d::Rectangle consoleBlackRectangle;
		public:
			//Default Console constructor. Creates a background with a textbox for console output
			Console(std::string defaultText);

			//Deconstructor: Delete objects which were created solely for this object.
			virtual ~Console();
			//Toggle the state of the console (visible to invisible)
			void ToggleState();
			//Prints the last 10 lines, any previous lines after are ignored
			void print(std::string text);
			//Prints a piece of information with a new line preceding it
			void println(std::string text);
			//Determine how to draw the Console
			void draw(m3d::RenderContext t_context);
			//Determine if the console is being drawn
			bool isDrawn();
	};
} 