#include "sandbox.hpp"
#include "scenes/PongScene.hpp"
#include "scenes/MinigameSelectScene.hpp"


#define t(x) AddCommand(x)
#define func(a) [&]() { t(a); }
#define PAIR(name, command) { name, [&]() { t(command); }}
#define NULLPartialPAIR(name) { name, nullptr }
#define NULLPAIR PAIR("", nullptr)
#define COLORPAIR(name, r, g, b) PAIR(name, new ColorCommand(name, m3d::Color(r,g,b,255)))

#define SCOREBOARD_PADDING 30
#define SCOREBOARD_TOP_PADDING 5

#define Ball static_cast<PongBall*>(findObject(ballID))
#define LeftPaddle static_cast<PongPaddle*>(findObject(paddleID))
#define RightPaddle static_cast<PongPaddle*>(findObject(enemyID))

#define NullSafeCallFunction(ob, func) if(ob != nullptr) ob->func

#define LeftPaddleNullSafeCallFunction(funcName) NullSafeCallFunction(LeftPaddle, funcName)
#define RightPaddleNullSafeCallFunction(funcName) NullSafeCallFunction(RightPaddle, funcName)
#define BallNullSafeCallFunction(funcName) NullSafeCallFunction(Ball, funcName)

PongScene::PongScene(bool showTutorial)
{
	if (!showTutorial)
		tutCount = TUTORIAL_POPUP_COUNT;

	//showGridLines = false;

	commandLister->OverrideTabCommandListObjects(
		{
			PAIR("Set_X", new SetXCommand("varName")),
			PAIR("Set_Y", new SetYCommand("varName")),
			PAIR("Scale", new ScaleCommand("1", "1")),
			PAIR("Scale_X", new ScaleCommand("1", "-1")),
			PAIR("Scale_Y", new ScaleCommand("-1", "1"))
		}, 2
		);
}

PongScene::~PongScene()
{

}

void PongScene::initialize(){
	Minigame::initialize();

	// assign player and enemy points and points to win 
	for (int i = 0; i < TEAM_COUNT; i++)
		points[i] = 0;
	
	// initalize the scene background
	wallpaper = new SpriteMenuItem(*(ResourceManager::getSprite("pong1.png")));
	wallpaper->setCenter(0, 0);
	wallpaper->setScale(1, 1);
	menu->AddItem(wallpaper);
	
	//  initialize the win popup window 
	wPopup = new SpriteMenuItem(*(ResourceManager::getSprite("win_popup.png")));
	wPopup->setPosition(80, 20);
	menu->AddItem(wPopup);

	//  initialize the lose popup window 
	lPopup = new SpriteMenuItem(*(ResourceManager::getSprite("lose_popup.png")));
	lPopup->setPosition(80, 20);
	menu->AddItem(lPopup);

	//	initialize Score menu items
	for (int i = 0; i < TEAM_COUNT; i++)
	{
		scoreBoard[i] = new TextMenuItem(std::to_string(points[i]));

		scoreBoard[i]->setFontSize(2.0f);
		scoreBoard[i]->setFontWeight(2.0f);
		menu->AddItem(scoreBoard[i]);
	}

	//For some reason, the text->getWidth for scoreBoard[0] returns 34 when the real result is 23.
	//Not sure how to fix it inside the Text object.
	int realWidth = 23;
	scoreBoard[0]->setPosition(TOPSCREEN_WIDTH / 2 - realWidth - SCOREBOARD_PADDING, SCOREBOARD_TOP_PADDING);
	scoreBoard[1]->setPosition(TOPSCREEN_WIDTH / 2 + SCOREBOARD_PADDING, SCOREBOARD_TOP_PADDING);
	
	//  initialize the tutorial windows 
	for (int i = 0; i < TUTORIAL_POPUP_COUNT; i++)
	{
		tutorial[i] = new SpriteMenuItem(*(ResourceManager::getSprite("pong_tutorial_" + std::to_string(i + 1) + ".png")));
		tutorial[i]->setPosition(80, 20);
		menu->AddItem(tutorial[i]);
	}

	if (tutCount != TUTORIAL_POPUP_COUNT)
	{
		tutCount = 0;
		popup = tutorial[tutCount];
	}

	// initialize the game objects and add them to the hash map
	ballID = addObject(new PongBall());
	setObjectName("ball", ballID);
	BallNullSafeCallFunction(initialize)();

	paddleID = addObject(new PongPaddle(20, 90));
	setObjectName("player", paddleID);
	LeftPaddleNullSafeCallFunction(initialize)();

	enemyID = addObject(new PongPaddle(380, 90, ballID));
	setObjectName("enemy", enemyID);
	RightPaddleNullSafeCallFunction(initialize)();

	currentState = PongState::TutorialMessage;
}

