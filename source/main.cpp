#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sstream>
#include <thread>
#include <chrono>
#include <random>

#include <3ds.h>
#include <m3dia.hpp>
#include <vector>
#include "lua/lua.hpp"

#include "util.hpp"
#include "sandbox.hpp"
#include "resourceManager.hpp"
#include "gameManager.hpp"
#include "sceneManager.hpp"
#include "inputManager.hpp"
#include "commands/commands.h"
#include "scenes/MainMenuScene.hpp"

using namespace m3d;

int main(int argc, char* argv[])
{
	//  Create default Applet and Screen variables
	Applet app;
	Screen scr;
    srand(time(0));
	//  Create default Singleton instances of Utility class and ObjectManager class
	GameManager::Initialize(&app, &scr);
	Util *util = Util::createInstance(&scr, &app);
	ResourceManager::initialize();
	Input::initialize();
	SceneManager::OnInitialize();
	SceneManager::setTransition(new MainMenuScene());

	// Main loop
	while (app.isRunning())
	{
		if (m3d::buttons::buttonDown(m3d::buttons::Start) && m3d::buttons::buttonPressed(m3d::buttons::Select) ||
			m3d::buttons::buttonDown(m3d::buttons::Select) && m3d::buttons::buttonPressed(m3d::buttons::Start))
		{
			app.exit();
			//break;
		}

		//  Call OnUpdate Function for all Singletons.
		GameManager::Update();
		Input::update();

		util->OnUpdate();
		SceneManager::OnUpdate();
		
		SceneManager::OnDraw();
		util->OnDraw();

		scr.render();
	}

	delete (util);

	return 0;
}