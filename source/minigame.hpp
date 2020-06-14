#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <m3dia.hpp>

using namespace m3d;

class Minigame
{
	private:
		m3d::Screen* scr;
		m3d::Applet* app;
		bool winState;
	

	public:
		void start();
		void update();
		bool checkWinState();
		void loadSetting();
		void loadWinScreen();
		void loadLoseScreen();
		void requestUserInput();
		void closeGame();
	
	

};





