#pragma once

#include "../util.hpp"

#include "../ObjectManager.hpp"
#include "../MenuHandler.hpp"
#include "../m3diaLibCI/text.hpp"
#include "../m3diaLibCI/codeEditor.hpp"
#include "../m3diaLibCI/commandObject.hpp"
#include "../m3diaLibCI/commandLister.hpp"

#include <m3dia.hpp>

#define TOPSCREEN_WIDTH 400
#define BOTTOMSCREEN_WIDTH 320
#define TOPSCREEN_HEIGHT 240
#define BOTTOMSCREEN_HEIGHT 240

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