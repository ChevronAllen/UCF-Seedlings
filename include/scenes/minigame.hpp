/**
 *  @file minigame.hpp
 *  @brief Defines the Minigame class
 * 
 *  Minigames are a type of Scene with shared logic
 */
#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sstream>

#include <m3dia.hpp>

#include "core.h"
#include "scenes/scene.hpp"
#include "sandbox.hpp"

#ifdef DEBUG
#define DEBUG_MINIGAME
#endif

#define GRID_SIZE 20

/**
 *  @def setObjectName
 *  @brief Give an object a user accessible name within the Lua Environment.
 * 
 *   
 *  Given a name string literal and the id of a GameObject. 
 *  Executes some Lua code which will allow the user to manipulate that object with the UserAPI.
 *  @note Executes using the Lua Queue, so there may be a delay if other code is being executed.
 *  @param name [string] 
 *  @param id [int]
 */
#define setObjectName(name, id) m_sandbox->executeStringQueued("name_table[\"" name "\"] = " + std::to_string(id))

/**
 *  @class Minigame "/scenes/minigame.hpp"
 *  @brief Astract Minigame Class
 *  
 *  Defines the default behavior of Minigame type scenes
 */
class Minigame : public Scene
{
private:
	std::function<void(std::vector<CommandObject*>)> submitFunction = nullptr;

    SpriteMenuItem* m_gridOverlay = nullptr;

	enum DisplayState
	{
		CodeEditor,
		CommandLister,
		CommandEditor,
		CommandEditorCommandLister,
		null
	};

	DisplayState dState = CodeEditor, nextState = null;

protected:
	/**
		@brief MenuItems
	**/
	ButtonMenuItem  *AddButton = nullptr,
		*EditButton = nullptr,
		*RemoveButton = nullptr,
		*closeButton = nullptr,
		*submitButton = nullptr;
	CodeEditorMenuItem* codeEditor = nullptr;
	CommandEditorMenuItem* commandEditor = nullptr;

	bool isExecuting = false,
		showGridLines = true,
		blockButtons = false;

	/**
		@brief CommandLister is responsible for showing all objects which can be added to the CodeEditor.
	**/
	CommandListerMenuItem* commandLister = nullptr;

    /**
     *  @brief Sandbox environment
     * 
     *  Each minigame needs a sandbox environment. This is initialized and destroyed along with the Minigame.
     *  The minigame itself may affect its execution.
     */
    LuaSandbox* m_sandbox;

    /**
     *  @brief Win Condition State
     * 
     *  Used to track when a win condition for the game has been met.
     */
	static bool winCond;

	/**
	 *  @brief Function called before a sandbox execution
     * 
	 *  onExecutionBegin is called right before the sandbox executes a chunk
	 */
	virtual void onExecutionBegin();

	/**
	 *  @brief Function called before a sandbox execution
     * 
	 *  onExecutionEnd is called right after the sandbox executes a chunk.
	 */
	virtual void onExecutionEnd();

	/**
	 *  @brief Set the next transition to go to
	 */
	void SetTransitionToDisplayState(DisplayState state);

	/**
	 *  @brief Complete the transition
	 */
	void FinishTransitionToDisplayState();

public:

    /**
     *  @brief Toggle the win condition
     * 
     *  Inverts the value of @ref winCond
     */
	void toggleWinCond();

	/**
	 *  @brief Default Constructor, should be inherited by child class constructors
	 */
	Minigame();

	/**
	 *  @brief Default Destructor, should be inherited by child class destructor
	 */
	virtual ~Minigame();
	
	/**
		@brief Function which allows for adding commands to the CodeEditor window.
		@param command CommandObject to add to the CodeEditor
	**/
	void AddCommand(CommandObject* command);
	
	/**
		@brief Function which allows for adding several commands to the code editor at the very beginning. 
		Called by SceneManager::RequestUserCode().
		@param list List of CommandObject*s to add to the CodeEditor 
	**/
	void AddStartCommands(std::vector<CommandObject*> list);
	
	/**
		@brief Function to clear all Commands currently inside the CodeEditor
	**/
	void ClearCommands();

	/**
		@brief Function to set the function which is called when Run/Submit is called.
		@param callbackFunction The function which is called on Run/Submit. It will pass back a list of CommandObjects
	**/
	void SetSubmitFunction(std::function<void(std::vector<CommandObject*>)> callbackFunction);

	/**
		@brief Function containing the set of actions needed to happen when the Add Button gets clicked.
	**/
	void AddButton_OnClick();
	/**
		@brief Function containing the set of actions needed to happen when the Edit Button gets clicked.
	**/
	void EditButton_OnClick();
	/**
		@brief Function containing the set of actions needed to happen when the Delete Button gets clicked.
	**/
	void DeleteButton_OnClick();
	/**
		@brief Function containing the set of actions needed to happen when the Submit Button gets clicked.
	**/
	void SubmitButton_OnClick();
	/**
		@brief Function containing the set of actions needed to happen when the Close Button gets clicked.
	**/
	void CloseButton_OnClick();

	/**
		@brief Virtual Function responsible for determining if the Win Condition was met.
	**/
	virtual bool checkWinCond() {};
	
	/**
		@brief Virtual Function responsible for loading the Scene
	**/
	virtual void loadScene() {};
	
	/**
		@brief Virtual Function responsible for loading objects nessecary for the Win Screen
	**/
	virtual void loadWinScr() {};
	
	/**
		@brief Virtual Function responsible for loading objects nessecary for the Lose Screen
	**/
	virtual void loadLoseScr() {};
	
	/**
		@brief Virtual Function responsible for requesting specific UI Elements
	**/
	virtual void requestUI() {};
	
	/**
		@brief Virtual Function responsible for properly closing out of the Minigame
	**/
	virtual void closeGame() {};
	
	/**
		@brief Virtual Function responsible for the initialization of the minigame
	**/
	virtual void initialize();
	
	/**
		@brief Virtual Function responsible for loading objects. 
		Useful later for loading save states.
	**/
	virtual void load() {};
	
	/**
		@brief Virtual Function responsible for unloading objects. 
		Useful later for storing a save state.
	**/
	virtual void unload() {};
	
	/**
		@brief Virtual Function responsible for updating objects. 
		This is called each game frame.
	**/
	virtual void update();
	
	/**
		@brief Virtual Function responsible for drawing each object.
		This is called each game frame.
	**/
	virtual void draw();
	
	/**
		@brief Virtual Function responsible for setting initial values. 
		(Redundant with Initialize?).
	**/
	virtual void onEnter() {};
	
	/**
		@brief Virtual Function responsible for deleting objects created via OnEnter. 
		(Redundant with closeGame?).
	**/
	virtual void onExit() {};
};
