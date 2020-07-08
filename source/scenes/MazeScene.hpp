#pragma once
#include "../gameManager.hpp"
#include "../sceneManager.hpp"
#include "scene.hpp"
#include "../resources.h"
#include "../gameObjects/mazePlayer.hpp"

#include "MainMenuScene.hpp"

class MazeScene : public Minigame
{
	private:
		m3dCI::Sprite *wallpaper;
		m3dCI::Sprite *texture;
        m3dCI::Sprite* popup;
		m3d::Rectangle *winScreen;
        m3d::Rectangle *loseScreen;
		m3d::Color *colorRec;
		m3d::Color *colorText;
		m3dCI::Text *prompt;
		m3dCI::Text *winPrompt;
        TerminalObject *runner;
		int x, y, runnerID;
        bool walls[12][20] ={{ 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
							{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
							{ 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1},
							{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
							{ 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
							{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
							{ 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1},
							{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
							{ 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
							{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
							{ 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, 
							{ 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}};


			
            //2d array acting as map of array
        bool (*wallHolder)[12][20] = &walls;
		//wallHolder = &walls;

		enum MazeState
		{
			TutorialMessage,
			Requesting,
			Execute,
			Win,
			Lose
		};
		MazeState currentState;
	public:
		MazeScene();

		void initialize();

		void draw();
		
		void load();
        
		void unload();
        
		void update();

		void SubmitMazeCode(std::vector<CommandObject*> luaCode);

		void onEnter();
		void onExit();
		bool checkWinCond();
		void loadScene();
		void loadWinScr();
		void loadLoseScr();
		void requestUI();
		void closeGame();
};
