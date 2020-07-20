#pragma once
#include "../../m3diaLibCI/commandEditor.hpp"
#include "../MenuItem.hpp"

/**
	@brief The CommandEditorMenuItem is a combination of a m3dCI::CommandEditor and a MenuItem
**/
class CommandEditorMenuItem : public m3dCI::CommandEditor, public MenuItem
{
private:
	/**
		@brief Function responsible for handling the OnClick actions
	**/
	void HandleClick(int x, int y);

public:
	/**
		@brief Creates a CommandEditor to be used by the Menu system.
		@param command Command which is being edited
	**/
	CommandEditorMenuItem(CommandObject* command);

	/**
		@brief Deconstructor for CommandEditorMenuItem.
		Responsible for deleting all needed children.
	**/
	~CommandEditorMenuItem();

	/**
		@brief Sets the Function to call when a CommandObject's type is being edited
	**/
	void SetEditFunction(std::function<void()> function);

	/**
		@brief Function responsible for determining Intersection between the object and a specific XY Coordinate
	**/
	bool PointIntersection(int px, int py);
};