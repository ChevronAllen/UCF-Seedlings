#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <3ds.h>
#include <m3dia.hpp>
#include <png.h>
#include "lua/lua.hpp"

#include "util.hpp"
#include "ObjectManager.hpp"
#include "MenuHandler.hpp"
#include "sandbox.h"
#include "resources.h"

using namespace m3d;

int main(int argc, char* argv[])
{
	//  Create default Applet and Screen variables
    Applet app;
    Screen scr;
	m3d::Sprite spr;
    m3d::Texture * tex_ptr;
    std::string id = "gfx/error.png";

    //  Create a Sandbox environment (done here for testing)
	LuaSandbox* sandbox = new LuaSandbox();

	//  Create default Singleton instances of Utility class and ObjectManager class
	Util *util = Util::createInstance(&scr, &app);
	ObjectManager *om = ObjectManager::createInstance(&scr);
	MenuHandler *mh = MenuHandler::createInstance(&scr);
	ResourceManager::initialize();

    ResourceManager::loadTexture(id);  
    ResourceManager::loadFile("lua/init_scene.lua"); 
    
    tex_ptr = ResourceManager::getTexture(id);  

    spr.setTexture(*tex_ptr);
    spr.setXScale(10);
    spr.setYScale(10);
  
	// Main loop
	while (app.isRunning())
	{
		//  Call OnUpdate Function for all Singletons.
		util->OnUpdate();
		om->OnUpdate();
		mh->OnUpdate();
      
		scr.drawTop(spr); // draw the sprite 
    
        //  Render the game screen
		scr.render();
	}
	
    sandbox->close();
	
	delete (util);
	delete (om);
	delete (mh);
	
	return 0;
}
