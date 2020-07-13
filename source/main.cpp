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
#include "sandbox.h"
#include "resources.h"
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

	//  Create default Singleton instances of Utility class and ObjectManager class
	GameManager::Initialize(&app, &scr);
	Util *util = Util::createInstance(&scr, &app);
	ResourceManager::initialize();
	Input::initialize();
	SceneManager::OnInitialize();
	SceneManager::setTransition(new MainMenuScene());

	Input::AudioData ad;

	// Main loop
	while (app.isRunning())
	{
		if (m3d::buttons::buttonDown(m3d::buttons::Start) && m3d::buttons::buttonPressed(m3d::buttons::Select) ||
			m3d::buttons::buttonDown(m3d::buttons::Select) && m3d::buttons::buttonPressed(m3d::buttons::Start))
		{
			app.exit();
			//break;
		}

		if (m3d::buttons::buttonPressed(m3d::buttons::X) && !Input::isMicRecording())
				Util::PrintLine("Mic start: " + std::to_string(Input::recordMic()));

		if (m3d::buttons::buttonReleased(m3d::buttons::X) && Input::isMicRecording())
		{
			ad = Input::stopMicRecording();
			Util::PrintLine("Mic stop: " + std::to_string(ad.buffer == nullptr?0:1));
		}

		if (m3d::buttons::buttonPressed(m3d::buttons::Y))
			if (Input::reachedEndOfPlayback())
				Util::PrintLine("Playback: " + std::to_string(Input::playAudio(ad)));

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