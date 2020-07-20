/**
 *  @file coreAPI.cpp
 *  @brief Implementations for application related @ref UserAPI functions
 */
#include "../userAPI.hpp"


/**
 *  @brief Print line to console
 * 
 *  Prints a list of arguments to the console via @ref Util. 
 *  Implementation taken from Lua's own print function diverting output to Util::Print
 *  Accepts a variable number of Lua arguments, each evaluted as an expression
 */
int UserAPI::print_line(lua_State* L)
{   
    int n = lua_gettop(L);  /* number of arguments */
    int i;
    lua_getglobal(L, "tostring");
    for (i=1; i<=n; i++) {
        const char *s;
        size_t l;
        lua_pushvalue(L, -1);  /* function to be called */
        lua_pushvalue(L, i);   /* value to print */
        lua_call(L, 1, 1);
        s = lua_tolstring(L, -1, &l);  /* get result */
        
        if (s == NULL)
            return luaL_error(L, "'tostring' must return a string to 'print'");

        if (i>1) 
        {
            lua_writestring("\t", 1);
            std::cout << "    "; 
            Util::Print("    ");
        }   

        lua_writestring(s, l);
        std::cout << s ;
        Util::Print(s);
        lua_pop(L, 1);  /* pop result */
    }
    lua_writeline();
    std::cout << std::endl;
    Util::Print("\n");
    return 0;
}

/**
 *  @brief Print to console
 * 
 *  Prints a list of arguments to the console via @ref Util. 
 *  Implementation taken from Lua's own print function diverting output to Util::Print
 *  Accepts a variable number of Lua arguments, each evaluted as an expression
 */
int UserAPI::print(lua_State* L)
{    
    const char *s;
    size_t l;

    //   Convert evaluated parameter to string
    s = lua_tolstring(L, -1, &l);  
    if (s == NULL)
    {
        std::cerr << "'tostring' must return a string to 'print'";
        return 0;//luaL_error(L, "'tostring' must return a string to 'print'");
    }

    //  Write to Console
    //Util::Print(s);
    std::cout << s;

    // Number of results returned
    return 0; 
}  





