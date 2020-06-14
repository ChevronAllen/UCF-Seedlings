#include "util.hpp"

using namespace m3d;

Util *Util::instance = 0;

/*
	This Class is a singleton. 
	Meaning, only one instance of this class may ever exist.
	This allows for all classes to access this object through the use of an instance value.
	An initial instantiation must occur with proper values passed into createInstance
	All further attempts to accesss this class can use dummy values for all parameters of getInstance
*/
Util* Util::createInstance(Screen* screen, Applet* applet)
{
	if (instance == 0)
	{
		instance = new Util(screen, applet);
	}
	
	return instance;
}

/*
	This Class is a singleton. 
	Meaning, only one instance of this class may ever exist.
	This allows for all classes to access this object through the use of this instance value.
	An initial instantiation must occur with proper values passed into createInstance
	All further attempts to accesss this class can use dummy values for all parameters of getInstance
*/
Util* Util::getInstance()
{
	if (instance == 0)
	{
		return nullptr;
	}
	
	return instance;
}

//Initialize the Util class.
//Only ever called once.
/*
	This class requires an existing:
		Screen
		Applet
		
	And must handle:
		Console
*/
Util::Util(Screen* screen, Applet* applet)
{
	scr = screen;
	app = applet;
	
	console = new m3dCI::Console("Press A or B to write some text.");
}

//Destructor: Objects that must be deleted when this object is deleted. Delete(nullptr) is fail-safe.
Util::~Util()
{
	delete(console);
}

//The function which is called on every game frame.
void Util::OnUpdate()
{	
	//Check for force close button presses, Close if successful
	if (buttonDown(buttons::Button::Start)
		&& buttonDown(buttons::Button::Select))
		this->app->exit();
	
	//Check for Console Opening button presses, Open console if successful
	if (buttonPressed(buttons::Button::L)
		&& buttonPressed(buttons::Button::R))
		this->console->ToggleState();
	
	//Console specific actions, Only works when console is on screen
	if(IsConsoleDrawn())
	{
		//Write some text
		if (buttonPressed(buttons::Button::A))
			this->Print("Some Text.");
		
		//Write some text on a new line
		if (buttonPressed(buttons::Button::B))
			this->PrintLine("Some Text.");
	
		//Draw the console
		scr->drawTop(*console, RenderContext::Mode::Flat);
	}
}

void Util::drawTop(Drawable& obj, RenderContext::Mode mode = RenderContext::Mode::Flat, int layer = 0)
{
	getInstance();
	if (instance != 0)
		instance->scr->drawTop(obj, mode, layer);
}

void Util::drawBottom(Drawable& obj, RenderContext::Mode mode = RenderContext::Mode::Flat, int layer = 0)
{
	getInstance();
	if (instance != 0)
		instance->scr->drawBottom(obj, mode, layer);
}

//Print some text followed by a new line to the primary console.
void Util::PrintLine(std::string text)
{
	getInstance();
	if (instance != 0)
		instance->console->println(text);
}

//Print some text to the primary console.
void Util::Print(std::string text)
{
	getInstance();
	if (instance != 0)
		instance->console->print(text);
}

bool Util::IsConsoleDrawn()
{
	getInstance();
	if (instance != 0)
		return instance->console->isDrawn();

	return false;
}