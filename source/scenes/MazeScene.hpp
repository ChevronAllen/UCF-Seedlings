#pragma once
#include "../gameManager.hpp"
#include "../sceneManager.hpp"
#include "../MenuHandler.hpp"
#include "../scene.hpp"
#include "../resources.h"
#include "../minigame.hpp"
#include "../gameObjects/mazePlayer.hpp"

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
		MazeScene(): Minigame()
		{
            //array traversers
            x = 1.0;
			y = 0.0;
		}

		void initialize(){
            

        //loads and gets maze texture
			//texture = new m3dCI::Sprite(*(ResourceManager::getSprite("wall.png")));
            //sprite* spr = new m3d::Sprite();

       //initialize playable character
            runner = new TerminalObject(wallHolder);

			runnerID = addObject(runner);
            runner->initialize();
			setObjectName("runner", runnerID);
			//addObject(runner);

       //Load text and bottom screen background color
			colorRec = new m3d::Color(150,150,150);
			colorText = new m3d::Color(0,0,0);

       //initializes text and bottom screen background
			winScreen = new m3d::Rectangle(0,0,320,240,*colorRec);
			winPrompt = new m3dCI::Text("You Win!",*colorText);
			winPrompt->setPosition(90,30);
			winPrompt->setFontSize(.5);
			winPrompt->setFontWeight(.5);
			winPrompt->setPosition(160,120);
			
			prompt = new m3dCI::Text(" Use move commands to traverse \n the maze. In order to add a move \n command select Add, then go to\n the tab with the arrows. There\n you can select up, down, left \n or right as a direction to\n move in the maze. You can then\n change the amount of spaces you\n want to move by selecting it and\n clicking edit. Be sure to enter all\n commands you will need to get to\n the end of the maze before running.",*colorText);
			prompt->setPosition(90,30);
			prompt->setFontSize(.5);
			prompt->setFontWeight(.5);
			wallpaper   = new m3dCI::Sprite(*(ResourceManager::getSprite("maze1.png")));
            //  Initialize popup BG
            popup  = new m3dCI::Sprite(*(ResourceManager::getSprite("menu_popup.png")));
            popup->setPosition(80,20);
		    //wallpaper->setTexture(*texture);
		    wallpaper->setCenter(0,0);
		    wallpaper->setScale(1,1);

			currentState = MazeState::TutorialMessage;
		}

		void draw(){
			m3d::Screen * screen = GameManager::getScreen();

		    wallpaper->setPosition(0,0);
            screen->drawTop(*wallpaper);

            if(currentState == MazeState::TutorialMessage)
            {   
                screen->drawTop(*popup);
				screen->drawTop(*prompt);
				//use m3dci for prompt
            }

			if(currentState == MazeState::Win)
            {   
                screen->drawTop(*popup);
				screen->drawTop(*winPrompt);
				//use m3dci for prompt
            }

			//screen->drawBottom(*bwallpaper);
			//screen->drawBottom(*prompt);

            runner->draw();

		}
		
        void load(){}; //any data files
        
        void unload(){};
        
        void update()
        {
            

			switch (currentState)
			{
				case MazeState::TutorialMessage:

					if (buttons::buttonDown(buttons::Start))
					{
						currentState = MazeState::Requesting;

						std::vector<CommandObject*> startingCommands =
						{
							new SelectCommand("runner",true,true),
							new RightCommand("18"),
							new DownCommand("5"),
							new LeftCommand("18"),
							new DownCommand("5"),
							new RightCommand("18"),
							new DownCommand("5"),
							new LeftCommand("18"),
							new DownCommand("5"),
							new RightCommand("18")
						};

						MenuHandler::RequestUserCode(startingCommands, [&](std::vector<CommandObject*> commands) { SubmitMazeCode(commands); });
					}
					break;
				case MazeState::Execute:
					if(checkWinCond() == 1)
					{
						currentState = MazeState::Win;
					}
					break;
				case MazeState::Win:
					break;
				case MazeState::Lose:
					break;
				case MazeState::Requesting:
					break;
			}
        };

		void SubmitMazeCode(std::vector<CommandObject*> luaCode)
		{
			//std::string str = "coroutine.create(function ()" + CommandObject::ConvertBulk(luaCode) + " end)" ;
            Util::PrintLine("execute commands");
            std::string str = CommandObject::ConvertBulk(luaCode);


			//Util::getInstance()->PrintLine(str);
			//executeInSandbox(str);
            Util::PrintLine("done");

			currentState = MazeState::Execute;
		}

        void onEnter(){};
        void onExit(){};
        bool checkWinCond()
		{
			if(runner->winCond())
				return true;
			else
			{
				return false;
			}
			
		};
        void loadScene(){};
        void loadWinScr(){};
        void loadLoseScr(){};
        void requestUI(){};
        void closeGame(){};
        void executeBefore(){};
        void executeAfter(){};
};
