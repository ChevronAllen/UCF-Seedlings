#include "menu.hpp"

Menu::Menu(Screen* screen)
{
	util = Util::getInstance();
	om = ObjectManager::getInstance();
	mh = MenuHandler::getInstance();
	scr = screen;
}

//Destructor: Objects that must be deleted when this object is deleted. Delete(nullptr) is fail-safe.
Menu::~Menu()
{
	
}