#include "ObjectManager.hpp"

using namespace m3d;

//Set default instance of this class to 0, to notify that the instance hasn't been created
ObjectManager *ObjectManager::instance = 0;

/*
	This Class is a singleton. 
	Meaning, only one instance of this class may ever exist.
	This allows for all classes to access this object through the use of this instance value.
	An initial instantiation must occur with proper values passed into createInstance
	All further attempts to accesss this class can use dummy values for all parameters of getInstance
*/
ObjectManager* ObjectManager::createInstance(Screen* screen)
{
	if (instance == 0)
	{
		instance = new ObjectManager(screen);
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
ObjectManager* ObjectManager::getInstance()
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
		
	And must handle:
		Button creation
*/
ObjectManager::ObjectManager(Screen* screen)
{
	scr = screen;
	
	lastFrameTouchX = -1;
	lastFrameTouchY = -1;
	
	util = Util::getInstance();
}

//Destructor: Objects that must be deleted when this object is deleted. Delete(nullptr) is fail-safe.
ObjectManager::~ObjectManager()
{

}

//The function which is called on every game frame.
void ObjectManager::OnUpdate()
{
	int touchedThisFrame = hidKeysDown() & KEY_TOUCH,
		touchReleasedThisFrame = hidKeysUp() & KEY_TOUCH,
		touchx = m3d::touch::getXPosition(),
		touchy = m3d::touch::getYPosition();

	std::vector<m3dCI::Button*> buttonsClone(buttons);
	std::vector<m3dCI::CodeEditor*> codeEditorsClone(codeEditors);
	std::vector<m3dCI::CommandLister*> commandListersClone(commandListers);

	for (unsigned int i = 0; i < codeEditorsClone.size(); i++)
	{
		if (codeEditorsClone[i] == nullptr)
			continue;

		//only fires if point is actually inside the code editor

		if (touchReleasedThisFrame && !Input::isTouchDragging() && !draggedLastFrame)
			codeEditorsClone[i]->SelectCommand(lastFrameTouchX, lastFrameTouchY);

		if (draggedLastFrame && touchReleasedThisFrame && codeEditorsClone[i]->isPointInside(lastFrameTouchX, lastFrameTouchY))
			codeEditorsClone[i]->DragComplete();

		if (Input::isTouchDragging())
		{
			int tX = Input::getTouchDragOrigin()->u;
			int tY = Input::getTouchDragOrigin()->v;

			if (codeEditorsClone[i]->isPointInside(tX, tY))
				codeEditorsClone[i]->DoDrag(Input::getTouchDragVector());
		}
	}

	if (touchReleasedThisFrame)
	{
		for (unsigned int i = 0; i < commandListersClone.size(); i++)
		{
			if (commandListersClone[i] == nullptr)
				continue;

			//only fires if point is actually inside the command lister
			commandListersClone[i]->SelectPoint(lastFrameTouchX, lastFrameTouchY);
		}
	}
	
	for (unsigned int i = 0; i < buttonsClone.size(); i++)
	{
		if (buttonsClone[i] == nullptr || !buttonsClone[i]->GetEnabledState())
			continue;

		//Check for touch event on Button
		if (touchedThisFrame)
		{
			if (buttonsClone[i]->OnTouch != nullptr && buttonsClone[i]->PointIntersects(touchx, touchy))
				(buttonsClone[i]->OnTouch)(buttonsClone[i]);
		}
		else if (touchReleasedThisFrame)
		{
			if (buttonsClone[i]->OnRelease != nullptr && buttonsClone[i]->PointIntersects(lastFrameTouchX, lastFrameTouchY))
				(buttonsClone[i]->OnRelease)(buttonsClone[i]);
		}
		else
		{
			if (buttonsClone[i]->OnHeld != nullptr && buttonsClone[i]->PointIntersects(touchx, touchy))
				(buttonsClone[i]->OnHeld)(buttonsClone[i]);
		}
	}
	
	lastFrameTouchX = touchx;
	lastFrameTouchY = touchy;

	draggedLastFrame = Input::isTouchDragging();
}

//Rectangle button creation. Adds button to array of active buttons.
m3dCI::Button* ObjectManager::CreateButton(int x, int y, int w, int h, m3d::Color color, m3d::Color borderColor, int borderWidth = 3)
{
	m3dCI::Button* newButton = new m3dCI::Button(x, y, w, h, color, borderColor, borderWidth);
	
	buttons.push_back(newButton);
	
	return newButton;
}

//Circular button creation. Adds button to array of active buttons.
m3dCI::Button* ObjectManager::CreateButton(int x, int y, int radius, m3d::Color color, m3d::Color borderColor, int borderWidth = 3)
{
	m3dCI::Button* newButton = new m3dCI::Button(x, y, radius, color, borderColor, borderWidth);
	
	buttons.push_back(newButton);
	
	return newButton;
}

//Circular button creation. Adds button to array of active buttons.
m3dCI::Button* ObjectManager::CreateButton(int x, int y, m3d::Texture& t_texture)
{
	m3dCI::Button* newButton = new m3dCI::Button(x, y, t_texture);

	buttons.push_back(newButton);

	return newButton;
}

//Circular button creation. Adds button to array of active buttons.
m3dCI::Button* ObjectManager::CreateButton(int x, int y, const std::string& t_spriteSheet, int t_imageId = 0)
{
	m3dCI::Button* newButton = new m3dCI::Button(x, y, t_spriteSheet, t_imageId);

	buttons.push_back(newButton);

	return newButton;
}

void ObjectManager::DeleteButton(m3dCI::Button* button)
{
	int index = -1;

	for (unsigned int i = 0; i < buttons.size(); i++)
		if (buttons[i] == button)
			index = i;

	if (index != -1)
	{
		delete(buttons[index]);
		buttons.erase(buttons.begin() + index);
	}
}

m3dCI::CodeEditor* ObjectManager::CreateCodeEditor(int x, int w, int borderWidth)
{
	m3dCI::CodeEditor* ce = new m3dCI::CodeEditor(x, w, borderWidth);

	codeEditors.push_back(ce);

	return ce;
}

void ObjectManager::DeleteCodeEditor(m3dCI::CodeEditor* ce)
{
	int index = -1;

	for (unsigned int i = 0; i < codeEditors.size(); i++)
		if (codeEditors[i] == ce)
			index = i;

	if (index != -1)
	{
		delete(codeEditors[index]);
		codeEditors.erase(codeEditors.begin() + index);
	}
}

m3dCI::CommandLister* ObjectManager::CreateCommandLister()
{
	m3dCI::CommandLister* cl = new m3dCI::CommandLister();

	commandListers.push_back(cl);

	return cl;
}

void ObjectManager::DeleteCommandLister(m3dCI::CommandLister* cl)
{
	int index = -1;

	for (unsigned int i = 0; i < commandListers.size(); i++)
		if (commandListers[i] == cl)
			index = i;

	if (index != -1)
	{
		delete(commandListers[index]);
		commandListers.erase(commandListers.begin() + index);
	}
}