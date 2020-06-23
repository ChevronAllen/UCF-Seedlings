#include "mainMenu.hpp"

MainMenu::MainMenu(m3d::Screen* screen) :
	Menu(screen)
{
	StartupText = new m3dCI::Text("GZLO");
	StartupText->setFontSize(2);
	StartupText->setFontWeight(2);
	StartupText->setColor(m3d::Color(0, 0, 0));

	int width = StartupText->getWidth();
	int height = StartupText->getHeight();
	
	int topScreenWidth = screen->getScreenWidth(m3d::RenderContext::ScreenTarget::Top);
	int bottomScreenWidth = screen->getScreenWidth(m3d::RenderContext::ScreenTarget::Bottom);
	int screenHeight = screen->getScreenHeight();

	StartupText->setPosition((topScreenWidth / 2) - (width / 2), (screenHeight / 2) - (height / 2));

	whiteBackground = new m3d::Rectangle(0, 0, 1000, 1000, m3d::Color(255, 255, 255));

	int clickHereToContinueX = ((bottomScreenWidth)-(bottomScreenWidth*0.8)) / 2;
	int clickHereToContinueY = ((screenHeight)-(screenHeight*0.3));

	ClickHereToContinue = om->CreateButton(clickHereToContinueX, clickHereToContinueY, (bottomScreenWidth*0.8), (screenHeight*0.2), m3d::Color(255, 255, 255), m3d::Color(0, 0, 0), 3);
	ClickHereToContinue->SetText("Press start to Play!");
	ClickHereToContinue->OnTouch = &ClickHereToContinue_OnClick;
}

void MainMenu::OnUpdate()
{
	if (util->IsConsoleDrawn())
		return;

	if (m3d::buttons::buttonReleased(m3d::buttons::Button::Start))
		ClickHereToContinue->OnTouch(ClickHereToContinue);

	scr->drawTop(*whiteBackground, RenderContext::Mode::Flat);
	scr->drawBottom(*whiteBackground, RenderContext::Mode::Flat);
	scr->drawTop(*StartupText, RenderContext::Mode::Flat);
	scr->drawBottom(*ClickHereToContinue, RenderContext::Mode::Flat);
}

//Destructor: Objects that must be deleted when this object is deleted. Delete(nullptr) is fail-safe.
MainMenu::~MainMenu()
{
	delete(StartupText);
	//The following commented out object don't have deletion support. They *should* be grabbed by the garbage collector. 
	//Ideally, we would change these objects to support a default virtual deconstructor
	//delete(whiteBackground);
	//delete(whiteBottomBackground);
	om->DeleteButton(ClickHereToContinue);
}

void MainMenu::ClickHereToContinue_OnClick(m3dCI::Button* button)
{
	MenuHandler::getInstance()->TransitionTo(MenuHandler::MenuState::MinigameSelect);
}