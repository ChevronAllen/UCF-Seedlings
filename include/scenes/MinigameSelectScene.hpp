#pragma once

#include "scene.hpp"
#include "MinigameDescriptor.hpp"
#include "MazeScene.hpp"
#include "PongScene.hpp"
#include "TicTacToeScene.hpp"

#include "gameManager.hpp"
#include "inputManager.hpp"
#include "sceneManager.hpp"
#include "resourceManager.hpp"

#define MINIGAME_COUNT 6
#define xScale 1.3f
#define yScale 1.3f

/**
	@brief The MinigameSelectScene is the screen which shows all minigames to choose from
	- List Minigame Options
	- Load into respective Minigames
	- Give sneak peak of each Minigame
**/
class MinigameSelectScene : public Scene
{
	private:		
		///@brief List of Minigame ID's. This is used to link each button to the proper Minigame/MinigameDescriptor
		enum MINIGAME_LIST
		{
			MAZE = 0,
			TIC_TAC_TOE = 1,
			PONG = 2,
		};
		
		///@brief List of MinigameDescriptors which make up the Boxes on screen.
		MinigameDescriptor minigames[MINIGAME_COUNT] =
		{
			MinigameDescriptor("Maze", "Navigate a player through a\nmaze.\n\n\nAims to teach: Object Movement", "mazeSmall.png", "mazeLarge.png"),
			MinigameDescriptor("Tic-Tac-Toe", "Get three O's in a row!\n\n\n\nAims to teach: Object Creation", "TTTSmall.png", "TTTLarge.png"),
			MinigameDescriptor("Pong", "Don't let the ball bounce\ninto your base!\n\n\nAims to teach: Conditionals", "pongSmall.png", "pongLarge.png"),
			MinigameDescriptor(),
			MinigameDescriptor(),
			MinigameDescriptor()
		};

		///@brief curently selected Minigame ID
		int selectedMinigame = -1;

		RectangleMenuItem *whiteBackground;

		SpriteMenuItem* grass;
		SpriteMenuItem* bGrass;

		SpriteMenuItem *selectedMinigameLargeSprite = nullptr;
		TextMenuItem *MinigameSelectTopText = nullptr, *MinigameDescription = nullptr, *MinigameName = nullptr;
		ButtonMenuItem* minigameOptions[MINIGAME_COUNT];
		RectangleMenuItem* minigameDescriptorFrame[4];
		RectangleMenuItem* minigameDesciptorBackground;

	public:
	
		/**
			@brief Constructor for MinigameSelectScene.
			Responsible for creating all necessary MenuItems.
		**/
		MinigameSelectScene();
		
		/**
			@brief Deconstructor for MinigameSelectScene.
			Responsible for deleting all needed MenuItems.
		**/
		~MinigameSelectScene();

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

		/**
			@brief Function called to select a specific minigame
			@param index ID of Minigame to select
		**/
		void SelectMinigame(int index);
};
