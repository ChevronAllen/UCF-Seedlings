#pragma once
#include "../../m3diaLibCI/commandLister.hpp"
#include "../MenuItem.hpp"

/**
	@brief The CommandListerMenuItem is a combination of a m3dCI::CommandLister and a MenuItem
**/
class CommandListerMenuItem : public m3dCI::CommandLister, public MenuItem
{
public:
	/**
		@brief Creates a CommandListerMenuItem which is responsible for adding Commands to a Minigame's Code Editor
		@param minigame The active Minigame to tell where the commands should go.
	**/
	CommandListerMenuItem(Minigame* minigame);

	/**
		@brief Deconstructor for CommandListerMenuItem.
		Responsible for deleting all needed children.
	**/
	~CommandListerMenuItem();

	/**
		@brief Function responsible for determining Intersection between the object and a specific XY Coordinate
	**/
	bool PointIntersection(int px, int py);
};