#pragma once

#include "menu.hpp"

#define MinigameCount 6
#define Rows 2
#define Columns 3

class MinigameSelect : public Menu
{
	private:

		m3d::Rectangle* whiteBackground;

		m3dCI::Text* MinigameSelectTopText;
		m3dCI::Button* minigameOptions[MinigameCount];

		static void TransitionToMinigameTemplate(m3dCI::Button* b);
	public:
		MinigameSelect(m3d::Screen* screen);
		virtual ~MinigameSelect();

		static void SelectFirstMinigame(m3dCI::Button* button);
		
		void OnUpdate();
};