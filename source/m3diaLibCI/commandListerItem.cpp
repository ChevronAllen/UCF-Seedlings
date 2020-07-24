#include "m3diaLibCI/commandListerItem.hpp"

namespace m3dCI
{
	commandListerItem::commandListerItem(int x, int y, int w, int h, std::string command, bool selected = false)
	{
		backgroundRectangle = new m3d::Rectangle(x, y, w, h, m3d::Color(0, 0, 255));

		std::transform(command.begin(), command.end(), command.begin(), ::toupper);

		commandTextObject = new m3dCI::Text(command);
		commandTextObject->setColor(m3d::Color(0, 0, 0));
		commandTextObject->setPosition(x + 2, y);//+2 for buffer from left edge
		commandTextObject->setFontSize(0.75);
		commandTextObject->setFontWeight(0.68);
	}

	commandListerItem::~commandListerItem()
	{
		delete(backgroundRectangle);
		delete(commandTextObject);
	}

	void commandListerItem::draw(m3d::RenderContext t_context)
	{
		backgroundRectangle->draw(t_context);
		commandTextObject->draw(t_context);
	}

	void commandListerItem::setBackgroundColor(m3d::Color color)
	{
		backgroundRectangle->setColor(color);
	}

	void commandListerItem::setPosition(int x, int y)
	{
		commandTextObject->setPosition(x + 2, y);//+2 for buffer from left edge
		backgroundRectangle->setPosition(x, y);
	}

	void commandListerItem::setText(std::string command)
	{
		std::transform(command.begin(), command.end(), command.begin(), ::toupper);
		commandTextObject->setText(command);
	}
}