void PongScene::draw(){
	Minigame::draw();

	m3d::Screen *screen = GameManager::getScreen();

	wallpaper->setPosition(0, 0);
	screen->drawTop(*wallpaper, m3d::RenderContext::Mode::Flat, 0);

	BallNullSafeCallFunction(draw)();
	LeftPaddleNullSafeCallFunction(draw)();
	RightPaddleNullSafeCallFunction(draw)();
	
	for (int i = 0; i < TEAM_COUNT; i++)
		screen->drawTop(*scoreBoard[i], m3d::RenderContext::Mode::Flat, 4);

	if (currentState == PongState::TutorialMessage)
	{
		screen->drawTop(*popup, m3d::RenderContext::Mode::Flat, 5);
	}

	// display win screen
	if (currentState == PongState::Win)
	{
		screen->drawTop(*wPopup, m3d::RenderContext::Mode::Flat, 5);
		screen->drawTop(*wPopup);
	}

	// display lose screen
	if (currentState == PongState::Lose)
	{
		screen->drawTop(*lPopup, m3d::RenderContext::Mode::Flat, 5);
	}
}

void PongScene::load(){ Minigame::load(); }; //any data files

void PongScene::unload(){ Minigame::unload(); };

void PongScene::reset()
{
	currentState = PongState::Requesting;

	for (int i = 0; i < TEAM_COUNT; i++)
		points[i] = 0;

	for (int i = 0; i < TEAM_COUNT; i++)
		scoreBoard[i]->setText(std::to_string(points[i]));

	if (Ball == nullptr)
	{
		ballID = addObject(new PongBall());
		setObjectName("ball", ballID);
		BallNullSafeCallFunction(initialize)();
	}


	if (LeftPaddle == nullptr)
	{
		paddleID = addObject(new PongPaddle(20, 90));
		setObjectName("player", paddleID);

		LeftPaddleNullSafeCallFunction(initialize)();
	}


	if (RightPaddle == nullptr)
	{
		enemyID = addObject(new PongPaddle(380, 90, ballID));
		setObjectName("enemy", enemyID);
		RightPaddleNullSafeCallFunction(initialize)();
	}

	BallNullSafeCallFunction(reset)();
	LeftPaddleNullSafeCallFunction(reset)(true);
	RightPaddleNullSafeCallFunction(reset)(true);
}

