#include "MainMenuScene.hpp"

#include "MinigameSelectScene.hpp"

MainMenuScene::MainMenuScene()
{
	m3d::Screen * screen = GameManager::getScreen();

	StartupText = new TextMenuItem("Seedlings");
	menu->AddItem(StartupText);
	whiteBackground = new RectangleMenuItem(0, 0, 1000, 1000, m3d::Color(255, 255, 255));
	menu->AddItem(whiteBackground);

	int topScreenWidth = screen->getScreenWidth(m3d::RenderContext::ScreenTarget::Top);
	int bottomScreenWidth = screen->getScreenWidth(m3d::RenderContext::ScreenTarget::Bottom);
	int screenHeight = screen->getScreenHeight();
	int clickHereToContinueX = ((bottomScreenWidth)-(bottomScreenWidth*0.8)) / 2;
	int clickHereToContinueY = ((screenHeight)-(screenHeight*0.3));

	ClickHereToContinue = new ButtonMenuItem(clickHereToContinueX, clickHereToContinueY, (bottomScreenWidth*0.8), (screenHeight*0.2), m3d::Color(255, 255, 255), m3d::Color(0, 0, 0), 3);
	menu->AddItem(ClickHereToContinue);

	apple = new SpriteMenuItem(*ResourceManager::getSprite("apple.png"));
	menu->AddItem(apple);
}

MainMenuScene::~MainMenuScene()
{
	
}

void MainMenuScene::initialize()
{
	m3d::Screen * screen = GameManager::getScreen();

	int topScreenWidth = screen->getScreenWidth(m3d::RenderContext::ScreenTarget::Top);
	int bottomScreenWidth = screen->getScreenWidth(m3d::RenderContext::ScreenTarget::Bottom);
	int screenHeight = screen->getScreenHeight();

	StartupText->setFontSize(2);
	StartupText->setFontWeight(2);
	StartupText->setColor(m3d::Color(0, 0, 0));
	StartupText->setOpacity(0);

	int width = StartupText->getWidth();
	int height = StartupText->getHeight();

	StartupText->setPosition((topScreenWidth / 2) - (width / 2) + 25, (screenHeight / 2) - (height / 2));

	int clickHereToContinueX = ((bottomScreenWidth)-(bottomScreenWidth*0.8)) / 2;
	int clickHereToContinueY = ((screenHeight)-(screenHeight*0.3));

	ClickHereToContinue->SetText("Press start to Play!");
	ClickHereToContinue->SetOnRelease([this](int x, int y) { SceneManager::setTransition(new MinigameSelectScene()); });
	ClickHereToContinue->SetActive(false);

	apple->setCenter(apple->m_sprite.params.pos.w / 2, apple->m_sprite.params.pos.h / 2);
	apple->setPosition(topScreenWidth * 0.75 + 25, -(apple->m_sprite.params.pos.h / 2));
	apple->setScale(0.35f, 0.35f);
}

void MainMenuScene::draw()
{
	m3d::Screen * scr = GameManager::getScreen();

	if (Util::IsConsoleDrawn())
		return;

	int topScreenWidth = scr->getScreenWidth(m3d::RenderContext::ScreenTarget::Top);
	int bottomScreenWidth = scr->getScreenWidth(m3d::RenderContext::ScreenTarget::Bottom);
	int screenHeight = scr->getScreenHeight();

	if (m3d::buttons::buttonReleased(m3d::buttons::Button::Start)
		|| m3d::buttons::buttonReleased(m3d::buttons::Button::A)
		|| Input::btnReleased(m3d::buttons::Touch))
	{
		if (!ClickHereToContinue->GetActive())
		{
			apple->setXPosition(topScreenWidth * 0.1 + 25);
			apple->setYPosition((screenHeight / 2) - 10);
			apple->setRotation(0);
			StartupText->setOpacity(255);
		}
		else
		{
			/*if (m3d::buttons::buttonReleased(m3d::buttons::Button::Start))
			{
				MenuHandler::getInstance()->TransitionTo(MenuHandler::MenuState::MinigameSelect);
			}*/
		}
	}

	scr->drawTop(*whiteBackground, RenderContext::Mode::Flat);
	scr->drawBottom(*whiteBackground, RenderContext::Mode::Flat);
	scr->drawTop(*StartupText, RenderContext::Mode::Flat);
	if (apple->getYPosition() < (screenHeight / 2 - 10))
	{
		apple->setYPosition(apple->getYPosition() + 4);
	}
	else
	{
		if (apple->getXPosition() > topScreenWidth * 0.1 + 25)
		{
			apple->setXPosition(apple->getXPosition() - 3);
			apple->rotate(-8.25f);
		}
		else if (StartupText->getOpacity() < 255)
		{
			apple->setRotation(0.0f);
			apple->setXPosition(topScreenWidth * 0.1 + 25);
			apple->setYPosition((screenHeight / 2) - 10);
			StartupText->setOpacity(std::min((int)StartupText->getOpacity() + 3, 255));
		}
		else
		{
			ClickHereToContinue->SetActive(true);
			scr->drawBottom(*ClickHereToContinue);
		}
	}

	scr->drawTop(*apple);
}

void MainMenuScene::update()
{
	menu->OnUpdate();
}