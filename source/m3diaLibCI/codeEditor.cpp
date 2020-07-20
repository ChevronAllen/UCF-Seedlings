#include "codeEditor.hpp"

#include "../commands/commands.h"

#define TOPSCREEN_WIDTH 400
#define BOTTOMSCREEN_WIDTH 320
#define TOPSCREEN_HEIGHT 240
#define BOTTOMSCREEN_HEIGHT 240

#define CELL_HEIGHT 20
#define CELLS_TALL 12

#define LEAST_CELLS_ON_SCREEN 12

namespace m3dCI
{
	CodeEditor::CodeEditor(int px, int pw, int p_borderWidth)
		: m3d::Drawable()
	{
		x = px;
		xShift = 0;
		y = 0;
		w = pw;
		h = TOPSCREEN_HEIGHT;
		borderWidth = p_borderWidth;
		currentSelectedCommand = nullptr;

		borderRectangle = new m3d::Rectangle(px, y, pw, h, m3d::Color(0, 0, 0));
		innerRectangle = new m3d::Rectangle(px + p_borderWidth, y, pw - (p_borderWidth * 2), h, m3d::Color(255, 255, 255));

		addCommand(new EmptyCommand(true));
	}

	CodeEditor::~CodeEditor()
	{
		delete(borderRectangle);
		delete(innerRectangle);

		for (unsigned int i = 0; i < commands.size(); i++)
		{
			delete(commands[i]);
		}
	}

	void CodeEditor::draw(m3d::RenderContext t_context)
	{
		if(borderRectangle != nullptr)
			borderRectangle->draw(t_context);

		if (innerRectangle != nullptr)
			innerRectangle->draw(t_context);

		//from 0 - CELLHEIGHT draw first box as top box
		//int topIndex = scrollY / CELL_HEIGHT - 1;
		//topIndex = topIndex < 0 ? 0 : topIndex;

		//int largerBound = topIndex + CELLS_TALL > commands.size() ? commands.size() - 1 : topIndex + CELLS_TALL;

		int topLeftX = x + xShift + borderWidth;
		int topLeftY = y;

		//we want to bound this so only objects which can actually be seen get rendered
		for (unsigned int i = 0; i < commands.size(); i++)
		{
			commands[i]->draw(topLeftX, topLeftY + (CELL_HEIGHT * i) - scrollY, t_context);
		}
	}

	void CodeEditor::addCommand(CommandObject* obj, int position)
	{
		if (currentSelectedCommand == nullptr)
			SelectCommand(commands.size() - 1);

		if (position < 0)
		{
			if (currentSelectedCommand != nullptr)
			{
				commands.insert(commands.begin() + GetSelectedCommandIndex(), obj);
			}
			else
			{
				if (commands.size() == 0)
					commands.push_back(obj);
				else
					commands.insert(commands.begin() + commands.size() - 1, obj);
			}
		}
		else
			commands.insert(commands.begin() + position, obj);

		refreshCommandList();
	}

	void CodeEditor::removeCommand(int position)
	{
		if (position > (int)commands.size())
			return;

		int commandToRemoveIndex = position == -1? GetSelectedCommandIndex():position;

		if (commandToRemoveIndex >= 0 && commandToRemoveIndex < (int)commands.size() - 1)//dont allow deletion of last slot. hence the - 1
		{
			if (currentSelectedCommand == commands[commandToRemoveIndex])
				currentSelectedCommand = nullptr;

			delete(commands[commandToRemoveIndex]);
			commands.erase(commands.begin() + commandToRemoveIndex);

			if (commandToRemoveIndex >= (int)commands.size() - LEAST_CELLS_ON_SCREEN)
				scrollY -= CELL_HEIGHT;
		}

		int maxScroll = (commands.size() - LEAST_CELLS_ON_SCREEN) * CELL_HEIGHT;

		if (scrollY < 0)
			scrollY = 0;
		else if (scrollY > maxScroll)
			scrollY = maxScroll;

		refreshCommandList();
		
		SelectCommand(commandToRemoveIndex == (int)commands.size()?commandToRemoveIndex - 1:commandToRemoveIndex-1);
	}

