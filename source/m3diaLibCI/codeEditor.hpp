#pragma once

#include <citro2d.h>
#include <string>
#include <3ds.h>
#include <m3dia.hpp>
#include <cmath>
#include <vector>
#include <m3dia.hpp>

class CommandObject;

namespace m3dCI 
{
    /**
		@brief A way to display a list of CommandObjects to be Added to, Edited, Removed and Selected.
		Based off of m3d::Drawable
    **/
    class CodeEditor: public m3d::Drawable
	{
		protected:
			m3d::Rectangle *borderRectangle,
				*innerRectangle;
				
			/**
				@brief List of all CommandObjects inside the CodeEditor in display order
			**/
			std::vector<CommandObject*> commands;

			/**
				@brief The currently selected CommandObject
			**/
			CommandObject* currentSelectedCommand = nullptr;
			int x, xShift = 0, y, borderWidth, w, h;

			/**
				@brief The current scroll set
			**/
			double scrollY = 0;
			double thisScrollChange = 0;
			
			/**
				@brief Function used to reset the Coordinates of all CommandObjects once an object was removed/deleted/selected
			**/
			void refreshCommandList();

			/**
				@brief Get the index of the selected CommandObject
				@returns Index of selected CommandObject
				-1 if no selection
			**/
			int GetSelectedCommandIndex();

			/**
				@brief Sets the selected CommandObject
				@param index Index of CommandObject to select
			**/
			void SelectCommand(int index);

			/**
				@brief Function responsible for determining Intersection between the object and a specific XY Coordinate
				TODO: Replace with CodeEditorMenuItem's PointIntersection
			**/
			bool isPointInside(int px, int py);
			
			/**
				@brief Select an Object based off a click pointer
				TODO: Replace with CodeEditorMenuItem's OnTouch
				@param px Touch X
				@param py Touch Y
			**/
			void InternalSelectCommand(int px, int py);

			/**
				@brief Handle the drag of this object
				TODO: Replace with CodeEditorMenuItem's OnDrag
				@param u Drag amount in X direction
				@param v Drag amount in Y direction
			**/
			void InternalDoDrag(int u, int v);
			
			/**
				@brief Handle the completion of a drag on this object
				TODO: Replace with CodeEditorMenuItem's OnDragComplete
			**/
			void InternalDragComplete();

		public:
			/** @brief Create the CodeEditor.
			 *  @param px X Coordinate
			 *  @param pw The width of the CodeEditor
			 *  @param p_borderWidth Width of Border
			**/
			CodeEditor(int px, int pw, int p_borderWidth);

			/**
				@brief Deconstructor for CodeEditor.
				Responsible for deleting all needed children.
			**/
			virtual ~CodeEditor();
			
			/**
				@brief Function for adding a CommandObject to the CodeEditor list
				@param command CommandObject to Added
				@param position Index to add to. -1 will add it based on the current selected index.
			**/
			void addCommand(CommandObject* command, int position = -1);
			
			/**
				@brief Removes a CommandObject from the CodeEditor
				@param position Index of CommandObject to remove. -1 will remove it based on the current selected object.
			**/
			void removeCommand(int position = -1);

			/**
				@brief Replace a CommandObject with a different CommandObject
				@param current Current CommandObject inside CodeEditor | Object being removed
				@param newCommand CommandObject which is used as a replacement | Object being added
			**/
			void replaceCommand(CommandObject* current, CommandObject* newCommand);

			/**
				@brief Clear all the CommandObjects from the list
			**/
			void ClearCommands();

			/**
				@brief Checks if the selected item can be added above
				@returns Boolean containing if the selected item can be added above
			**/
			bool canAdd();
			
			/**
				@brief Checks if the selected item can be edited
				@returns Boolean containing if the selected item can be edited
			**/
			bool canEdit();
			
			/**
				@brief Checks if the selected item can be removed
				@returns Boolean containing if the selected item can be removed
			**/
			bool canRemove();
			
			/**
				@brief Get the list of commands stored inside the CodeEditor
				@returns A list of CommandObject*s that the CodeEditor contains
			**/
			std::vector<CommandObject*> GetCommands();
			
			/**
				@brief Get the currently selected CommandObject
				@returns The currently selected CommandObject
			**/
			CommandObject* getSelectedObject();

			/**
				@brief Get if the CurrentlySelected Command is the Blank (--) command
				@returns Boolean containing if the CurrentlySelected Command is the Blank (--) command
			**/
			bool IsBlankCommandSelected();

			/**
				@brief Draw the CodeEditor
				@param t_context The context to draw in
			**/
			void draw(m3d::RenderContext t_context);

			/**
				@brief Shifts the positions of the CodeEditor to be placed properly on the Top screen
			**/
			void ShiftToTop();
			
			/**
				@brief Shifts the positions of the CodeEditor to be placed properly on the Bottom screen
			**/
			void ShiftToBottom();
	};
}