#include "sandbox.hpp"

luaL_Reg m_custom_funcs[] = {
        { "println"     , UserAPI::print_line},
        { "print"       , UserAPI::print},
        { "rectangle"   , UserAPI::make_rectangle},
        { "circle"      , UserAPI::make_circle},
        { "triangle"    , UserAPI::make_rectangle},
        { "move"        , UserAPI::move_object},
        { "position"    , UserAPI::set_position},
        { "get_x"       , UserAPI::get_x_position},
        { "get_y"       , UserAPI::get_y_position},
        { "rotate"      , UserAPI::rotate},
        { "set_angle"   , UserAPI::set_angle},
        { "get_angle"   , UserAPI::get_angle},
        { "set_scale"   , UserAPI::set_scale},
        { "set_color"   , UserAPI::set_color},
        { "delete"      , UserAPI::delete_object},
        {NULL, NULL}
};  /// Defines functions included in the UserAPI

unsigned long int LuaSandbox::m_memCapacity = 0;
unsigned long int LuaSandbox::m_memSize = 0;
lua_State * LuaSandbox::m_sandbox = nullptr;
short int LuaSandbox::m_threadState = 0;
m3d::Thread * LuaSandbox::m_thread = nullptr;
std::string * LuaSandbox::m_currentChunk = nullptr;

int LuaSandbox::luaopen_custom (lua_State *L) 
{
    m3d::Lock lock(m_mutex_sandbox);
    luaL_newlib(L, m_custom_funcs);
    return 1;
}

void LuaSandbox::sandboxRuntime(m3d::Parameter param)
{            
    int* state = param.get<int*>();
    if(state == NULL)
    {
        Util::PrintLine("Error: threadstate not defined, sandbox thread closing.");
        return;
    }
    
    while(true)
    {                
        //  Lock access to Thread State
        m3d::Lock lock_state(m_mutex_threadState);
        if(*state == THREAD_CLOSE)
        {   
            break; //  close Thread
        }else if(*state == THREAD_HALT)
        {   
            continue;
        }                
        lock_state.~Lock();

        
        if(m_currentChunk != nullptr)
        {                    
            m_preExecution();
            //  TODO: Disable Command Menu
            std::string t_lua(m_currentChunk->c_str());
            
            #ifdef DEBUG
            Util::PrintLine(t_lua);
            #endif
            
            m3d::Lock lock_sandbox(m_mutex_sandbox);
            luaL_dostring(m_sandbox,t_lua.c_str());
            m_currentChunk = nullptr;
            lock_sandbox.~Lock();

            m_postExecution();

            SetThreadState(THREAD_RUNNING);
        }

        //  Give other threads a chance to wake
        m3d::Thread::sleep();
    }
    
}

void * LuaSandbox::allocator(void *ud, void *ptr, size_t osize, size_t nsize)
{
    m3d::Lock lock_mem(m_mutex_memory);
    (void)ud;  (void)osize;  /* not used */
    if (nsize == 0) 
    {
        free(ptr);
        return NULL;
    }
    else
    {
        return realloc(ptr, nsize);
    }
}

m3d::Thread* LuaSandbox::Initialize(int* status)
{
    m3d::Lock lock_sandbox(LuaSandbox::m_mutex_sandbox);
    if(m_sandbox != nullptr) 
    {
        Destroy();
    }
    m_sandbox = luaL_newstate();
    luaopen_base(m_sandbox);
    luaopen_table(m_sandbox);
    luaopen_custom(m_sandbox);
    ExecuteFile("lua/init_scene.lua");
    lock_sandbox.~Lock();

    m_thread = new m3d::Thread(sandboxRuntime,status,false,false, THREAD_STACKSIZE);
    m_thread->start();
    return m_thread;
}

void LuaSandbox::Destroy()
{
    SetThreadState(THREAD_CLOSE);
    m_thread->join();
    m3d::Lock lock_sandbox(m_mutex_sandbox);
    lua_close(m_sandbox);
}

void LuaSandbox::SetPreOp(std::function<void()>& func)
{
    m_preExecution = func;
}

void LuaSandbox::SetPostOp(std::function<void()>& func)
{
    m_postExecution = func;
}

void LuaSandbox::SetThreadState(int state)
{
    m3d::Lock lock_state(m_mutex_threadState);
    m_threadState = state;
    lock_state.~Lock();

    m3d::Lock lock_sandbox(m_mutex_sandbox);
    std::string t_lua = "_EXEC_STATE = " + std::to_string(state);
    luaL_dostring(m_sandbox ,t_lua.c_str());
}

int LuaSandbox::GetThreadState()
{
    m3d::Lock lock_state(m_mutex_threadState);
    return m_threadState;
}

bool LuaSandbox::ExecuteString(std::string text)
{
    // TODO: Needs a more thorough test
    // Temporary implementation, unprotected
    const char* temp = text.c_str();    
    return luaL_dostring(m_sandbox,temp);
}

