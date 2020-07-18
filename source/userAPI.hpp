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

#define STEP_TIME 150
#define STR_LEN 255

/** UserAPI
 *  A namespace defining the functions bound to a Lua Sandbox
 *  Any function to become a user functions must be a C Closure, returning an int and accepting a lua_State*.
 *  enabled functions must be added to the enabledFunctions array manually
 */
namespace UserAPI
{
    //========== Core API

 
 /** Print Line API Function
     *  @brief User API function, prints a string to the console inserting a new-line after
     *  The function will convert a parameter on top of the stack into a string.
     *  called with one parameter.
     *  @param L lua state object
     *  @returns 0 on success, 1 if the stack is empty
     */
    int print_line(lua_State* L);
    

    /**
     *  @brief prints a string to the console.
     *  The function will convert a parameter on top of the stack into a string.
     *  called with one parameter.
     *  @param L lua state object
     *  @returns 0 on success, 1 if the stack is empty
     */
    int print(lua_State* L);
    
    

    //========== Object API

    /**
     *  @brief Creates a rectange in the current scene
     *  Reads in two Lua parameters: x, y. These two values are passed to the RectangleObject Constructor
     *  @see RectangleObject
     *  @param L lua state object
     *  @returns 0 on success, 1 if the stack is empty
     */
    int make_rectangle(lua_State* L);  
    /**
     *  @brief Creates a circle in the current scene
     *  Reads in two Lua parameters: x, y. These two values are passed to the CircleObject Constructor
     *  @see RectangleObject
     *  @param L lua state object
     *  @returns 0 on success, 1 if the stack is empty
     */
    int make_circle(lua_State* L);  
    int make_text(lua_State* L);
    int make_paddle(lua_State* L); 

    /**
     *  @brief Moves an object within the current scene
     *  Reads in three Lua parameters: x, y, id. Moves the gameobject associated with the id a number of units, sleeping the current thread between each step
     *  @see STEP_TIME
     *  @param L lua state object
     *  @returns 0 on success, 1 on error.
     */
    int move_object(lua_State* L);   
    int set_position(lua_State* L);
    int get_x_position(lua_State* L);   
    int get_y_position(lua_State* L);   

    int rotate(lua_State* L);    
    int set_angle(lua_State* L);    
    int get_angle(lua_State* L);   

    int scale(lua_State* L);    
    int set_scale(lua_State* L);    
    int get_x_scale(lua_State* L);    
    int get_y_scale(lua_State* L);    
      
    int set_color(lua_State* L);   
    
    int delete_object(lua_State* L);  
    int change_color(lua_State* L);

    //========== Hardware API


}
/*
---- Control Statements
SELECT [obj_name] -> 
IF [bool_expression] 
    -> if [bool_expression] then
LOOP [int] 
    -> while [int] > 0 do
WHILE [bool_expression] -> while [bool_expression] do
END    -> end
LABEL [label_name]
GOTO [label_name]

---- Object Manipulation
LEFT, RIGHT, UP, DOWN [double]
    -> apifunction([double],[double])
RED, BLUE, GREEN, YELLOW, ORANGE, PURPLE
    -> apifunction([color])
SCALE [x] [y], SCALE_X [x], SCALE_Y [y]
    -> apifuntion([x],[y])
ROTATE [double] 
    -> apifunction([double] , false) 
ANGLE [double] 
    -> apifunction([double] , true) 

CIRCLE [obj_name] 
RECTANGLE [obj_name]
TRIANGLE [obj_name]
PADDLE, etc [obj_name]
    -> apifunction([obj_name]) 

DELETE [obj_name]

---- Variables
VAR [var_name] [value] 
    -> [var_name] = [value]
DELETE_VAR [var_name]
    -> [var_name] = nil

---- OTHER
GET_X, GET_Y [var_name] 
GET_ANGLE [var_name]
* GET_SPEED_X, GET_SPEED_Y [var_name]

*/