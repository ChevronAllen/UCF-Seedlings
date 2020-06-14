#include "minigameSelect.hpp"

MinigameSelect::MinigameSelect(m3d::Screen* screen) :
	Menu(screen)
{
	MinigameSelectTopText = new m3dCI::Text("Select a minigame");
	MinigameSelectTopText->setFontSize(1);
	MinigameSelectTopText->setFontWeight(1);
	MinigameSelectTopText->setColor(m3d::Color(0, 0, 0));

	int width = MinigameSelectTopText->getWidth();
	int height = MinigameSelectTopText->getHeight();
	
	int topScreenWidth = screen->getScreenWidth(m3d::RenderContext::ScreenTarget::Top);
	int bottomScreenWidth = screen->getScreenWidth(m3d::RenderContext::ScreenTarget::Bottom);
	int screenHeight = screen->getScreenHeight();

	MinigameSelectTopText->setPosition((topScreenWidth / 2) - (width / 2), (screenHeight / 2) - (height / 2));

	whiteTopBackground = new m3d::Rectangle(0, 0, 1000, 1000, m3d::Color(255, 255, 255));
	whiteBottomBackground = new m3d::Rectangle(0, 0, 1000, 1000, m3d::Color(255, 255, 255));

	int ButtonWidth = 50;
	int ButtonHeight = 50;

	int rows = 2;
	int columns = 3;

	int rowPadding = ((screenHeight * 0.25) * rows - (ButtonHeight * rows)) / (rows - 1);
	int columnPadding = ((bottomScreenWidth * 0.25) * columns - (ButtonWidth * columns)) / (columns - 1);//45

	for (int row = 0; row < rows; row++)
	{
		for (int column = 0; column < columns; column++)
		{
			int x = (bottomScreenWidth * 0.25) / 2 + (columnPadding * column) + (ButtonWidth * column),
				y = (screenHeight * 0.25) + (rowPadding * row) + (ButtonHeight * row),
				w = ButtonWidth,
				h = ButtonHeight;

			minigameOptions[column + (row * columns)] = new m3dCI::Button(x, y, w, h, m3d::Color(255, 255, 255), m3d::Color(0, 0, 0), 3);
		}
	}
}

void MinigameSelect::OnUpdate()
{
	if(!util->IsConsoleDrawn())
	{
		scr->drawTop(*whiteTopBackground, RenderContext::Mode::Flat);
		scr->drawBottom(*whiteBottomBackground, RenderContext::Mode::Flat);
		scr->drawTop(*MinigameSelectTopText, RenderContext::Mode::Flat);

		for(int i = 0; i < 6; i++)
			scr->drawBottom(*minigameOptions[i], RenderContext::Mode::Flat);
	}
}

MinigameSelect::~MinigameSelect()
{
	delete(MinigameSelectTopText);
}