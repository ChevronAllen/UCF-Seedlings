#pragma once

#include "text.hpp"

#include <m3dia.hpp>
#include <string.h>
#include <citro2d.h>

namespace m3dCI
{
	/**
		@brief The Console is a custom debugging interface useful for printing out messages during runtime
	**/
	class Console : public m3d::Drawable
	{
		private:
			bool toggleState;
			m3dCI::Text consoleTextBox;
			m3d::Rectangle consoleBlackRectangle;
			
		public:
			/**
				@brief Creates a Console
				@param defaultText Initial text to display on the Console
			**/
			Console(std::string defaultText);

			/**
				@brief Deconstructor for Console.
				Delete objects which were created solely for this object.
			**/
			virtual ~Console();
			
			/**
				@brief Toggles the visibility state of the console.
			**/
			void ToggleState();
			
			/**
				@brief Add text to be displayed.
				Up to 10 lines are displayed at once.
				@param text Text to add to the Console
			**/
			void print(std::string text);
			
			/**
				@brief Add text to be displayed followed by a new line.
				Up to 10 lines are displayed at once.
				@param text Text to add to the Console
			**/
			void println(std::string text);
			
			/**
				@brief Draw the Console
				@param t_context Where on screen the Console should be rendered
			**/
			void draw(m3d::RenderContext t_context);
			
			/**
				@brief Determine if the console is being drawn
				@returns A boolean with the draw state of the Console
			**/
			bool isDrawn();
	};
} 