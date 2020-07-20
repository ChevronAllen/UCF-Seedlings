#pragma once
#include "scene.hpp"

#include "../gameManager.hpp"
#include "../inputManager.hpp"
#include "../sceneManager.hpp"
#include "../resources.h"
#include "../Menu/MenuItems/ButtonMenuItem.hpp"


/**
	@brief The MainMenuScene is the splash screen first shown on the game being loaded
	- Show Loading Animation
	- Ability to transfer to MinigameSelectScene
**/
class MainMenuScene : public Scene
{
	private:
		RectangleMenuItem* whiteBackground;

		TextMenuItem* StartupText;
		ButtonMenuItem* ClickHereToContinue = nullptr;
		SpriteMenuItem* apple;

	public:
		/**
			@brief Constructor for MainMenuScene.
			Responsible for creating all necessary MenuItems.
		**/
		MainMenuScene();
		
		/**
			@brief Deconstructor for MainMenuScene.
			Responsible for deleting all needed MenuItems.
		**/
		~MainMenuScene();

		/**
			@brief Initialization of values of all MenuItems.
		**/
		void initialize();
		
		/**
			@brief Function responsible for drawing the MainMenuScene
			Updates each game frame.
		**/
		void draw();
		
		/**
			@brief Function responsible for determining Menu Clicks and Apple Animation.
			Updates each game frame.
		**/
		void update();

		/**
			@brief Load Scene Data
			UNUSED
		**/
		void load() {};
		
		/**
			@brief Unload Scene Data
			UNUSED
		**/
		void unload() {};
		
		/**
			@brief Function called when Minigame is first created
			UNUSED
		**/
		void onEnter() {};
		
		/**
			@brief Function called before Minigame is destroyed
			UNUSED
		**/
		void onExit() {};
};
