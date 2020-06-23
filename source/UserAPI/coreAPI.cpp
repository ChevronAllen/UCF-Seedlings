
#include "../userAPI.h"
#include "../util.hpp" 

/**
 *  User API print function
 */
int UserAPI::print_line(lua_State* L)
{    
    const char *s;
    size_t l;

    //   Convert evaluated parameter to string
    s = lua_tolstring(L, -1, &l);  
    if (s == NULL)
    {
        Util::getInstance()->PrintLine("'tostring' must return a string to 'print'");
        return luaL_error(L, "'tostring' must return a string to 'print'");
    }

    //  Write to Console
    Util::getInstance()->PrintLine(s);

    // Number of results returned
    return 0; 
}