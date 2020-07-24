/**
 *  @file objectAPI.cpp
 *  @brief Implementations for @ref GameObject related @ref UserAPI functions
 */
#include "../userAPI.hpp"


int UserAPI::move_object(lua_State* L)
{
    int t_id = lua_tonumber(L,-3); 
    int x = lua_tonumber(L,-2); 
    int y = lua_tonumber(L,-1);
    
    
    Scene* scene = SceneManager::getScene();

    if(scene == nullptr)
    {
        Util::PrintLine("Error: no current scene");
        return 0;
    }
    GameObject* obj = scene->findObject(t_id);
    if(obj == nullptr)
    {
        Util::PrintLine("Error: couldnt find object \'" + std::to_string(t_id) +"\' in Scene \'" + scene->getSceneName() + "\'");
        return 0;
    }
    
    #ifdef DEBUG_API
    Util::PrintLine("move [" + std::to_string(t_id) + "] - x:" +  std::to_string(x) + ", y:" +  std::to_string(y) );
    #endif

    int t_runState;
    // while there are steps left
    while(!(x == 0 && y == 0))
    {

        #ifdef DEBUG_API
            Util::PrintLine("state: " + std::to_string(t_runState) );
        #endif

        //  check the threadState for a halt
        do{
            lua_getglobal(L,"_EXEC_STATE");
            if(!lua_isnoneornil(L,-1))
            {  
                t_runState = lua_tonumber(L,-1);
                lua_remove(L,-1);                
                if(t_runState < 0)
                {
                    return 0;
                }
            }
            
        }while(t_runState == 1);

        if(t_runState == THREAD_SKIP || t_runState == THREAD_CLOSE || t_runState == THREAD_CLEAR)
        {
            return 0;
        } 

        obj->moveTo( sign(x), sign(y));

        // Adjust remaining steps
        x = x - sign(x);
        y = y - sign(y);
        
        #ifdef DEBUG_API
        Util::PrintLine("step [" + std::to_string(t_id) + "]. x: " +  std::to_string(sign(x)) + ", y: " +  std::to_string(sign(x)) );
        #endif
        
        m3d::Thread::sleep(STEP_TIME);
    }
    

    return 0;
}

int UserAPI::make_rectangle(lua_State* L)
{
    lua_Number x = lua_tonumber(L,-2);
    lua_Number y = lua_tonumber(L,-1);

    Scene* scene = SceneManager::getScene();
    if(scene == nullptr)
    {
        Util::PrintLine("Error: no current scene");
        return 0;
    }

    int t_id = scene->addObject( new RectangleObject( x, y, DEFAULT_SIZE, DEFAULT_SIZE, 0, DEFAULT_COLOR) );
    if(t_id == 0) 
    {
        Util::PrintLine("Error: could not create Rectangle Object in Scene \'" + scene->getSceneName() + "\'");
        return 0;
    }
    
    lua_pushinteger(L,t_id);
    lua_setglobal(L,"current_object");
    lua_pushinteger(L,t_id);
    return 1;
}

int UserAPI::make_circle(lua_State* L) 
{
    lua_Number x = lua_tonumber(L,-2);
    lua_Number y = lua_tonumber(L,-1);

    Scene *currScene = SceneManager::getScene();
    if(currScene == nullptr)
    {
        Util::PrintLine("Error: no current scene");
        return 0;
    }

    int t_id = currScene->addObject(new CircleObject(x,y,(DEFAULT_SIZE/2),0,DEFAULT_COLOR)); 
    if(t_id == 0)
    {
        Util::PrintLine("Error: could not create Circle Object in Scene \'" + currScene->getSceneName() + "\'");
        return 0;
    }
    
    lua_pushinteger(L,t_id);
    lua_setglobal(L,"current_object");
    lua_pushinteger(L,t_id);
    return 1;
}

