#pragma once
#include "scenes/scene.hpp"
#include "scenes/minigame.hpp"

#include "commands/commands.h"

/**
	@brief Manager of:
	- Active Scene
	- Scene transitions
	- Drawing of Scenes
**/
class SceneManager
{
private:
	///@brief The scene to be transitioned to
    static Scene* m_nextScene;
	
	///@brief The current scene
    static Scene* m_currentScene;

	///@brief Function used to create a one frame buffer between scene changes
	static void finishTransition();
public:
	/**
		@brief Get the currently running Scene
		@returns The currently running scene
	**/
    static Scene* getScene();
	
	/**
		@brief Set the scene to transition to next frame
		@param t_next The scene to transition to
	**/
    static void setTransition(Scene*);

	/**
		@brief Initialize the values needed by the SceneManger
	**/
    static void OnInitialize();
	
	/**
		@brief Update all pieces of the running Scene during a game frame
	**/
    static void OnUpdate();
	
	/**
		@brief Draw all pieces of the running Scene during a game frame
	**/
    static void OnDraw();

	/**
		@brief Add a command to the currently selected minigame
		NOTE: Doing it this way is HORRBIBLE. 
		This is leftover code from the transition from ObjectManager to SceneManager.
		This should be handled by each specific Minigame via a callback function
		@param command Command to add to the Minigames CodeEditor
	**/
	static void AddCommand(CommandObject *command);
	
	/**
		@brief Populate the CodeEditor with a beginning list of commands and set the function to be called when the Submit button is called
		NOTE: Doing it this way is HORRBIBLE. 
		This is leftover code from the transition from ObjectManager to SceneManager.
		This should be handled by each specific Minigame via a callback function
		@param commands The default list of commands to show
		@param callbackFunction The function to call when the Submit/Run button is called.
	**/
	static void RequestUserCode(std::vector<CommandObject*> commands, std::function<void(std::vector<CommandObject*>)> callbackFunction);
};
