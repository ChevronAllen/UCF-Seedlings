#include "scenes/MinigameSelectScene.hpp"
#include "scenes/MainMenuScene.hpp"

MinigameSelectScene::MinigameSelectScene()
{
	m3d::Screen * screen = GameManager::getScreen();

	MinigameSelectTopText = new TextMenuItem("Select a minigame");
	MinigameSelectTopText->setFontSize(1);
	MinigameSelectTopText->setFontWeight(1);
	MinigameSelectTopText->setColor(m3d::Color(0, 0, 0));
	menu->AddItem(MinigameSelectTopText);

	int width = MinigameSelectTopText->getWidth();
	int height = MinigameSelectTopText->getHeight();

	int topScreenWidth = screen->getScreenWidth(m3d::RenderContext::ScreenTarget::Top);
	int bottomScreenWidth = screen->getScreenWidth(m3d::RenderContext::ScreenTarget::Bottom);
	int screenHeight = screen->getScreenHeight();

	MinigameSelectTopText->setPosition((topScreenWidth / 2) - (width / 2), (screenHeight / 2) - (height / 2));

	int descriptorX = 125, topLeftY = 15, mwidth = 260, mheight = 170, border = 2;

	MinigameName = new TextMenuItem("[SELECTED MINIGAME]");
	MinigameName->setFontSize(0.9);
	MinigameName->setFontWeight(0.9);
	MinigameName->setColor(m3d::Color(0, 0, 0));
	MinigameName->setPosition(descriptorX + 10, topLeftY + 5);
	menu->AddItem(MinigameName);

	MinigameDescription = new TextMenuItem("If you see this then\n I made a mistake..");
	MinigameDescription->setFontSize(0.6);
	MinigameDescription->setFontWeight(0.6);
	MinigameDescription->setColor(m3d::Color(0, 0, 0));
	MinigameDescription->setPosition(descriptorX + 10, topLeftY + 45);
	menu->AddItem(MinigameDescription);

	minigameDesciptorBackground = new RectangleMenuItem(descriptorX + border, topLeftY + border, mwidth - (border * 2), mheight - (border * 2), m3d::Color(255,255,255,180));
	menu->AddItem(minigameDesciptorBackground);
	
	minigameDescriptorFrame[0] = new RectangleMenuItem(descriptorX, topLeftY, mwidth, 2, m3d::Color(17,15,11));
	minigameDescriptorFrame[1] = new RectangleMenuItem(descriptorX, topLeftY, 2, mheight, m3d::Color(17, 15, 11));
	minigameDescriptorFrame[2] = new RectangleMenuItem(descriptorX, topLeftY + mheight - border, mwidth, 2, m3d::Color(17, 15, 11));
	minigameDescriptorFrame[3] = new RectangleMenuItem(descriptorX + mwidth - border, topLeftY, 2, mheight, m3d::Color(17, 15, 11));

	for (int i = 0; i < 4; i++)
		menu->AddItem(minigameDescriptorFrame[i]);

	whiteBackground = new RectangleMenuItem(0, 0, 1000, 1000, m3d::Color(255, 255, 255));
	menu->AddItem(whiteBackground);

	grass = new SpriteMenuItem(*ResourceManager::getSprite("grassB1.png"));
	menu->AddItem(grass);

	bGrass = new SpriteMenuItem(*ResourceManager::getSprite("grassB2.png"));
	menu->AddItem(bGrass);

	int ButtonWidth = 50;
	int ButtonHeight = 50;

	int Rows = MINIGAME_COUNT / 3;
	int Columns = MINIGAME_COUNT / 2;

	int rowPadding = ((screenHeight * 0.25) * Rows - (ButtonHeight * Rows)) / (Rows - 1);
	int columnPadding = ((bottomScreenWidth * 0.25) * Columns - (ButtonWidth * Columns)) / (Columns - 1);//45

	for (int i = 0; i < MINIGAME_COUNT; i++)
	{
		int column = i % Columns;
		int row = i / 3;

		int x = (bottomScreenWidth * 0.25) / 2 + (columnPadding * column) + (ButtonWidth * column),
			y = (screenHeight * 0.25) + (rowPadding * row) + (ButtonHeight * row),
			w = ButtonWidth,
			h = ButtonHeight;

		ButtonMenuItem* newButton;
		if (minigames[i].getSmallSpriteLocation() != "NULL")
			newButton = new ButtonMenuItem(x, y, new m3dCI::Sprite(*ResourceManager::getSprite(minigames[i].getSmallSpriteLocation())));
		else
			newButton = new ButtonMenuItem(x, y, w, h, m3d::Color(255, 255, 255), m3d::Color(0, 0, 0), 3);

		newButton->SetOnRelease([&, i](int x, int y)
		{
			//second touch
			if (selectedMinigame == i)
			{
				if (i == MINIGAME_LIST::MAZE)
					SceneManager::setTransition(new MazeScene());
				else if (i == MINIGAME_LIST::PONG)
					SceneManager::setTransition(new PongScene());
				else if(i == MINIGAME_LIST::TIC_TAC_TOE)
					SceneManager::setTransition(new TicTacToeScene());
				else
				{
					// We decided to not let it transition.
					//SceneManager::setTransition(new Minigame());
				}
			}
			else
			{
				SelectMinigame(i);
			}
		});

		menu->AddItem(newButton);

		minigameOptions[column + (row * Columns)] = newButton;
	}

	draw();
}

