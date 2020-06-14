#pragma once

#include "../util.hpp"
#include "../ObjectManager.hpp"
#include "../MenuHandler.hpp"
#include "../m3diaLibCI/text.hpp"

#include <m3dia.hpp>

class Menu
{
	protected:
		Util* util;
		MenuHandler* mh;
		ObjectManager* om;
		m3d::Screen* scr;
	public:
		Menu(Screen* screen);
		//Destructor: Objects that must be deleted when this object is deleted. Delete(nullptr) is fail-safe.
		virtual ~Menu();
		
		virtual void OnUpdate() = 0;
};