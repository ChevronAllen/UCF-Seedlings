#pragma once
#include <vector>
#include <algorithm>
#include "../inputManager.hpp"

#include "MenuItem.hpp"
#include "MenuItems/ButtonMenuItem.hpp"
#include "MenuItems/CodeEditorMenuItem.hpp"
#include "MenuItems/CommandEditorMenuItem.hpp"
#include "MenuItems/CommandListerMenuItem.hpp"
#include "MenuItems/RectangleMenuItem.hpp"
#include "MenuItems/SpriteMenuItem.hpp"
#include "MenuItems/TextMenuItem.hpp"
#include "../util.hpp"

/**
	@brief A Menu is responsible for holding all MenuItems and calling their following functions:
	- OnTouch
	- OnRelease
	- OnHeld
	- OnHeldEnter
	- OnHeldLeave
	- OnDrag
	- OnDragComplete
**/
class Menu
{
private:
	///@brief List of MenuItems
	std::vector<MenuItem*> menuItems;
	bool draggedLastFrame = false;
	int lastFrameTouchX = -1, lastFrameTouchY = -1;
	
public:
	/**
		@brief Creates a Menu
	**/
	Menu();
	
	/**
		@brief Deconstructor for Menu.
		Responsible for deleting all MenuItems
	**/
	~Menu();
	
	/**
		@brief Add a MenuItem to this menu
		@param item Item to add
		@returns If successful, returns item. Otherwise, returns nullptr
	**/
	MenuItem* AddItem(MenuItem* item);
	
	/**
		@brief Check if a MenuItem exists inside this Menu
		@param item Item to check for
		@returns Boolean if the MenuItem exists inside the Menu
	**/
	bool ContainsItem(MenuItem* item);
	
	/**
		@brief Remove a MenuItem from this menu
		@param item Item to remove
	**/
	void RemoveItem(MenuItem* item);
	
	/**
		@brief Function called on each game frame to check for interaction
	**/
	void OnUpdate();
};