MinigameSelectScene::~MinigameSelectScene()
{

}

void MinigameSelectScene::initialize()
{

}

void MinigameSelectScene::draw()
{
	m3d::Screen * scr = GameManager::getScreen();

	scr->drawTop(*grass, RenderContext::Mode::Flat);
	scr->drawBottom(*bGrass, RenderContext::Mode::Flat);

	if (selectedMinigame == -1)
		scr->drawTop(*MinigameSelectTopText, RenderContext::Mode::Flat);
	else
	{
		scr->drawTop(*minigameDesciptorBackground, RenderContext::Mode::Flat);
		for (int i = 0; i < 4; i++)
			scr->drawTop(*minigameDescriptorFrame[i], RenderContext::Mode::Flat);

		scr->drawTop(*MinigameName, RenderContext::Mode::Flat);
		scr->drawTop(*MinigameDescription, RenderContext::Mode::Flat);
		scr->drawTop(*selectedMinigameLargeSprite, RenderContext::Mode::Flat);
	}

	for (int i = 0; i < MINIGAME_COUNT; i++)
		scr->drawBottom(*minigameOptions[i], RenderContext::Mode::Flat);
}

void MinigameSelectScene::update()
{
	menu->OnUpdate();

	if (Input::btnReleased(m3d::buttons::DPadRight) || Input::btnReleased(m3d::buttons::CPadRight))
		SelectMinigame(selectedMinigame == -1 ? 0 : selectedMinigame + 1);
	else if (Input::btnReleased(m3d::buttons::DPadLeft) || Input::btnReleased(m3d::buttons::CPadLeft))
		SelectMinigame(selectedMinigame == -1 ? 0 : selectedMinigame - 1);
	else if (Input::btnReleased(m3d::buttons::DPadDown) || Input::btnReleased(m3d::buttons::CPadDown))
		SelectMinigame(selectedMinigame == -1 ? 0 : selectedMinigame + 3);
	else if (Input::btnReleased(m3d::buttons::DPadUp) || Input::btnReleased(m3d::buttons::CPadUp))
		SelectMinigame(selectedMinigame == -1 ? 0 : selectedMinigame - 3);

	if (Input::btnReleased(m3d::buttons::B))
	{
		if (selectedMinigame != -1)
		{
			int addedWidth = minigameOptions[selectedMinigame]->getWidth() * xScale - minigameOptions[selectedMinigame]->getWidth();
			int x = minigameOptions[selectedMinigame]->getXPosition() + (addedWidth / 2);
			int addedHeight = minigameOptions[selectedMinigame]->getHeight() * yScale - minigameOptions[selectedMinigame]->getHeight();
			int y = minigameOptions[selectedMinigame]->getYPosition() + (addedHeight / 2);

			minigameOptions[selectedMinigame]->setScale(1.0f, 1.0f);
			minigameOptions[selectedMinigame]->setPosition(x, y);

			selectedMinigame = -1;
		}
		else
		{
			SceneManager::setTransition(new MainMenuScene());
			return;
		}
	}

	if (Input::btnReleased(m3d::buttons::A) && selectedMinigame != -1)
		minigameOptions[selectedMinigame]->CallOnRelease(0,0);
}

void MinigameSelectScene::SelectMinigame(int index)
{
	index = (index < 0 ? MINIGAME_COUNT + index : index) % MINIGAME_COUNT;

	if (index < 0 || index >= MINIGAME_COUNT)
		return;

	if (selectedMinigame != -1)
	{
		int addedWidth = minigameOptions[selectedMinigame]->getWidth() * xScale - minigameOptions[selectedMinigame]->getWidth();
		int x = minigameOptions[selectedMinigame]->getXPosition() + (addedWidth / 2);
		int addedHeight = minigameOptions[selectedMinigame]->getHeight() * yScale - minigameOptions[selectedMinigame]->getHeight();
		int y = minigameOptions[selectedMinigame]->getYPosition() + (addedHeight / 2);

		minigameOptions[selectedMinigame]->setScale(1.0f, 1.0f);
		minigameOptions[selectedMinigame]->setPosition(x, y);

		menu->RemoveItem(selectedMinigameLargeSprite);
	}

	selectedMinigame = index;

	selectedMinigameLargeSprite = new SpriteMenuItem(*ResourceManager::getSprite(minigames[index].getLargeSpriteLocation()));
	menu->AddItem(selectedMinigameLargeSprite);
	selectedMinigameLargeSprite->setPosition(10, 44);

	int addedWidth = minigameOptions[index]->getWidth() * xScale - minigameOptions[index]->getWidth();
	int x = minigameOptions[index]->getXPosition() - (addedWidth / 2);
	int addedHeight = minigameOptions[index]->getHeight() * yScale - minigameOptions[index]->getHeight();
	int y = minigameOptions[index]->getYPosition() - (addedHeight / 2);

	minigameOptions[index]->setScale(xScale, yScale);
	minigameOptions[index]->setPosition(x, y);

	MinigameName->setText(minigames[index].getName());
	MinigameDescription->setText(minigames[index].getDescription());
}