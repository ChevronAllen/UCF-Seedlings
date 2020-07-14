/**
 *  @file minigame.hpp
 *  @brief Defines the minigame inherited class
 */
#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <m3dia.hpp>
#include <sstream>

#include "../util.hpp"
#include "../gameManager.hpp"
#include "../inputManager.hpp"
#include "../sceneManager.hpp"
#include "../resources.h"
#include "../scenes/scene.hpp"
#include "../sandbox.hpp"
#include "../modules/modules.h"


#ifdef DEBUG
#define DEBUG_THREAD
#endif




#define setObjectName(name, id) m_sandbox->executeStringQueued("name_table[\"" name "\"] = " + std::to_string(id))

class Minigame : public Scene
{
private:
	ButtonMenuItem  *AddButton = nullptr,
                    *EditButton = nullptr,
                    *RemoveButton = nullptr,
                    *closeButton = nullptr,
                    *submitButton = nullptr;
	CodeEditorMenuItem* codeEditor = nullptr;
	CommandListerMenuItem* commandLister = nullptr;
	CommandEditorMenuItem* commandEditor = nullptr;

	std::function<void(std::vector<CommandObject*>)> submitFunction = nullptr;

	bool showCommandLister = false, showCommandEditor = false;

protected:
    LuaSandbox* m_sandbox;
	static bool winCond;

    

	/**
	 *  @brief Function called before a sandbox execution
	 *  onExecutionBegin is called right before the sandbox executes a chunk
	 */
	virtual void onExecutionBegin(){}

	/**
	 *  @brief Function called before a sandbox execution
	 *  onExecutionEnd is called right after the sandbox executes a chunk.
	 */
	virtual void onExecutionEnd(){}

public:
	void toggleWinCond();

	/**
	 *  @brief Default Constructor, should be inherited by child class constructors
	 */

	Minigame();
	/**
	 *  @brief Default Destructor, should be inherited by child class destructor
	 */
	virtual ~Minigame();

	void AddCommand(CommandObject* command);
	void AddStartCommands(std::vector<CommandObject*> obj);
	void ClearCommands();

	void SetSubmitFunction(std::function<void(std::vector<CommandObject*>)> callbackFunction);

	void AddButton_OnClick();
	void EditButton_OnClick();
	void DeleteButton_OnClick();
	void SubmitButton_OnClick();
	void CloseButton_OnClick();

	virtual bool checkWinCond() {};


	virtual void loadScene() {};
	virtual void loadWinScr() {};
	virtual void loadLoseScr() {};
	virtual void requestUI() {};
	virtual void closeGame() {};

	virtual void initialize() {};
	virtual void load() {};
	virtual void unload() {};
	virtual void update();
	virtual void draw() {};

	virtual void onEnter() {};
	virtual void onExit() {};
};
