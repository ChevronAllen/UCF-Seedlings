#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sstream>
#include <thread>
#include <chrono>

#include <3ds.h>
#include <m3dia.hpp>
#include <vector>
#include "lua/lua.hpp"

#include "util.hpp"
#include "ObjectManager.hpp"
#include "MenuHandler.hpp"
#include "sandbox.hpp"
#include "resources.h"
#include "gameManager.hpp"
#include "sceneManager.hpp"
#include "inputManager.hpp"
#include "commands/commands.h"

using namespace m3d;


int main(int argc, char* argv[])
{
	//  Create default Applet and Screen variables
    Applet app;
    Screen scr;

	//  Create default Singleton instances of Utility class and ObjectManager class
    GameManager::Initialize(&app, &scr);
	Util *util = Util::createInstance(&scr, &app);
	ObjectManager *om = ObjectManager::createInstance(&scr);
	MenuHandler *mh = MenuHandler::createInstance(&scr);
	ResourceManager::initialize();
    Input::initialize();
	SceneManager::OnInitialize();


	// Main loop
	while (app.isRunning())
	{
        if( m3d::buttons::buttonDown(m3d::buttons::Start) && m3d::buttons::buttonPressed(m3d::buttons::Select) ||
            m3d::buttons::buttonDown(m3d::buttons::Select) && m3d::buttons::buttonPressed(m3d::buttons::Start))
        {
            app.exit();
            //break;
        }

		//  Call OnUpdate Function for all Singletons.
        GameManager::Update();
        Input::update();
		om->OnUpdate();
		mh->OnUpdate();
		util->OnUpdate();
		SceneManager::OnUpdate();

		SceneManager::OnDraw();
        util->OnDraw();
		scr.render();
	}

	delete (util);
	delete (mh);
	delete (om);

	return 0;
}
