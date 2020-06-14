#pragma once

#include "menu.hpp"

class MinigameSelect : public Menu
{
	private:
		m3d::Rectangle* whiteTopBackground;
		m3d::Rectangle* whiteBottomBackground;

		m3dCI::Text* MinigameSelectTopText;
		m3dCI::Button* minigameOptions[6];
	public:
		MinigameSelect(m3d::Screen* screen);
		virtual ~MinigameSelect();
		
		void OnUpdate();
};