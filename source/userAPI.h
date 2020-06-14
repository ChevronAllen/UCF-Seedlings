#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <utility>

#include "lua/lua.hpp"


/**
 *  A namespace defining the functions bound to a Lua Sandbox
 *  Any function to become a user functions must be a C Closure, returning an int and accepting a lua_State*.
 *  enabled functions must be added to the enabledFunctions array manually
 */
namespace UserAPI
{
    /**
     *  User API functtion, prints a string to the console inserting a new-line after
     *  The function will convert a parameter on top of the stack into a string.
     *  called with one parameter.
     *  @param L lua state object
     *  @returns 0 on success, 1 if the stack is empty
     */
    int print_line(lua_State* L);  

    
}
