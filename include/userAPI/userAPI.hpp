/**
 *  @file userAPI.hpp
 *  @brief Define the UserAPI namespace
 */
#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <utility>
#include <string>
#include <sstream> 
#include <math.h>

#include <3ds.h>
#include <m3dia.hpp>

#include "lua/lua.hpp"
#include "util.hpp"   
#include "m3diaLibCI/text.hpp"
#include "sceneManager.hpp"
#include "gameObjects/objects.h"

#ifdef DEBUG
#define DEBUG_API
#endif

#define STEP_TIME 75 /// Used in intermediate API sleep functions to give the illusion of animation
#define STR_LEN 256 /// Maximum string length that can be read from the sandbox

/** 
 *  @namespace UserAPI
 *  @brief A namespace defining the functions bound to a Lua Sandbox
 * 
 *  Any function that becomes a UserAPI function must be a <a href="https://www.lua.org/manual/5.3/manual.html#lua_CFunction"> Lua C Closures </a>, 
 *  returning an int and accepting a single lua_State* parameter.\n
 *  Enabled functions must be added to the @ref enabledFunctions array manually.
 */
namespace UserAPI
{
    //========== Core API

    /** 
     *  @brief User API function, prints a string to the console inserting a new-line after
     * 
     *  The function will convert a parameter on top of the stack into a string.
     *  called with one parameter.
     *  @param L lua state object
     *  @returns 0 on success, 1 if the stack is empty
     */
    int print_line(lua_State* L);

    /**
     *  @brief prints a string to the console.
     * 
     *  The function will convert a parameter on top of the stack into a string.
     *  called with one parameter.
     *  @param L lua state object
     *  @returns 0 on success, 1 if the stack is empty
     */
    int print(lua_State* L);
    
    //========== Object API

    /**
     *  @brief Creates a rectange in the current scene
     * 
     *  Reads in two Lua parameters: x, y. These two values are passed to the RectangleObject Constructor
     *  @see RectangleObject
     *  @param L lua state object
     *  @returns 0 on success, 1 if the stack is empty
     */
    int make_rectangle(lua_State* L);  
    /**
     *  @brief Creates a circle in the current scene
     * 
     *  Reads in two Lua parameters: x, y. These two values are passed to the CircleObject Constructor
     *  @see RectangleObject
     *  @param L lua state object
     *  @returns 0 on success, 1 if the stack is empty
     */
    int make_circle(lua_State* L);  
    int make_text(lua_State* L);
    int make_paddle(lua_State* L); 
    int make_naught(lua_State* L);
    int make_cross(lua_State* L);

    /**
     *  @brief Moves an object within the current scene
     * 
     *  Reads in three Lua parameters: x, y, id. 
     *  Moves the gameobject associated with the id a number of units, relative to its current position. 
     *  Each step has a maximon absolute distance (1,1)
     *  @see STEP_TIME
     *  @warning Calls sleep(STEP_TIME) between each 'step'
     *  @param L lua state object
     *  @returns 0 on success, 1 on error.
     */
    int move_object(lua_State* L);
    
    /**
     *  @brief Sets the position of an object
     * 
     *  Reads in three Lua parameters: x, y, id. 
     *  Sets the position, relative to the screen origin, of the gameobject associated with the id.
     *  @param L lua state object
     *  @returns 0 on success, 1 on error.
     */   
    int set_position(lua_State* L);


    int set_x_position(lua_State* L);

    int set_y_position(lua_State* L);

    /**
     *  @brief Get an objects x-axis position
     * 
     *  Reads one Lua parameter (id), the scene id of the target gameobject.
     *  @param L lua state object
     *  @returns 0 on success, 1 on error.
     */   
    int get_x_position(lua_State* L);   

    /**
     *  @brief Get an objects y-axis position
     * 
     *  Reads one Lua parameter (id), the scene id of the target gameobject.
     *  @param L lua state object
     *  @returns 0 on success, 1 on error.
     */  
    int get_y_position(lua_State* L);   

    /**
     *  @brief Changes an object's angle relative to its current angle
     * 
     *  Reads one Lua parameter (id), the scene id of the target gameobject.
     *  @param L lua state object
     *  @returns 0 on success, 1 on error.
     */  
    int rotate(lua_State* L);    

    /**
     *  @brief Sets an object's angle.
     * 
     *  Reads two Lua parameters (id, angle). 
     *  id - the scene id of the target gameobject.
     *  angle - the new angle of the object.
     *  @param L lua state object
     *  @returns 0 on success, 1 on error.
     */  
    int set_angle(lua_State* L);

    /**
     *  @brief Gets an object's angle.
     * 
     *  Reads two Lua parameters (id). 
     *  **id** - the scene id of the target gameobject.
     *  @param L lua state object
     *  @returns 0 on success, 1 on error.
     */    
    int get_angle(lua_State* L);   

    /**
     *  @brief Sets object's scale.
     * 
     *  Reads two Lua parameters (id, x_scale, y_scale).\n 
     *  *id* - the scene id of the target gameobject.\n
     *  *x_scale* - the X component of the new scale.\n
     *  *y_scale* - the Y component of the new scale
     *  @param L lua state object
     *  @returns 0 on success, 1 on error.
     */ 
    int set_scale(lua_State* L);    

    /**
     *  @brief Gets the x-axis component of an objects current scale
     * 
     *  Reads one Lua parameter (id).\n 
     *  *id* - the scene id of the target gameobject.
     *  @param L lua state object
     *  @returns 0 on success, 1 on error.
     */ 
    int get_x_scale(lua_State* L);    

    /**
     *  @brief Gets the y-axis component of an objects current scale
     * 
     *  Reads one Lua parameter (id).\n 
     *  *id* - the scene id of the target gameobject.
     *  @param L lua state object
     *  @returns 0 on success, 1 on error.
     */ 
    int get_y_scale(lua_State* L);    
    
    /**
     *  @brief Sets an objects color
     * 
     *  Reads one Lua parameter (id).\n 
     *  *id* - the scene id of the target gameobject.
     *  @param L lua state object
     *  @returns 0 on success, 1 on error.
     */ 
    int set_color(lua_State* L);   

    /**
     *  @brief Sets the 'current_object' GameObject
     * 
     *  Reads one Lua parameter (id).\n 
     *  *id* - the scene id of the target gameobject.\n
     *  For use in the command system, commands automatically fill the id parameter of UserAPI 
     *  functions with the 'current_object' variable.
     *  @param L lua state object
     *  @returns 0 on success, 1 on error.
     */ 
    int select_object(lua_State* L);  

    /**
     *  @brief Deletes a GameObject
     * 
     *  Reads one Lua parameter (id).\n 
     *  *id* - the scene id of the target gameobject.\n
     *  Removes the specified object from the scene.  
     *  @param L lua state object
     *  @returns 0 on success, 1 on error.
     */ 
    int delete_object(lua_State* L);  

    //========== Hardware API

};