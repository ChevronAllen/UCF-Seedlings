#pragma once
#include <string>
#include <vector>
#include <cmath>

#include <3ds.h>
#include <citro2d.h>
#include <m3dia.hpp>

#include "resourceManager.hpp"
#include "m3diaLibCI/sprite.hpp"
#include "m3diaLibCI/text.hpp"
#include "m3diaLibCI/button.hpp"
#include "commands/commands.h"


#define TOPSCREEN_WIDTH 400
#define BOTTOMSCREEN_WIDTH 320
#define TOPSCREEN_HEIGHT 240
#define BOTTOMSCREEN_HEIGHT 240

#define XStart 5
#define YStart 6
#define CELL_WIDTH 274
#define CELL_HEIGHT 57
#define MAX_PARAMS 3

using namespace std;

class CommandObject;

namespace m3dCI 
{
    /**
     * @brief A way to edit a CommandObject once it has been added to the CodeEditor
	 Based off of m3d::Drawable
     */
    class CommandEditor : public m3d::Drawable
	{
		protected:
			/**
				@brief The CommandObject being edited
			**/
			CommandObject* command;
			
			m3dCI::Sprite* background = nullptr;

			m3dCI::Text *name = nullptr;

			m3dCI::Text *params[MAX_PARAMS] = { nullptr, nullptr, nullptr };

			/**
				@brief Function to call if the type of the Object is being changed
				Used to open up the CommandLister
			**/
			std::function<void()> OnEditCommand = nullptr;
		public:
			
			/** @brief Create the CommandEditor.
			 *  @param command The CommandObject needing to be edited
			**/
			CommandEditor(CommandObject* command);

			/**
				@brief Deconstructor for CommandEditor.
				Responsible for deleting all needed children.
			**/
			virtual ~CommandEditor();

			/**
				@brief Draw the CommandEditor
				@param t_context The context to draw in
			**/
			void draw(m3d::RenderContext t_context);
	};
}