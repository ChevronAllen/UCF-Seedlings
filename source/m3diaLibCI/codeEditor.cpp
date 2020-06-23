#include "codeEditor.hpp"

namespace m3dCI
{
	#define TOPSCREEN_WIDTH 400
	#define BOTTOMSCREEN_WIDTH 320
	#define TOPSCREEN_HEIGHT 240
	#define BOTTOMSCREEN_HEIGHT 240

	#define CELL_HEIGHT 20
	#define CELLS_TALL 12

	#define LEAST_CELLS_ON_SCREEN 5

	CodeEditor::CodeEditor(int px, int pw, int p_borderWidth)
		: m3d::Drawable()
	{
		x = px;
		y = 0;
		w = pw;
		h = TOPSCREEN_HEIGHT;
		borderWidth = p_borderWidth;
		currentSelectedCommand = nullptr;

		borderRectangle = new m3d::Rectangle(px, y, pw, h, m3d::Color(0, 0, 0));
		innerRectangle = new m3d::Rectangle(px + p_borderWidth, y, pw - (p_borderWidth * 2), h, m3d::Color(255, 255, 255));

		addCommand("");
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

	void CodeEditor::ShiftToTop()
	{
		int change = (TOPSCREEN_WIDTH - BOTTOMSCREEN_WIDTH) / 2;
		x += change;

		innerRectangle->setXPosition(innerRectangle->getXPosition() + change);
		borderRectangle->setXPosition(borderRectangle->getXPosition() + change);

		refreshCommandList();
	}

	void CodeEditor::ShiftToBottom()
	{
		int change = (TOPSCREEN_WIDTH - BOTTOMSCREEN_WIDTH) / 2;
		x -= change;

		innerRectangle->setXPosition(innerRectangle->getXPosition() - change);
		borderRectangle->setXPosition(borderRectangle->getXPosition() - change);

		refreshCommandList();
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

		//we want to bound this so only objects which can actually be seen get rendered
		for (unsigned int i = 0; i < commands.size(); i++)
		{
			commands[i]->draw(t_context);
		}
	}

	void CodeEditor::addCommand(std::string command, int position)
	{
		m3dCI::CommandObject* obj = new m3dCI::CommandObject(x + borderWidth, y + CELL_HEIGHT * commands.size(), w - (borderWidth * 2), CELL_HEIGHT, command, false);

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
		}

		refreshCommandList();
		
		SelectCommand(commandToRemoveIndex == (int)commands.size()?commandToRemoveIndex - 1:commandToRemoveIndex-1);
	}

	bool CodeEditor::isPointInside(int px, int py)
	{
		return px >= x && px <= x + w && py >= y && py < y + h;
	}

	void CodeEditor::SelectCommand(int px, int py)
	{
		if (!active || !isPointInside(px, py))
			return;

		int commandIndexToSelect = -1;

		for (int i = 0; i < (int)commands.size(); i++)
		{
			if (py + scrollY >= y + CELL_HEIGHT * i && py + scrollY < y + CELL_HEIGHT * (i + 1))
			{
				commandIndexToSelect = i;
			}
		}

		SelectCommand(commandIndexToSelect);
	}

	void CodeEditor::SelectCommand(int index)
	{
		if (!active)
			return;

		if (index == -1 || index >= (int)commands.size())
			currentSelectedCommand = nullptr;
		else
			currentSelectedCommand = commands[index];

		refreshCommandList();
	}

	void CodeEditor::refreshCommandList()
	{
		for (unsigned int i = 0; i < commands.size(); i++)
		{
			if (commands[i] == nullptr)
				continue;

			if (commands[i] == currentSelectedCommand)
				commands[i]->setBackgroundColor(m3d::Color(34,177,76));
			else
			{
				commands[i]->setBackgroundColor(i % 2 ? m3d::Color(211, 211, 211) : m3d::Color(169, 169, 169));
			}

			commands[i]->setPosition(x + borderWidth, y - scrollY + (CELL_HEIGHT * i));
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

	void CodeEditor::SetActive(bool state)
	{
		active = state;
	}

	bool CodeEditor::IsBlankCommandSelected()
	{
		int index = GetSelectedCommandIndex();

		if (index == -1)
			return true;

		return GetSelectedCommandIndex() == (int)commands.size() - 1;
	}

	void CodeEditor::DoDrag(m3d::Vector2f dragVector)
	{
		double change = dragVector.v - thisScrollChange;

		thisScrollChange = dragVector.v;
		scrollY -= change;
		
		//mus
		int maxScroll = (commands.size() - LEAST_CELLS_ON_SCREEN) * CELL_HEIGHT;

		if (scrollY < 0)
			scrollY = 0;
		else if (scrollY > maxScroll)
			scrollY = maxScroll;

		
		refreshCommandList();
	}

	void CodeEditor::DragComplete()
	{
		thisScrollChange = 0;
	}
}