int UserAPI::make_text(lua_State* L)
{
    lua_Number x = lua_tonumber(L,-3);
    lua_Number y = lua_tonumber(L,-2);
    std::string text = lua_tostring(L,-1);

    Scene *currScene = SceneManager::getScene();
    if(currScene == nullptr)
    {
        Util::PrintLine("Error: no current scene");
        return 0;
    }
    //int t_id = currScene->addObject( new TextObject("TEXT",0,0) ); 
    int t_id = currScene->addObject(new RectangleObject(0,0)); 
    if(t_id < 0)
    {
        Util::PrintLine("Error: could not create Text Object in Scene \'" + currScene->getSceneName() + "\'");
        return 0;
    }
    
    lua_pushinteger(L,t_id);
    lua_setglobal(L,"current_object");
    lua_pushinteger(L,t_id);
    
    return 1;
}

int UserAPI::make_naught(lua_State* L)
{
    lua_Number x = lua_tonumber(L,-2);
    lua_Number y = lua_tonumber(L,-1);

    Scene *currScene = SceneManager::getScene();
    if(currScene == nullptr)
    {
        Util::PrintLine("Error: no current scene");
        return 0;
    }

    int t_id = currScene->addObject(new TTT_Token(false,x,y)); 
    if(t_id == 0)
    {
        Util::PrintLine("Error: could not create Naught Object in Scene \'" + currScene->getSceneName() + "\'");
        return 0;
    }
    
    lua_pushinteger(L,t_id);
    lua_setglobal(L,"current_object");
    lua_pushinteger(L,t_id);
    return 1;
}

int UserAPI::make_cross(lua_State* L)
{
    {
    lua_Number x = lua_tonumber(L,-2);
    lua_Number y = lua_tonumber(L,-1);

    Scene *currScene = SceneManager::getScene();
    if(currScene == nullptr)
    {
        Util::PrintLine("Error: no current scene");
        return 0;
    }


    int t_id = currScene->addObject(new TTT_Token(true,x,y)); 
    if(t_id == 0)
    {
        Util::PrintLine("Error: could not create Cross Object in Scene \'" + currScene->getSceneName() + "\'");
        return 0;
    }
    
    lua_pushinteger(L,t_id);
    lua_setglobal(L,"current_object");
    lua_pushinteger(L,t_id);
    return 1;
}
}

int make_paddle(lua_State* L)
{
    return 0;
}
  
int UserAPI::set_position(lua_State* L)
{
    lua_Number t_id = lua_tonumber(L,-3);
    lua_Number t_x  = lua_tonumber(L,-2);
    lua_Number t_y  = lua_tonumber(L,-1);

    Scene *currScene = SceneManager::getScene();
    if(currScene == nullptr)
    {
        Util::PrintLine("Error: no current scene");
        return 0;
    }

    GameObject *currObj = currScene->findObject(t_id);
    if(currObj == nullptr) 
    {
        Util::PrintLine("Error: could not get specified object " + std::to_string( t_id) +" in Scene" + currScene->getSceneName() + " \n");
        return 0;
    }

    currObj->setPosition(t_x, t_y);
    return 0;
}

int UserAPI::set_x_position(lua_State* L)
{
    lua_Number t_id = lua_tonumber(L,-2);
    lua_Number t_x = lua_tonumber(L,-1);

    Scene *currScene = SceneManager::getScene();
    if(currScene == nullptr)
    {
        Util::PrintLine("Error: no current scene");
        return 0;
    }

    GameObject *currObj = currScene->findObject(t_id);
    if(currObj == nullptr) 
    {
        Util::PrintLine("Error: could not get specified object " + std::to_string( t_id) +" in Scene" + currScene->getSceneName() + " \n");
        return 0;
    }

    currObj->setPosition(t_x, currObj->getPosition().v);
    return 0;
}

int UserAPI::set_y_position(lua_State* L)
{
    lua_Number t_id = lua_tonumber(L,-2);
    lua_Number t_y = lua_tonumber(L,-1);

    Scene *currScene = SceneManager::getScene();
    if(currScene == nullptr)
    {
        Util::PrintLine("Error: no current scene");
        return 0;
    }

    GameObject *currObj = currScene->findObject(t_id);
    if(currObj == nullptr) 
    {
        Util::PrintLine("Error: could not get specified object " + std::to_string( t_id) +" in Scene" + currScene->getSceneName() + " \n");
        return 0;
    }

    currObj->setPosition(currObj->getPosition().u, t_y);
    return 0;
}

