#pragma once

#include "util.hpp"

#include <3ds.h>
#include <vector>
#include <m3dia.hpp>

using namespace m3d;

class Menu;
class MainMenu;
class MinigameSelect;

class MenuHandler
{
	private:
		//The active Screen object
		Screen* scr;
		//The Utility manager
		Util* util;

		Menu* currentMenu;
		
		/*
			This Class is a singleton. 
			Meaning, only one instance of this class may ever exist.
			This allows for all classes to access this object through the use of this instance value.
			An initial instantiation must occur with proper vaules passed into getInstance
			All further attempts to accesss this class can use dummy values for all parameters of getInstance
		*/
		static MenuHandler *instance;
		MenuHandler(Screen* screen);
	public:
		enum class MenuState
		{
			MainMenu,
			MinigameSelect,
			Testing
		};

		static MenuHandler* getInstance();
		static MenuHandler* createInstance(Screen* screen);
		
		//The function which is called on every game frame.
		void OnUpdate();

		void TransitionTo(MenuState state);
		virtual ~MenuHandler();
};