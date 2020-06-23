#pragma once

#include "sprite.hpp"
#include "text.hpp"
#include "button.hpp"
#include "commandObject.hpp"
#include "../resources.h"
#include "../MenuHandler.hpp"

#include <citro2d.h>
#include <string>
#include <3ds.h>
#include <m3dia.hpp>
#include <cmath>
#include <vector>

#define TOPSCREEN_WIDTH 400
#define BOTTOMSCREEN_WIDTH 320
#define TOPSCREEN_HEIGHT 240
#define BOTTOMSCREEN_HEIGHT 240

#define NUM_TABS 5
#define NUM_COMMANDS_PER_TAB 8

#define SHAPE_INDEX 0
#define COLOR_INDEX 1
#define OBJECT_MANIPULATION 2
#define VAR_STATEMENTS 3
#define CONTROL_STATEMENTS 4

namespace m3dCI 
{
    class CommandLister : public m3d::Drawable
	{
		private:
			std::string listOfCommandsByTab[NUM_TABS][NUM_COMMANDS_PER_TAB] =
			{
				{ "Circle","Rectangle","Triangle","Text", "Select", "Delete", "", "" },
				{ "Red","Orange","Yellow","Green", "Blue", "Indigo", "Violet", "" },
				{ "Up","Down","Left","Right", "Scale", "Scale_X", "Scale_Y", "Rotate" },
				{ "var","Delete_var","get_x","get_y", "get_angle", "get_scale_x", "get_scale_y", "get_speed" },
				{ "if","loop","while","end", "label", "goto", "", "" }
			};

			m3d::Rectangle *backgroundRectangle;
			std::vector<m3dCI::Sprite*> tabs;
			std::vector<std::vector<CommandObject*>> commands;

			int currentlySelectedTab = -1;
			CommandObject* currentSelectedCommand = nullptr;

			bool active = false;
			int x, y, w, h;

			std::string getTabSpriteStringID(int index, bool selected);
			m3dCI::Sprite* getTabSprite(int index, bool selected);

			int getCurrentlySelectedTab();

			void CreateTabCommandObjects(int index);

			void SelectTab(int tabIndex);
			void SelectTab(int px, int py);
			void SelectCommand(int px, int py);
		public:
			//Create the CodeEditor.
			/*
			 *  @param px X Coordinate
			 *  @param py Y Coordinate
			 *  @param pw Width of Code Editor
			 *  @param ph Height of Code Editor
			 *  @param p_borderWidth Width of Border
			 *  @returns a Code Editor drawable object
			*/
			CommandLister();

			//Destructor: Objects that must be deleted when this object is deleted. Delete(nullptr) is fail-safe.
			virtual ~CommandLister();

			void SelectPoint(int px, int py);

			void draw(m3d::RenderContext t_context);

			void SetActive(bool state);
	};
}