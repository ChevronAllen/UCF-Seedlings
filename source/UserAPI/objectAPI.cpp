#include <m3dia.hpp>

#include "../objectAPI.hpp"
#include "../util.hpp"   
#include "../m3diaLibCI/text.hpp"

const int DEF_HEIGHT = 10;
const int DEF_WIDTH = 10;
const int DEF_RADIUS = 10; 
const m3d::Color DEF_COLOR(100,0,0);

int objectAPI::rectangle(lua_State *L) 
{
    lua_Number luaXpos, luaYpos;
    int xpos, ypos;
    if (lua_isnumber(L,-1) && lua_isnumber(L,-2))
    {
        luaXpos = lua_tonumber(L, -1);
        luaYpos = lua_tonumber(L, -2);

        xpos = (int)luaXpos;
        ypos = (int)luaYpos;

        m3d::Rectangle *newRec = new m3d::Rectangle(xpos,ypos,DEF_HEIGHT,DEF_WIDTH,DEF_COLOR);

        /* TODO: How to identify and link these to the GameObject class?? 
        We need a unique identifier to help us link this object to the new object created.
        Also: include GameObject Class. Discuss with team. */

        return(0);
    }
    
    else
    {
        return luaL_error(L,"int needs to be entered in order to execute");
    }
}

int objectAPI::circle(lua_State *L) 
{
    lua_Number luaXpos, luaYpos;
    int xpos, ypos;
    if (lua_isnumber(L,-1) && lua_isnumber(L,-2))
    {
        luaXpos = lua_tonumber(L, -1);
        luaYpos = lua_tonumber(L, -2);

        xpos = (int)luaXpos;
        ypos = (int)luaYpos;

       m3d::Circle *newCir = new m3d::Circle(xpos,ypos,DEF_RADIUS,DEF_COLOR);

        /* TODO: How to identify and link these to the GameObject class?? 
        We need a unique identifier to help us link this object to the new object created.
        Also: include GameObject Class. Discuss with team. */

        return(0);
    }
    
    else
    {
        return luaL_error(L,"int needs to be entered in order to execute");
    }
}

int objectAPI::triangle(lua_State *L) 
{
    lua_Number luaXpos, luaYpos;
    int xpos, ypos;
    if (lua_isnumber(L,-1) && lua_isnumber(L,-2))
    {
        luaXpos = lua_tonumber(L, -1);
        luaYpos = lua_tonumber(L, -2);

        xpos = (int)luaXpos;
        ypos = (int)luaYpos;

       m3d::Triangle *newTri = new m3d::Triangle(xpos,ypos,xpos-1,ypos-1,xpos+1,ypos+1,DEF_COLOR);

        /* TODO: How to identify and link these to the GameObject class?? 
        We need a unique identifier to help us link this object to the new object created.
        Also: include GameObject Class. Discuss with team. */

        return(0);
    }
    
    else
    {
        return luaL_error(L,"int needs to be entered in order to execute");
    }
}

int objectAPI::text(lua_State *L) 
{
    lua_Number luaXpos, luaYpos;
    int xpos, ypos;

    if (lua_isnumber(L,-1) && lua_isnumber(L,-2) && lua_isstring(L,-3))
    {
        luaXpos = lua_tonumber(L, -1);
        luaYpos = lua_tonumber(L, -2);

        xpos = (int)luaXpos;
        ypos = (int)luaYpos;

        const char *s;
        size_t len;

        s = lua_tolstring(L,-3,&len);

       m3dCI::Text *newText = new m3dCI::Text(s,DEF_COLOR);
       newText->setXPosition(xpos);
       newText->setYPosition(ypos);

        /* TODO: How to identify and link these to the GameObject class?? 
        We need a unique identifier to help us link this object to the new object created.
        Also: include GameObject Class. Discuss with team. */

        return(0);
    }

    else
    {
        return luaL_error(L,"'int,int,string' needs to be entered in order to execute");
    }

}

int objectAPI::up(lua_State *L) 
{
    lua_Number luaXchange, luaID;
    int xchange, id;

    if (lua_isnumber(L,-1) && lua_isnumber(L,-2))
    {
        luaID = lua_tonumber(L,-1);
        luaXchange = lua_tonumber(L,-2);

        id = (int)luaID;
        xchange = (int)luaXchange;

        /* TODO: Discuss how to connect GameObject class with userAPI to look for Object.
        */

        /*
       m3d::Drawable *object; 

       if (m3d::Rectangle *shape = dynamic_cast<m3d::Rectangle*>(object))
       {
           shape->setXPosition(shape->getXPosition() + xchange);
       }

       else if (m3d::Circle *shape = dynamic_cast<m3d::Circle*>(object))
       {
           shape->setXPosition(shape->getXPosition() + xchange);
       }

       else if (m3d::Triangle *shape = dynamic_cast<m3d::Triangle*>(object))
       {
           shape->setX1Pos(shape->getX1Pos() + xchange);
           shape->setX2Pos(shape->getX2Pos() + xchange);
           shape->setX3Pos(shape->getX3Pos() + xchange);
       }

       else if(m3d::Text *shape = dynamic_cast<m3d::Text*>(object))
       {
           shape->setXPosition(shape->getXPosition() + xchange);
       }

       */
    }
    
}       