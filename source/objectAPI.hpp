#include <m3dia.hpp>
#include "lua/lua.hpp"

class objectAPI {
    public:

    // Our Object Instantiation methods are below:
    int rectangle(lua_State *L);
    int circle(lua_State *L);
    int triangle(lua_State *l);
    int text(lua_State *L);

    //Our Object Manipulation Methods are below:
    int up(lua_State *L);
    int down(lua_State *L);
    int left(lua_State *L);
    int right(lua_State *L);

    // Other object manipulation methods are below, these are more specific for the type of object we're passing. 
    


};