int UserAPI::get_x_position(lua_State* L)
{
    lua_Number t_id = lua_tonumber(L,-1);

    Scene *currScene = SceneManager::getScene();
    if(currScene == nullptr)
    {
        Util::PrintLine("Error: no current scene");
        return 0;
    }

    GameObject *currObj = currScene->findObject(t_id);
    if(currObj == nullptr) 
    {
        Util::PrintLine("Error: could not get specified object " + std::to_string( t_id ) +" in Scene" + currScene->getSceneName() + " \n");
        return 0;
    }

    lua_pushnumber(L, currObj->getPosition().u);
    return 1;
}
   
int UserAPI::get_y_position(lua_State* L)
{
    lua_Number t_id = lua_tonumber(L,-1);

    Scene *currScene = SceneManager::getScene();
    if(currScene == nullptr)
    {
        Util::PrintLine("Error: no current scene");
        return 0;
    }

    GameObject *currObj = currScene->findObject(t_id);
    if(currObj == nullptr) 
    {
        Util::PrintLine("Error: could not get specified object " + std::to_string( t_id) +" in Scene" + currScene->getSceneName() + " \n");
        return 0;
    }
    
    lua_pushnumber(L,currObj->getPosition().v);
    return 1;
}
   
int UserAPI::rotate(lua_State* L)
{
    lua_Number t_id = lua_tonumber(L,-2);
    lua_Number t_angle = lua_tonumber(L,-1);

    Scene *currScene = SceneManager::getScene();
    if(currScene == nullptr)
    {
        Util::PrintLine("Error: no current scene");
        return 0;
    }

    GameObject *currObj = currScene->findObject(t_id);
    if(currObj == nullptr) 
    {
        Util::PrintLine("Error: could not get specified object " + std::to_string( t_id) +" in Scene" + currScene->getSceneName() + " \n");
        return 0;
    }

    currObj->Rotate(t_angle);
    m3d::Thread::sleep(STEP_TIME);
    return 0;
}
    
int UserAPI::set_angle(lua_State* L)
{
    lua_Number t_id = lua_tonumber(L,-2);
    lua_Number t_angle = lua_tonumber(L,-1);

    Scene *currScene = SceneManager::getScene();
    if(currScene == nullptr)
    {
        Util::PrintLine("Error: no current scene");
        return 0;
    }

    GameObject *currObj = currScene->findObject(t_id);
    if(currObj == nullptr) 
    {
        Util::PrintLine("Error: could not get specified object " + std::to_string( t_id) +" in Scene" + currScene->getSceneName() + " \n");
        return 0;
    }

    currObj->setAngle(t_angle);
    m3d::Thread::sleep(STEP_TIME);
    return 0;
}
    
int UserAPI::get_angle(lua_State* L)
{
    lua_Number t_id = lua_tonumber(L,-1);

    Scene *currScene = SceneManager::getScene();
    if(currScene == nullptr)
    {
        Util::PrintLine("Error: no current scene");
        return 0;
    }

    GameObject *currObj = currScene->findObject(t_id);
    if(currObj == nullptr) 
    {
        Util::PrintLine("Error: could not get specified object " + std::to_string( t_id) +" in Scene" + currScene->getSceneName() + " \n");
        return 0;
    }

    lua_pushnumber(L, currObj->getAngle());

    return 1;
}
   
// TODO: Design such that x or y = -1, maintains that scale.
int UserAPI::set_scale(lua_State* L)
{
    lua_Number t_id     = lua_tonumber(L,-3);
    lua_Number t_width = lua_tonumber(L,-2);
    lua_Number t_height = lua_tonumber(L,-1);

    Scene *currScene = SceneManager::getScene();
    if(currScene == nullptr)
    {
        Util::PrintLine("Error: no current scene");
        return 0;
    }

    GameObject *currObj = currScene->findObject(t_id);
    if(currObj == nullptr) 
    {
        Util::PrintLine("Error: could not get specified object " + std::to_string( t_id) +" in Scene" + currScene->getSceneName() + " \n");
        return 0;
    }

    currObj->setScale(t_width,t_height);
    m3d::Thread::sleep(STEP_TIME);
    return 0;
}
    
