#pragma once

#include "m3diaLibCI/button.hpp" 
#include "m3diaLibCI/console.hpp"
#include "m3diaLibCI/codeEditor.hpp" 
#include "m3diaLibCI/commandLister.hpp" 
#include "util.hpp"
#include "inputManager.hpp"

#include <3ds.h>
#include <vector>
#include <citro2d.h>
#include <m3dia.hpp>

using namespace m3d;

class ObjectManager
{
	private:
		//The active Screen object
		Screen* scr;
		//The Utility manager
		Util* util;
		//Stored values for TouchEvents. Stores the previous frames x and y touch values
		int lastFrameTouchX, lastFrameTouchY;
		bool draggedLastFrame = false;
		//Array of all active buttons
		std::vector<m3dCI::Button*> buttons;

		//Array of all active CodeEditors
		std::vector<m3dCI::CodeEditor*> codeEditors;

		//Array of all active CommandListers
		std::vector<m3dCI::CommandLister*> commandListers;
		
		/*
			This Class is a singleton. 
			Meaning, only one instance of this class may ever exist.
			This allows for all classes to access this object through the use of this instance value.
			An initial instantiation must occur with proper vaules passed into getInstance
			All further attempts to accesss this class can use dummy values for all parameters of getInstance
		*/
		static ObjectManager *instance;
		ObjectManager(Screen* screen);
	public:
		//Destructor: Objects that must be deleted when this object is deleted. Delete(nullptr) is fail-safe.
		virtual ~ObjectManager();

		static ObjectManager* getInstance();
		static ObjectManager* createInstance(Screen* screen);
		
		//The function which is called on every game frame.
		void OnUpdate();
		
		//Rectangle button creation. Adds button to array of active buttons.
		m3dCI::Button* CreateButton(int x, int y, int w, int h, m3d::Color color, m3d::Color borderColor, int borderWidth);
		
		//Circular button creation. Adds button to array of active buttons.
		m3dCI::Button* CreateButton(int x, int y, int radius, m3d::Color color, m3d::Color borderColor, int borderWidth);

		m3dCI::Button* CreateButton(int px, int py, m3d::Texture& t_texture);

		m3dCI::Button* CreateButton(int px, int py, const std::string& t_spriteSheet, int t_imageId);

		void DeleteButton(m3dCI::Button* button);

		m3dCI::CodeEditor* CreateCodeEditor(int x, int w, int borderWidth);

		void DeleteCodeEditor(m3dCI::CodeEditor* ce);

		m3dCI::CommandLister* CreateCommandLister();

		void DeleteCommandLister(m3dCI::CommandLister* ce);
};