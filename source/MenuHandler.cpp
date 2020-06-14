#include "MenuHandler.hpp"

#include "menus/menu.hpp"
#include "menus/mainMenu.hpp"
#include "menus/minigameSelect.hpp"

using namespace m3d;

//Set default instance of this class to 0, to notify that the instance hasn't been created
MenuHandler *MenuHandler::instance = 0;

/*
	This Class is a singleton. 
	Meaning, only one instance of this class may ever exist.
	This allows for all classes to access this object through the use of this instance value.
	An initial instantiation must occur with proper values passed into createInstance
	All further attempts to accesss this class can use dummy values for all parameters of getInstance
*/
MenuHandler* MenuHandler::createInstance(Screen* screen)
{
	if (instance == 0)
	{
		instance = new MenuHandler(screen);
	}
	
	return instance;
}

/*
	This Class is a singleton. 
	Meaning, only one instance of this class may ever exist.
	This allows for all classes to access this object through the use of this instance value.
	An initial instantiation must occur with proper values passed into createInstance
	All further attempts to accesss this class can use dummy values for all parameters of getInstance
*/
MenuHandler* MenuHandler::getInstance()
{
	if (instance == 0)
	{
		return nullptr;
	}
	
	return instance;
}

//Initialize the Util class.
//Only ever called once.
MenuHandler::MenuHandler(Screen* screen)
{
	currentMenu = nullptr;
	scr = screen;

	TransitionTo(MenuState::MainMenu);

	util = Util::getInstance();
}

MenuHandler::~MenuHandler()
{
	delete(currentMenu);
}

//The function which is called on every game frame.
void MenuHandler::OnUpdate()
{
	if(currentMenu != nullptr)
		currentMenu->OnUpdate();
}

void MenuHandler::TransitionTo(MenuState state)
{
	switch (state)
	{
		case MenuState::MainMenu:
		{
			MainMenu* menu = new MainMenu(scr);

			if (currentMenu != nullptr)
				delete(currentMenu);

			currentMenu = menu;
			break;
		}
		case MenuState::MinigameSelect:
		{
			MinigameSelect* menu = new MinigameSelect(scr);

			if (currentMenu != nullptr)
				delete(currentMenu);

			currentMenu = menu;
			break;
		}
		case MenuState::Testing:
		{
			break;
		}
		default:
		{
			util->PrintLine("Attempting to transition to menu state which has not been defined.");
			break;
		}
	}
}