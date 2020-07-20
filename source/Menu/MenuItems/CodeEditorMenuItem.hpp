#pragma once
#include "../../m3diaLibCI/codeEditor.hpp"
#include "../MenuItem.hpp"

/**
	@brief The CodeEditorMenuItem is a combination of a m3dCI::CodeEditor and a MenuItem
**/
class CodeEditorMenuItem : public m3dCI::CodeEditor, public MenuItem
{
public:
	/**
		@brief Creates a CodeEditor to be used as a MenuItem
		@param px X position
		@param py Y position
		@param p_borderWidth Gap between the Outer and Inner Rectangles
	**/
	CodeEditorMenuItem(int px, int py, int p_borderWidth);

	/**
		@brief Deconstructor for CodeEditorMenuItem.
		Responsible for deleting all needed children.
	**/
	~CodeEditorMenuItem();

	/**
		@brief Function responsible for determining Intersection between the object and a specific XY Coordinate
	**/
	bool PointIntersection(int px, int py);

	/**
		@brief Function used to move the CodeEditor from the bottom screen to the top screen
	**/
	
	void ShiftToTop();
	/**
		@brief Function used to move the CodeEditor from the top screen back to the botto screen
	**/
	void ShiftToBottom();
};