int UserAPI::get_x_scale(lua_State* L)
{
    lua_Number t_id = lua_tonumber(L,-1);

    Scene *currScene = SceneManager::getScene();
    if(currScene == nullptr)
    {
        Util::PrintLine("Error: no current scene");
        return 0;
    }

    GameObject *currObj = currScene->findObject(t_id);
    if(currObj == nullptr) 
    {
        Util::PrintLine("Error: could not get specified object " + std::to_string( t_id) +" in Scene" + currScene->getSceneName() + " \n");
        return 0;
    }

    lua_pushnumber(L, currObj->getScale().u);

    return 1;
}
    
int UserAPI::get_y_scale(lua_State* L)
{
    lua_Number t_id = lua_tonumber(L,-1);

    Scene *currScene = SceneManager::getScene();
    if(currScene == nullptr)
    {
        Util::PrintLine("Error: no current scene");
        return 0;
    }

    GameObject *currObj = currScene->findObject(t_id);
    if(currObj == nullptr) 
    {
        Util::PrintLine("Error: could not get specified object " + std::to_string( t_id) +" in Scene" + currScene->getSceneName() + " \n");
        return 0;
    }

    lua_pushnumber(L, currObj->getScale().v);

    return 1;
}

int UserAPI::set_color(lua_State* L)
{
    lua_Number t_id     = lua_tonumber(L,-5);
    lua_Number t_red    = lua_tonumber(L,-4);
    lua_Number t_green  = lua_tonumber(L,-3);
    lua_Number t_blue   = lua_tonumber(L,-2);
    lua_Number t_alpha  = lua_tonumber(L,-1);

    Scene *currScene = SceneManager::getScene();
    if(currScene == nullptr)
    {
        Util::PrintLine("Error: no current scene");
        return 0;
    }

    GameObject *currObj = currScene->findObject(t_id);
    if(currObj == nullptr) 
    {
        Util::PrintLine("Error: could not get specified object " + std::to_string( t_id) +" in Scene" + currScene->getSceneName() + " \n");

    }

    currObj->setColor(m3d::Color(t_red,t_green,t_blue,t_alpha));
    m3d::Thread::sleep(STEP_TIME);
    return 0;
}

int UserAPI::select_object(lua_State* L)
{
    lua_Number t_id = lua_tonumber(L,-1);

    Scene *currScene = SceneManager::getScene();
    if(currScene == nullptr)
    {
        Util::PrintLine("Error: no current scene");
        return 0;
    }

    GameObject *currObj = currScene->findObject(t_id);
    if(currObj == nullptr) 
    {
        Util::PrintLine("Error: could not get specified object " + std::to_string( t_id) +" in Scene" + currScene->getSceneName() + " \n");

    }
    if(t_id < 0)
    {
        lua_pushnil(L);
    }else
    {
        lua_pushnumber(L,t_id);
    }
    lua_setglobal(L,"current_object");
    return 0;
}

int UserAPI::delete_object(lua_State* L)
{
    lua_Number t_id = lua_tonumber(L,-1);
    Scene *currScene = SceneManager::getScene();
    
    if(currScene == nullptr)
    {
        Util::PrintLine("Error: no current scene");
        return 0;
    }

    GameObject *currObj = currScene->findObject(t_id);
    if(currObj == nullptr) 
    {
        Util::PrintLine("Error: could not get specified object " + std::to_string( t_id) +" in Scene" + currScene->getSceneName() + " \n");
        return 0;
    }
    currScene->removeObject(t_id);

	delete(currObj);
	currObj = nullptr;
    m3d::Thread::sleep(STEP_TIME);
    return 0;
}



