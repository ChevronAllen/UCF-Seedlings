#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <map>
#include <memory>

#include "../gameObject.hpp"
#include "../sandbox.hpp"
#include "../util.hpp"
#include "../Menu/Menu.hpp"

/**	
 *  @class Scene "scenes/scene.hpp"
 *  @brief Scene Abstract Class
 * 
 *  Used to encapsulate multiple game objects and Unique logic. 
 *  By organising game states into scenes we can process them individually and handle transitions  
*/
class Scene : public Updateable
{

protected:
    /**
     *  @brief hash map of GameObjects indexed by an insigned integer
     */
    std::map<unsigned int, GameObject*> m_hashmap;

    /// @brief counter used to track number of objects in m_hashmap
    unsigned int m_idCounter;
    
    /// @brief name of the scene, used as an identifier
    std::string m_name;

    /// @brief internal menu object
	Menu* menu;
public:

	/**
     *  @brief Default Constructor for Scene.
     *  @note Must be inherited by child classes
	*/
    Scene()
    {
        // Initialize an empty object list
        m_hashmap.empty();
        // Set the id counter 
        m_idCounter = 0;

		menu = new Menu();
    }
	
	/**
     *  @brief Deconstructor for Scene.
     * 
     *  Destroy all GameObjects within the to Scene
	*/
    virtual ~Scene()
    {
        // Iterates through the hashmap calling each items GameObject::destroy() 
        auto it =  m_hashmap.cbegin();
        for(;it != m_hashmap.cend(); it++)
        {
            it->second->destroy();
        }

        //  Calls the default destructor of the menu
		delete(menu);
    }

	/**
     *  @brief Initialization of values of all MenuItems.
     *  
     *  Called by @ref SceneManager once during transition
	*/
    virtual void initialize()=0;
	
	/**
     *  @brief Load Scene Data
     * 
     *  Called by @ref SceneManager once during transition
    */
    virtual void load()=0;
	
	/**	
     *  @brief Unload Scene Data
     * 
     *  Called by @ref SceneManager once during transition
    */
    virtual void unload()=0; 
	
	/**
     *  @brief Update the Scene's logic
     * 
     *  Called by @ref SceneManager::OnUpdate() once per game loop
	*/
    virtual void update()=0;
	
	/**
     *  @brief Draw the Scene
     *  
     *  Called by @ref SceneManager::OnDraw() once per game loop
	*/
    virtual void draw()
    {
        for (auto objPair : m_hashmap)
        {
            if (objPair.second != nullptr)
            {
                objPair.second->draw(); 
            }
        }
        
    }

	/**
     *  @brief Called when Scene is first created
	*/
    virtual void onEnter()=0;

	/**
     *  @brief Called before a Scene is destroyed
	*/
    virtual void onExit()=0;

	/**
     *  @brief Returns the name of the Scene.
     *  
     *  @return value of @ref m_name
	*/
    std::string getSceneName()
    {
        return m_name;
    }

	/** @brief Find a game object by it's hashmap ID 
     *  
     *  @param t_id hashmap id of the Object to find
     *  @return pointer to the GameObject, if no object found returns NULL
	*/
    GameObject* findObject(int t_id)
    {
        return m_hashmap[t_id];
    }

	/**
     *  @brief Add an object to the scene
     * 
     *  @param obj GameObject to add to the scene
	*/
    unsigned int addObject(GameObject* obj)
    {
        m_hashmap[m_idCounter] = obj;
        return m_idCounter++;
    }

	/**
     *  @brief Remove an object from the scene
     *  
     *  @param t_id ID of the object to be removed
	**/
    void removeObject(unsigned int t_id)
    {
        m_hashmap[t_id] = NULL;
    }
};