bool LuaSandbox::ExecuteFile(std::string path)
{    
    size_t size;
    char* buffer;
    std::string fullPath = "romfs:/";
    fullPath = fullPath.append(path);
    
    FILE* fp = fopen(fullPath.c_str(), "r");
    if(fp == NULL)
    {
        std::cerr << "Error: couldnt open file at '" << fullPath << "'" << std::endl;
        return 0;
    }

    fseek(fp,0L, SEEK_END);
    size = ftell(fp);
    rewind(fp);

    buffer = (char*)calloc(size, sizeof(char));
    fread(buffer,sizeof(char),size,fp);

    fclose(fp);    
    
    return ExecuteString(buffer);
}

bool LuaSandbox::ExecuteStringAsync(std::string text)
{
    if(m_currentChunk == nullptr)
    {
        m_currentChunk = new std::string(text);
        return true;
    }else{
        Util::PrintLine("warning: Thread in use");
        return false;
    }
    
}

bool LuaSandbox::ExecuteFileAsync(std::string path)
{
    if(m_currentChunk == nullptr)
    {
        size_t size;
        char* buffer;
        std::string fullPath = "romfs:/";
        fullPath = fullPath.append(path);
        
        FILE* fp = fopen(fullPath.c_str(), "r");
        if(fp == NULL)
        {
            std::cerr << "Error: couldnt open file at '" << fullPath << "'" << std::endl;
            return false;
        }

        fseek(fp,0L, SEEK_END);
        size = ftell(fp);
        rewind(fp);

        buffer = (char*)calloc(size, sizeof(char));
        fread(buffer,sizeof(char),size,fp);

        fclose(fp);

        return ExecuteStringAsync(buffer);
    }else
    {
        Util::PrintLine("warning: Thread in use");
        return false;
    }
    
}

unsigned long int LuaSandbox::getMemCapacity()
{
    m3d::Lock lock_mem(m_mutex_memory);
    return m_memCapacity;
}

void LuaSandbox::setMemCapacity(unsigned long int capacity)
{
    m3d::Lock lock_mem(m_mutex_memory);
    m_memCapacity = capacity;
}

unsigned long int LuaSandbox::getMemSize()
{
    m3d::Lock lock_mem(m_mutex_memory);
    return m_memSize;
}

void LuaSandbox::tryGetDouble(std::string varName, double* &ptr)
{        
    //  convert sting to const char*
    const char* n = varName.c_str();

    //  push value unto the stack
    int ltype = lua_getglobal(m_sandbox,n);

    // throw an error if the type is wrong
    if(ltype != LUA_TNUMBER){
        ptr = nullptr;
        //lua_Lerror(m_sandbox,"error: no number \'" + std::to_string(varName) + "\' found");
    }else{
        //  convert value on the stack to a double 
        *ptr = lua_tonumber(m_sandbox,-1);
    }

    // value no longer needed, remove from the stack
    lua_pop(m_sandbox,1);
}

void LuaSandbox::tryGetString(std::string varName, std::string* &ptr)
{
    
    //  convert sting to const char*
    const char* n = varName.c_str();

    //  push value unto the stack
    int ltype = lua_getglobal(m_sandbox,n);

    // throw an error if the type is wrong
    if(ltype != LUA_TSTRING){
        ptr = nullptr;
        //lua_Lerror(m_sandbox,"error: no number \'" + std::to_string(varName) + "\' found");
    }else{
        //  convert value on the stack to a double 
        *ptr = lua_tonumber(m_sandbox,-1);
    }

    // value no longer needed, remove from the stack
    lua_pop(m_sandbox,1);
}

void LuaSandbox::tryGetBool(std::string varName, bool* &ptr)
{
    
    //  convert string to const char*
    const char* n = varName.c_str();

    //  push value unto the stack
    int ltype = lua_getglobal(m_sandbox,n);

    // throw an error if the type is wrong
    if(ltype != LUA_TBOOLEAN){
        ptr = nullptr;
        //lua_Lerror(m_sandbox,"error: no number \'" + std::to_string(varName) + "\' found");
    }else{
        //  convert value on the stack to a double 
        *ptr = lua_tonumber(m_sandbox,-1);
    }

    // value no longer needed, remove from the stack
    lua_pop(m_sandbox,1);
}

void LuaSandbox::tryGetTable(std::string varName, const void** &ptr)
{
    
    //  convert string to const char*
    const char* n = varName.c_str();

    //  push value unto the stack
    int ltype = lua_getglobal(m_sandbox,n);

    // throw an error if the type is wrong
    if(ltype != LUA_TBOOLEAN){
        ptr = nullptr;
        //lua_Lerror(m_sandbox,"error: no number \'" + std::to_string(varName) + "\' found");
    }else{
        //  convert value on the stack to a double 
        *ptr =  lua_topointer(m_sandbox,-1);
    }

    // value no longer needed, remove from the stack
    lua_pop(m_sandbox,1);
}

bool LuaSandbox::setGlobal(std::string name, int value){ return false;}
bool LuaSandbox::setGlobal(std::string name, double value){ return false;}
bool LuaSandbox::setGlobal( std::string name, std::string value){ return false;}