	void CodeEditor::replaceCommand(CommandObject* current, CommandObject* newCommand)
	{
		int index = -1;
		for (unsigned int i = 0; i < commands.size(); i++)
			if (commands[i] == current)
				index = i;

		if (index == -1)
			return;

		if (currentSelectedCommand == commands[index])
		{
			currentSelectedCommand = newCommand;
			currentSelectedCommand->setSelected(true);
		}

		delete(commands[index]);
		commands[index] = newCommand;
	}

	void CodeEditor::ClearCommands()
	{
		for (int i = (int)commands.size() - 1; i >= 0; i--)
		{
			removeCommand(i);
		}
		scrollY = 0;
	}

	bool CodeEditor::isPointInside(int px, int py)
	{
		return px >= x && px <= x + w && py >= y && py < y + h;
	}

	void CodeEditor::InternalSelectCommand(int px, int py)
	{
		if (!isPointInside(px, py))
			return;

		int commandIndexToSelect = (py + scrollY) / CELL_HEIGHT;

		if (commandIndexToSelect == -1 || commandIndexToSelect >= (int)commands.size())
			return;

		SelectCommand(commandIndexToSelect);
	}

	void CodeEditor::SelectCommand(int index)
	{
		if (index == -1 || index >= (int)commands.size())
		{
			if (currentSelectedCommand != nullptr)
				currentSelectedCommand->setSelected(false);

			currentSelectedCommand = nullptr;
		}
		else
		{
			if (currentSelectedCommand != nullptr)
				currentSelectedCommand->setSelected(false);

			currentSelectedCommand = commands[index];
			currentSelectedCommand->setSelected(true);
		}

		refreshCommandList();
	}

	void CodeEditor::refreshCommandList()
	{
		for (unsigned int i = 0; i < commands.size(); i++)
		{
			if (commands[i] == nullptr)
				continue;

			//if (commands[i] == currentSelectedCommand)
			//	commands[i]->setBackgroundColor(m3d::Color(34,177,76));
			//else
			//{
			//	commands[i]->setBackgroundColor(i % 2 ? m3d::Color(211, 211, 211) : m3d::Color(169, 169, 169));
			//}
		}
	}

	int CodeEditor::GetSelectedCommandIndex()
	{
		int index = -1;
		//remove curently selected command
		for (unsigned int i = 0; i < commands.size(); i++)
			if (commands[i] == currentSelectedCommand)
				index = i;

		return index;
	}

	bool CodeEditor::IsBlankCommandSelected()
	{
		int index = GetSelectedCommandIndex();

		if (index == -1)
			return true;

		return GetSelectedCommandIndex() == (int)commands.size() - 1;
	}

	void CodeEditor::InternalDoDrag(int u, int v)
	{
		double change = v - thisScrollChange;

		thisScrollChange = v;
		scrollY -= change;

		int maxScroll = (commands.size() - (commands.size() > LEAST_CELLS_ON_SCREEN?LEAST_CELLS_ON_SCREEN:commands.size())) * CELL_HEIGHT;

		if (scrollY < 0)
		{
			scrollY = 0;
		}
		else if (scrollY > maxScroll)
		{
			scrollY = maxScroll;
		}

		
		refreshCommandList();
	}

	void CodeEditor::InternalDragComplete()
	{
		thisScrollChange = 0;
	}

	std::vector<CommandObject*> CodeEditor::GetCommands()
	{
		return commands;
	}

	bool CodeEditor::canAdd()
	{
		if (currentSelectedCommand != nullptr && currentSelectedCommand->IsAddlocked())
			return false;
			
		return true;
	}

	bool CodeEditor::canEdit()
	{
		if (currentSelectedCommand != nullptr && currentSelectedCommand->IsEditLocked())
			return false;

		return !IsBlankCommandSelected();
	}

	bool CodeEditor::canRemove()
	{
		if (currentSelectedCommand != nullptr && currentSelectedCommand->IsEditLocked())
			return false;

		return !IsBlankCommandSelected();
	}

	CommandObject* CodeEditor::getSelectedObject()
	{
		return currentSelectedCommand;
	}
}
