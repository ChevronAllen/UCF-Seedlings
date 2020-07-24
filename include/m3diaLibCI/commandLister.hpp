#pragma once
#include <string>
#include <vector>
#include <cmath>

#include <3ds.h>
#include <citro2d.h>
#include <m3dia.hpp>

#include "resourceManager.hpp"
#include "menu/menuItems/SpriteMenuItem.hpp"
#include "m3diaLibCI/sprite.hpp"
#include "m3diaLibCI/text.hpp"
#include "m3diaLibCI/button.hpp"
#include "m3diaLibCI/commandListerItem.hpp"


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

class Minigame;
class CommandObject;

using namespace std;

namespace m3dCI 
{
    /**
     @brief A selection menu tasked with displaying all selectable Commands and giving the CodeEditor a respective CommandObject
	 Based off of m3d::Drawable
     */
    class CommandLister : public m3d::Drawable
	{
		private:
			Minigame* minigame;

			pair<string, function<void()>> listOfCommandsByTab[NUM_TABS][NUM_COMMANDS_PER_TAB];

			m3d::Rectangle *backgroundRectangle = nullptr;
			std::vector<SpriteMenuItem*> tabs;
			std::vector<std::vector<commandListerItem*>> commands;

			int currentlySelectedTab = -1;
			commandListerItem* currentSelectedCommand = nullptr;

			int x, y, w, h;

			/**
				@brief Get the String for a Sprites Tab location
				@param index Index of the Tab
				@param selected Boolean if it should grab the Tab_Selected Sprite
				@returns String for a Sprites Tab location
			**/
			std::string getTabSpriteStringID(int index, bool selected);
			
			/**
				@brief Get the sprite for a Tab 
				@param index Index of the Tab
				@param selected Boolean if it should grab the Tab_Selected Sprite
				@returns Sprite for the Tab
			**/
			m3dCI::Sprite* getTabSprite(int index, bool selected);

			/**
				@brief Create all the CommandObjects when a Tab is switched to
				@param index Tab to switch to
			**/
			void CreateTabCommandObjects(int index);

			/**
				@brief Switch between Tabs
				@param tabIndex Tab to switch to
			**/
			void SelectTab(int tabIndex);
		protected:
			/**
				@brief Get the selected tab index
				@returns the Selected Tab Index
			**/
			int getCurrentlySelectedTab();
			
			/**
				@brief Determine which Tab to select based off a Touch
				@param px X coordinate clicked
				@param py Y coordinate clicked
			**/
			void SelectTab(int px, int py);
			
			/**
				@brief Determine which CommandObject to select based off a Touch
				@param px X coordinate clicked
				@param py Y coordinate clicked
			**/
			void SelectCommandObject(int px, int py);

		public:
			/** @brief Create the CommandLister.
			 *  @param minigame Minigame object to add the new Object to.
				NOTE: Storing the Minigame inside the object is a poor way of doing it. 
				Should be changed to being handled inside a MenuItem
			**/
			CommandLister(Minigame* minigame);

			/**
				@brief Deconstructor for CommandLister.
				Responsible for deleting all needed children.
			**/
			virtual ~CommandLister();

			/**
				@brief Draw the CommandLister
				@param t_context The context to draw in
			**/
			void draw(m3d::RenderContext t_context);

			/**
				@brief Provide Option for Minigames to Override which CommandListerItems exist inside the menu.
				@param commandListObject The object which will replace the existing one
				@param tab The ID of the tab
				@parma id The index of the commandListerItem
			**/
			void OverrideCommandListObject(pair<string, function<void()>> commandListObject, int tab, int id);

			/**
				@brief Provide Option for Minigames to Override which CommandListerItems exist inside the menu.
				Overrides an entire Tab. Missing Entries will be filled by blanks.
				@param commandListObject A list of CommandListObjects to replace
				@param tab The ID of the tab
			**/
			void OverrideTabCommandListObjects(std::vector<pair<string, function<void()>>> commandListObjects, int tab);

			/**
				@brief Sets a tab enabled state
				@param tabIndex Tab to select
				@param state State to leave the tab in
			**/
			void SetTabState(int tabIndex, bool state);
	};
}