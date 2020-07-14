#include "MazeScene.hpp"
#include "MinigameSelectScene.hpp"

MazeScene::MazeScene()
{
    //array traversers
    x = 1.0;
	y = 0.0;
}

MazeScene::~MazeScene()
{

}

void MazeScene::initialize(){
	Minigame::initialize();

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
	winScreen = new RectangleMenuItem(0,0,320,240,*colorRec);
	menu->AddItem(winScreen);
	winPrompt = new TextMenuItem("You Win!",*colorText);
	menu->AddItem(winPrompt);
	winPrompt->setPosition(90,30);
	winPrompt->setFontSize(.5);
	winPrompt->setFontWeight(.5);
	winPrompt->setPosition(160,120);
			
	prompt = new TextMenuItem(" Use move commands to traverse \n the maze. In order to add a move \n command select Add, then go to\n the tab with the arrows. There\n you can select up, down, left \n or right as a direction to\n move in the maze. You can then\n change the amount of spaces you\n want to move by selecting it and\n clicking edit. Be sure to enter all\n commands you will need to get to\n the end of the maze before running.",*colorText);
	menu->AddItem(prompt);
	prompt->setPosition(90,30);
	prompt->setFontSize(.5);
	prompt->setFontWeight(.5);
	wallpaper = new SpriteMenuItem(*(ResourceManager::getSprite("maze1.png")));
	menu->AddItem(wallpaper);
	//  Initialize popup BG
    popup = new SpriteMenuItem(*(ResourceManager::getSprite("menu_popup.png")));
	menu->AddItem(popup);
	popup->setPosition(80,20);
	//wallpaper->setTexture(*texture);
	wallpaper->setCenter(0,0);
	wallpaper->setScale(1,1);

	currentState = MazeState::TutorialMessage;
}

void MazeScene::draw(){
	Minigame::draw();

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
		
void MazeScene::load(){ Minigame::load(); }; //any data files
        
void MazeScene::unload(){ Minigame::unload(); };
        
void MazeScene::update()
{
	Minigame::update();

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

				SceneManager::RequestUserCode(startingCommands, [&](std::vector<CommandObject*> commands) { SubmitMazeCode(commands); });
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
			if (Input::btnReleased(m3d::buttons::B))
				SceneManager::setTransition(new MinigameSelectScene());
			break;
	}
};

void MazeScene::SubmitMazeCode(std::vector<CommandObject*> luaCode)
{
	
    Util::PrintLine("maze: queue commands");
    std::string str = CommandObject::ConvertBulk(luaCode);


	//Util::getInstance()->PrintLine(str);
	//executeInSandbox(str);
    m_sandbox->executeStringQueued(str);

    Util::PrintLine("done");

	currentState = MazeState::Execute;
}

void MazeScene::onEnter(){ Minigame::onEnter(); };
void MazeScene::onExit() { Minigame::onExit(); };
bool MazeScene::checkWinCond()
{
	if(runner->winCond())
		return true;
	else
	{
		return false;
	}
			
};
void MazeScene::loadScene() { Minigame::loadScene(); };
void MazeScene::loadWinScr() { Minigame::loadWinScr(); };
void MazeScene::loadLoseScr() { Minigame::loadLoseScr(); };
void MazeScene::requestUI() { Minigame::requestUI(); };
void MazeScene::closeGame() { Minigame::closeGame(); };