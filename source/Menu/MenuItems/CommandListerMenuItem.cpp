#include "menu/menuItems/CommandListerMenuItem.hpp"

CommandListerMenuItem::CommandListerMenuItem(Minigame* minigame)
	: CommandLister(minigame), MenuItem()
{
	SetOnRelease([&](int x, int y) 
	{
		if (!GetActive())
			return;

		int tabWidthAndHeight = (TOPSCREEN_HEIGHT / NUM_TABS);

		if (x <= tabWidthAndHeight)
		{
			SelectTab(x, y);
		}
		else if (x <= tabWidthAndHeight + BOTTOMSCREEN_WIDTH * 0.5 && getCurrentlySelectedTab() != -1)
		{
			SelectCommandObject(x, y);
		}
	});
}

//Destructor: Objects that must be deleted when this object is deleted. Delete(nullptr) is fail-safe.
CommandListerMenuItem::~CommandListerMenuItem()
{

}

bool CommandListerMenuItem::PointIntersection(int px, int py)
{
	int tabWidthAndHeight = (TOPSCREEN_HEIGHT / NUM_TABS);

	if (px <= tabWidthAndHeight)
		return true;
	else if (px <= tabWidthAndHeight + BOTTOMSCREEN_WIDTH * 0.5 && getCurrentlySelectedTab() != -1)
		return true;

	return false;
}