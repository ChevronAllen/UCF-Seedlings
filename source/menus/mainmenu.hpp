#pragma once

#include "menu.hpp"

class MainMenu : public Menu
{
	private:
		m3d::Rectangle* whiteTopBackground;
		m3d::Rectangle* whiteBottomBackground;

		m3dCI::Text* StartupText;
		m3dCI::Button* ClickHereToContinue;

		static void ClickHereToContinue_OnClick(m3dCI::Button* button);
	public:
		MainMenu(m3d::Screen* screen);
		virtual ~MainMenu();
		
		void OnUpdate();
};