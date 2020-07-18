#include "commandLister.hpp"
#include "../scenes/minigame.hpp"
#include "../commands/commands.h"

#define t(x) mini->AddCommand(x)
#define func(a) [mini]() { t(a); }
#define PAIR(name, command) { name, [mini]() { t(command); }}
#define NULLPartialPAIR(name) { name, nullptr }
#define NULLPAIR PAIR("", nullptr)
#define COLORPAIR(name, r, g, b) PAIR(name, new ColorCommand(name, m3d::Color(r,g,b,255)))

namespace m3dCI
{
	CommandLister::CommandLister(Minigame* mini)
		: m3d::Drawable()
	{
		minigame = mini;

		pair<string, function<void()>> helper[NUM_TABS][NUM_COMMANDS_PER_TAB] =
		{
			{ 
                PAIR("Circle", new CircleCommand()), 
                PAIR("Rectangle", new RectangleCommand()), 
                //NULLPartialPAIR("Triangle"), 
                PAIR("Text", new TextCommand("TEXT")), 
                PAIR("Select", new SelectCommand()), 
                PAIR("Delete", new DeleteCommand), 
                NULLPAIR, 
                NULLPAIR, 
                NULLPAIR 
            },
			{ 
                COLORPAIR("Red", 255, 0, 0), 
                COLORPAIR("Orange", 255, 127, 0), 
                COLORPAIR("Yellow", 255, 255, 0), 
                COLORPAIR("Green", 0, 255, 0), 
                COLORPAIR("Blue", 0, 0, 255), 
                COLORPAIR("Indigo", 75, 0, 130), 
                COLORPAIR("Violet", 148, 0, 211), 
                COLORPAIR("Black", 0, 0, 0) 
            },
			{ 
                PAIR("Up", new UpCommand()), 
                PAIR("Down", new DownCommand()), 
                PAIR("Left", new LeftCommand()), 
                PAIR("Right", new RightCommand()), 
                PAIR("Scale", new ScaleCommand("1","1")), 
                PAIR("Scale_X", new ScaleCommand("1", "-1")), 
                PAIR("Scale_Y", new ScaleCommand("-1", "1")) 
            },
			{ 
                PAIR("Var", new VarCommand()), 
                PAIR("Get_X", new GetXCommand()), 
                PAIR("Get_Y", new GetYCommand()), 
                PAIR("Get_Angle", new GetAngleCommand()), 
                PAIR("Set_Angle", new SetAngleCommand()), 
                PAIR("Get_Scale_X", new Get_ScaleXCommand()), 
                PAIR("Get_Scale_Y", new Get_ScaleYCommand()) 
            },
			{ 
                PAIR("If", new IfCommand()), 
                NULLPartialPAIR("Loop"), 
                PAIR("While", new WhileCommand()), 
                PAIR("End", new EndCommand()), 
                PAIR("Label", new LabelCommand()), 
                PAIR("Goto", new GotoCommand()), 
                NULLPAIR, 
                NULLPAIR 
            }
		};

		for (int i = 0; i < NUM_TABS; i++)
			for (int j = 0; j < NUM_COMMANDS_PER_TAB; j++)
				listOfCommandsByTab[i][j] = helper[i][j];		

		x = 0;
		y = 0;
		w = BOTTOMSCREEN_WIDTH * 0.25;
		h = BOTTOMSCREEN_HEIGHT;

		int tabWidthAndHeight = (TOPSCREEN_HEIGHT / NUM_TABS);

		backgroundRectangle = new m3d::Rectangle(x, y, tabWidthAndHeight + BOTTOMSCREEN_WIDTH * 0.5, h, m3d::Color(255, 255, 255));
		
		for (int i = 0; i < NUM_TABS; i++)
		{
			m3dCI::Sprite* tab = new m3dCI::Sprite(*getTabSprite(i, false));
			//getTabSprite(i, true)->setPosition(0, i * tabWidthAndHeight);//set the selected sprites position ahead of time

			//m3dCI::Sprite* tab = getTabSprite(i, false);//new m3dCI::Sprite(*getTabSprite(1, false));

			tab->setPosition(0, i * tabWidthAndHeight);

			tabs.push_back(tab);

			CreateTabCommandObjects(i);
		}

		SelectTab(0);
	}

	CommandLister::~CommandLister()
	{
		for (unsigned int i = 0; i < commands.size(); i++)
			for(unsigned int j = 0; j < commands[i].size(); j++)
				delete(commands[i][j]);
	}

	void CommandLister::CreateTabCommandObjects(int index)
	{
		std::vector<commandListerItem*> objects;

		int tabWidthAndHeight = (TOPSCREEN_HEIGHT / NUM_TABS);
		int commandObjectHeight = BOTTOMSCREEN_HEIGHT / NUM_COMMANDS_PER_TAB;

		int sizeOfArray = sizeof(listOfCommandsByTab[index]) / sizeof(listOfCommandsByTab[index][0]);
		for (int i = 0; i < sizeOfArray; i++)
		{
			if (listOfCommandsByTab[index][i].first == "")
				continue;

			m3dCI::commandListerItem* command = new m3dCI::commandListerItem(
				x + tabWidthAndHeight,
				y + commandObjectHeight * i,
				BOTTOMSCREEN_WIDTH * 0.5,
				commandObjectHeight,
				listOfCommandsByTab[index][i].first,
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

	void CommandLister::SelectCommandObject(int px, int py)
	{
		int selectedTab = getCurrentlySelectedTab();

		if (selectedTab == -1)
			return;

		int commandObjectHeight = BOTTOMSCREEN_HEIGHT / NUM_COMMANDS_PER_TAB;
		int selectedCommand = py / commandObjectHeight;

		if (selectedCommand == -1 || listOfCommandsByTab[selectedTab][selectedCommand].first == "" || listOfCommandsByTab[selectedTab][selectedCommand].second == nullptr)
			return;

		listOfCommandsByTab[selectedTab][selectedCommand].second();
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
		//selected sprite other than current selection
		// - deselect old
		// - select new
		// - replace selectedIndex
		if (currentlySelectedTab != tabIndex)
		{
			if (currentlySelectedTab != -1)
			{
				m3dCI::Sprite* oldSelected = new m3dCI::Sprite(*getTabSprite(currentlySelectedTab, false));
				oldSelected->setPosition(0, currentlySelectedTab * tabWidthAndHeight);
				delete(tabs[currentlySelectedTab]);

				tabs[currentlySelectedTab] = oldSelected;
			}

			m3dCI::Sprite* newSelected = new m3dCI::Sprite(*getTabSprite(tabIndex, true));
			newSelected->setPosition(0, tabIndex * tabWidthAndHeight);
			delete(tabs[tabIndex]);
			tabs[tabIndex] = newSelected;
			
			currentlySelectedTab = tabIndex;
		}
	}
}