void PongScene::update()
{
	Minigame::update();

	switch(currentState)
	{
		case PongState::TutorialMessage:
			blockButtons = true;

			// player reads the tutorial 
			if (buttons::buttonPressed(buttons::A)) 
			{
				if (tutCount < TUTORIAL_POPUP_COUNT)
				{
					tutCount++;

					if(tutCount < TUTORIAL_POPUP_COUNT)
						popup = tutorial[tutCount];
				}
			}
			// the player submits their code
			if (buttons::buttonDown(buttons::Start) || tutCount >= TUTORIAL_POPUP_COUNT)
			{
				tutCount = 0;

				std::vector<CommandObject*> startingCommands =
				{
					new WhileCommand("true", true, false),
					new SelectCommand("ball"),
					new GetYCommand("by"),
					new SelectCommand("player"),
					new SetYCommand("by"),
					new EndCommand(true)

				};

				SceneManager::RequestUserCode(startingCommands, [&](std::vector<CommandObject*> commands) { SubmitPongCode(commands); });

				currentState = PongState::Requesting;
			}
		break;
		case PongState::Requesting:
			blockButtons = false;

			if (Input::btnReleased(m3d::buttons::B))
				SceneManager::setTransition(new MinigameSelectScene());
		break;
		case PongState::Win:
			blockButtons = true;

			if (Input::btnReleased(m3d::buttons::B))
				SceneManager::setTransition(new MinigameSelectScene());
			if (Input::btnReleased(m3d::buttons::A)) // restart the game without showing the tutorial message
				reset();
		break;
		case PongState::Lose:
			blockButtons = true;

			if (Input::btnReleased(m3d::buttons::B)) // return to minigame select screen
				SceneManager::setTransition(new MinigameSelectScene());
			if (Input::btnReleased(m3d::buttons::A)) // restart the game 
				SceneManager::setTransition(new PongScene());
		break;
		case PongState::Execute:

			// determine winner and loser
			if (points[0] == MATCH_POINT)
			{
				m_sandbox->setThreadState(THREAD_CLEAR);

				currentState = PongState::Win;
			}
			else if (points[1] == MATCH_POINT || Ball == nullptr)
			{
				m_sandbox->setThreadState(THREAD_CLEAR);

				currentState = PongState::Lose;
			}

			if (Ball != nullptr)
			{
				BoundingBox ballAABB = Ball->getAABB();

				// handle ball bouncing
				// We don't want the ball interacting with itself hence i != ballID
				for (int i = 0; i < m_hashmap.size(); i++)
				{
					if (m_hashmap[i] == nullptr || i == ballID)
						continue;

					BoundingBox aabb = m_hashmap[i]->getAABB();

					// check if ball is inside object
					if (aabb.intersects(ballAABB))
					{
						//if so, bounce off

						//Determine which side of the ball hit the wall

						int pixelDifference = 3;

						//We can't take corners, and instead need to detect using a one pixel BB on each side of each corner.
						BoundingBox TL = BoundingBox(ballAABB.getX() + pixelDifference, ballAABB.getY(), 1, 1),
							TR = BoundingBox(ballAABB.getX() + ballAABB.getWidth() - pixelDifference, ballAABB.getY(), 1, 1),
							LT = BoundingBox(ballAABB.getX(), ballAABB.getY() + pixelDifference, 1, 1),
							LB = BoundingBox(ballAABB.getX(), ballAABB.getY() + ballAABB.getHeight() - pixelDifference, 1, 1),
							BL = BoundingBox(ballAABB.getX() + pixelDifference, ballAABB.getY() + ballAABB.getHeight(), 1, 1),
							BR = BoundingBox(ballAABB.getX() + ballAABB.getWidth() - pixelDifference, ballAABB.getY() + ballAABB.getHeight(), 1, 1),
							RT = BoundingBox(ballAABB.getX() + ballAABB.getWidth(), ballAABB.getY() + pixelDifference, 1, 1),
							RB = BoundingBox(ballAABB.getX() + ballAABB.getWidth(), ballAABB.getY() + ballAABB.getHeight() - pixelDifference, 1, 1);

						// set ball's direction based on where it collided
						if (aabb.intersects(TL) || aabb.intersects(TR))
							Ball->SetDirection(0, 1);
						else if (aabb.intersects(BL) || aabb.intersects(BR))
							Ball->SetDirection(0, -1);
						else if (aabb.intersects(LT) || aabb.intersects(LB))
							Ball->SetDirection(1, 0);
						else if (aabb.intersects(RT) || aabb.intersects(RB))
							Ball->SetDirection(-1, 0);

						if (RightPaddle != nullptr && m_hashmap[i] == RightPaddle)
							RightPaddle->ballBouncedOffPaddle();
					}
				}
				
				// ball goes out of x bounds, a goal has been scored
				if (Ball->getXPosition() < 0 || Ball->getXPosition() + Ball->getWidth() > TOPSCREEN_WIDTH)
				{
					if (Ball->getXPosition() < 0) // enemy scores
					{
						points[1]++;
					}
					else // player scores 
					{
						points[0]++;
					}

					BallNullSafeCallFunction(reset)();
					RightPaddleNullSafeCallFunction(reset)();
				}

				// ball goes out of y bounds, a collision with the wall occurs 
				if (Ball->getYPosition() < 0 || Ball->getYPosition() + Ball->getHeight() >= TOPSCREEN_HEIGHT)
				{
					// Bounce off top or bottom wall
					Ball->toggleYDir();
				}

				if(LeftPaddle != nullptr)
					LeftPaddle->update();
				if (RightPaddle != nullptr)
					RightPaddle->update();
				if (Ball != nullptr)
					Ball->update();
			}

			//update score
			for (int i = 0; i < TEAM_COUNT; i++)
				scoreBoard[i]->setText(std::to_string(points[i]));
		break;
	}
}

// run user code 
void PongScene::SubmitPongCode(std::vector<CommandObject*> luaCode)
{
    #ifdef DEBUG_MINIGAME
	Util::PrintLine("pong: queue commands");
    #endif DEBUG_MINIGAME
	std::string str = CommandObject::ConvertBulk(luaCode);

	m_sandbox->executeStringQueued(str);

	currentState = PongState::Execute;
}

void PongScene::onEnter(){ Minigame::onEnter(); };
void PongScene::onExit() { Minigame::onExit(); };
bool PongScene::checkWinCond()
{
	
			
};
void PongScene::loadScene() { Minigame::loadScene(); };
void PongScene::loadWinScr() { Minigame::loadWinScr(); };
void PongScene::loadLoseScr() { Minigame::loadLoseScr(); };
void PongScene::requestUI() { Minigame::requestUI(); };
void PongScene::closeGame() { Minigame::closeGame(); };