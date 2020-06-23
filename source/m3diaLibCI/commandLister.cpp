#include "commandLister.hpp"

namespace m3dCI
{
	CommandLister::CommandLister()
		: m3d::Drawable()
	{
		x = 0;
		y = 0;
		w = BOTTOMSCREEN_WIDTH * 0.25;
		h = BOTTOMSCREEN_HEIGHT;

		int tabWidthAndHeight = (TOPSCREEN_HEIGHT / NUM_TABS);

		backgroundRectangle = new m3d::Rectangle(x, y, tabWidthAndHeight + BOTTOMSCREEN_WIDTH * 0.5, h, m3d::Color(255, 255, 255));

		ResourceManager::loadSpritesheet("gfx/menuSprites");
		
		for (int i = 0; i < NUM_TABS; i++)
		{
			getTabSprite(i, true)->setPosition(0, i * tabWidthAndHeight);//set the selected sprites position ahead of time

			m3dCI::Sprite* tab = getTabSprite(i, false);//new m3dCI::Sprite(*getTabSprite(1, false));

			tab->setPosition(0, i * tabWidthAndHeight);

			tabs.push_back(tab);

			CreateTabCommandObjects(i);
		}

		SelectTab(0);
	}

	CommandLister::~CommandLister()
	{
		delete(backgroundRectangle);

		for (unsigned int i = 0; i < tabs.size(); i++)
			delete(tabs[i]);
	}

	void CommandLister::CreateTabCommandObjects(int index)
	{
		std::vector<CommandObject*> objects;

		int tabWidthAndHeight = (TOPSCREEN_HEIGHT / NUM_TABS);
		int commandObjectHeight = BOTTOMSCREEN_HEIGHT / NUM_COMMANDS_PER_TAB;

		int sizeOfArray = sizeof(listOfCommandsByTab[index]) / sizeof(listOfCommandsByTab[index][0]);
		for (unsigned int i = 0; i < sizeOfArray; i++)
		{
			if (listOfCommandsByTab[index][i] == "")
				continue;

			m3dCI::CommandObject* command = new m3dCI::CommandObject(
				x + tabWidthAndHeight,
				y + commandObjectHeight * i,
				BOTTOMSCREEN_WIDTH * 0.5,
				commandObjectHeight,
				listOfCommandsByTab[index][i],
				false);

			command->setBackgroundColor(i % 2 ? m3d::Color(211, 211, 211) : m3d::Color(169, 169, 169));

			objects.push_back(command);
		}

		commands.push_back(objects);
	}

	std::string CommandLister::getTabSpriteStringID(int index, bool selected = false)
	{
		return "tab" + std::to_string(index + 1) + (selected?"selected":"") + ".png";
	}

	m3dCI::Sprite* CommandLister::getTabSprite(int index, bool selected = false)
	{
		return ResourceManager::getSprite(getTabSpriteStringID(index, selected));
	}

	void CommandLister::draw(m3d::RenderContext t_context)
	{
		if(backgroundRectangle != nullptr)
			backgroundRectangle->draw(t_context);

		for (unsigned int i = 0; i < tabs.size(); i++)
			if(tabs[i] != nullptr)
				tabs[i]->draw(t_context);

		int selectedTab = getCurrentlySelectedTab();

		if (selectedTab != -1)
		{
			for (unsigned int i = 0; i < commands[selectedTab].size(); i++)
			{
				if (commands[selectedTab][i] != nullptr)
					commands[selectedTab][i]->draw(t_context);
			}
		}
	}

	int CommandLister::getCurrentlySelectedTab()
	{
		return currentlySelectedTab;
	}

	void CommandLister::SelectPoint(int px, int py)
	{
		if (!active)
			return;

		int tabWidthAndHeight = (TOPSCREEN_HEIGHT / NUM_TABS);

		if (px <= tabWidthAndHeight)
		{
			SelectTab(px, py);
		}
		else if (px <= tabWidthAndHeight + BOTTOMSCREEN_WIDTH * 0.5)
		{
			SelectCommand(px, py);
		}
	}

	void CommandLister::SelectCommand(int px, int py)
	{
		int selectedTab = getCurrentlySelectedTab();

		if (selectedTab == -1)
			return;

		int commandObjectHeight = BOTTOMSCREEN_HEIGHT / NUM_COMMANDS_PER_TAB;

		int selectedCommand = py / commandObjectHeight;

		MenuHandler::AddCommand(listOfCommandsByTab[selectedTab][selectedCommand]);
	}

	void CommandLister::SelectTab(int px, int py)
	{
		int tabWidthAndHeight = (TOPSCREEN_HEIGHT / NUM_TABS);
		int tabIndex = py / tabWidthAndHeight;

		SelectTab(tabIndex);
	}

	void CommandLister::SelectTab(int tabIndex)
	{
		int tabWidthAndHeight = (TOPSCREEN_HEIGHT / NUM_TABS);
		m3dCI::Sprite* spriteToChange = tabs[tabIndex];

		//selected sprite other than current selection
		// - deselect old
		// - select new
		// - replace selectedIndex
		if (currentlySelectedTab != tabIndex)
		{
			tabs[currentlySelectedTab] = getTabSprite(currentlySelectedTab, false);
			tabs[tabIndex] = getTabSprite(tabIndex, true);

			currentlySelectedTab = tabIndex;
		}
	}

	void CommandLister::SetActive(bool state)
	{
		active = state;
	}
}
