#include "../userAPI.hpp"

/**
 * @brief sign function
 * @returns positive (1), negative (-1), or zero (0) depending on the value of the parameter.
 * @ref https://stackoverflow.com/questions/1903954/is-there-a-standard-sign-function-signum-sgn-in-c-c
 */
template <typename T> int sign(T val) {
    return (T(0) < val) - (val < T(0));
}

int UserAPI::move_object(lua_State* L)
{
    int y = lua_tonumber(L,-1);
    int x = lua_tonumber(L,-2); 
    int t_id = lua_tonumber(L,-3); 
    
    
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
    while(!(x == 0 && y == 0))
    {
        x = x - sign(x);
        y = y - sign(y);
        #ifdef DEBUG_API
            Util::PrintLine("state: " + std::to_string(t_runState) );
        #endif
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
        
        #ifdef DEBUG_API
        Util::PrintLine("step [" + std::to_string(t_id) + "]. x: " +  std::to_string(sign(x)) + ", y: " +  std::to_string(sign(x)) );
        #endif
        obj->moveTo( sign(x), sign(y));
        

        

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

    Util::PrintLine("test 1");
    Scene *currScene = SceneManager::getScene();
    if(currScene == nullptr)
    {
        Util::PrintLine("Error: no current scene");
        return 0;
    }
    Util::PrintLine("test 2");
    //int t_id = currScene->addObject( new TextObject("TEXT",0,0) ); 
    int t_id = currScene->addObject(new RectangleObject(0,0)); 
    if(t_id < 0)
    {
        Util::PrintLine("Error: could not create Text Object in Scene \'" + currScene->getSceneName() + "\'");
        return 0;
    }
    
    Util::PrintLine("test 3");
    lua_pushinteger(L,t_id);
    lua_setglobal(L,"current_object");
    lua_pushinteger(L,t_id);
    
    return 1;
}

int make_paddle(lua_State* L)
{
    return 0;
}
  
// TODO: Revise, no set position, only set x and y.
int UserAPI::set_position(lua_State* L)
{
    lua_Number t_id = lua_tonumber(L,-1);
    lua_Number t_x = lua_tonumber(L,-2);
    lua_Number t_y = lua_tonumber(L,-3);

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
    m3d::Thread::sleep(STEP_TIME);
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
    lua_Number t_id = lua_tonumber(L,-1);
    lua_Number t_angle = lua_tonumber(L,-2);

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
    lua_Number t_id = lua_tonumber(L,-1);
    lua_Number t_angle = lua_tonumber(L,-2);

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
    lua_Number t_id     = lua_tonumber(L,-1);
    lua_Number t_width  = lua_tonumber(L,-2);
    lua_Number t_height = lua_tonumber(L,-3);

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
    lua_Number t_id     = lua_tonumber(L,-1);
    lua_Number t_red  = lua_tonumber(L,-2);
    lua_Number t_green = lua_tonumber(L,-3);
    lua_Number t_blue  = lua_tonumber(L,-2);
    lua_Number t_alpha = lua_tonumber(L,-3);

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
    m3d::Thread::sleep(STEP_TIME);
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

    currObj->destroy();
    currObj = nullptr;
    m3d::Thread::sleep(STEP_TIME);
    return 0;
}
 
int UserAPI::change_color(lua_State* L)
{
    int t_id = lua_tonumber(L,-1); 
    return 0;
}