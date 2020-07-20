#include "userAPI.hpp"
#include "util.hpp"
#include "sandbox.hpp"

/**
 *  @brief enabled UserAPI functions
 * 
 *  The array of Lua accessible user API functions, paired with their Lua global name.
 *  Used to initialize the LuaSandbox.
 *  @note These functions are added as variable functionsand can be easily overwritten by assigning a new value to the global name.
 */
std::pair<std::string, lua_CFunction> enabledFunctions[] = {
    std::make_pair( "println" , UserAPI::print_line),
    std::make_pair( "print" , UserAPI::print),
    std::make_pair( "make_rectangle" , UserAPI::make_rectangle),
    std::make_pair( "make_circle" , UserAPI::make_circle),
    std::make_pair( "make_text" , UserAPI::make_text),
    std::make_pair( "move" , UserAPI::move_object),
    std::make_pair( "position" , UserAPI::set_position),
    std::make_pair( "get_x" , UserAPI::get_x_position),
    std::make_pair( "get_y" , UserAPI::get_y_position),
    std::make_pair( "rotate" , UserAPI::rotate),
    std::make_pair( "set_angle" , UserAPI::set_angle),
    std::make_pair( "get_angle" , UserAPI::get_angle),
    std::make_pair( "set_scale" , UserAPI::set_scale),
    std::make_pair( "get_x_scale", UserAPI::get_x_scale),
    std::make_pair( "get_y_scale", UserAPI::get_y_scale),
    std::make_pair( "set_color" , UserAPI::set_color),
    //std::make_pair( "select" , UserAPI::select_object),
    std::make_pair( "delete" , UserAPI::delete_object)
};

void LuaSandbox::initialize(std::function<void()> before = 0, std::function<void()> after = 0)
{
    memSize = 0;
    memCapacity = SANDBOX_MEM_CAPACITY;

    if(before != 0)
        m_execBefore = before;
    if(after != 0)
        m_execAfter = after;    

    m3d::Lock lock_sandbox(m_mutex_sandbox);
	m_luaState = lua_newstate(allocator,nullptr);
    luaopen_base(m_luaState);
    luaopen_table(m_luaState);
    bindAPI();
    executeFile("lua/init_scene.lua");
    lock_sandbox.~Lock();

    m_thread = new m3d::Thread( [this](m3d::Parameter p){sandboxRuntime(p);}, 
                                &m_threadState, false, false, THREAD_STACK);
    m_thread->start();
}

LuaSandbox::LuaSandbox(std::function<void()> before, std::function<void()> after)
{    
    initialize(before, after);
}

LuaSandbox::~LuaSandbox()
{
    close();
}

void LuaSandbox::sandboxRuntime(m3d::Parameter param)
{
	#ifdef DEBUG_SANDBOX
    Util::PrintLine("thread: start");
    #endif
	int* state = param.get<int*>();
	if (state == NULL)
	{
		Util::PrintLine("Error: threadstate not defined, sandbox thread closing.");
		return;
	}

    

    #ifdef DEBUG_SANDBOX
    Util::PrintLine("thread: sandbox initialized");
    #endif
	
	while (true)
	{
		//  Lock access to Thread State
		m3d::Lock lock_state(m_mutex_threadState);
		if (*state == THREAD_CLOSE)
		{   //  close Thread
			break;
		}
		else if (*state == THREAD_HALT)
		{
			continue;
		}
		// Unlock Thread State
		lock_state.~Lock();

		if (m_luaQueue.size() > 0)
		{
			m_execBefore();
			//  TODO : Disable Command Menu
            
            // Lock lua queue access
            m3d::Lock lock_queue(m_mutex_lua);
			std::string t_lua(m_luaQueue.front());
            m_luaQueue.pop();
            // Unlock lua queue access
            lock_queue.~Lock();

            #ifdef DEBUG_SANDBOX
			Util::PrintLine("thread: read \'"+t_lua.substr(0,30)+"\'");
            #endif

            // Lock lua state access
			m3d::Lock lock_sandbox(m_mutex_sandbox);
            if(luaL_dostring(m_luaState,t_lua.c_str()) > 0)
            {
                #ifdef DEBUG_SANDBOX
                Util::PrintLine("lua:execution failed on \'" + t_lua.substr(0,30) + "\'");
                #endif
            } 
            #ifdef DEBUG_SANDBOX
            else
            { 
                Util::PrintLine("lua: success on \'" + t_lua.substr(0,30) + "\'");
            }
            #endif
			
            // Unlock lua state access
            lock_sandbox.~Lock();

			m_execAfter();

		}

		m3d::Thread::sleep();
	}

    //setThreadState(THREAD_RUNNING);
    #ifdef DEBUG_SANDBOX
    Util::PrintLine("thread: exit");
    #endif
}

void* LuaSandbox::allocator(void *ud, void *ptr, size_t osize, size_t nsize)
{
    (void)ud;  (void)osize;  /* not used */
    if (nsize == 0) {
        free(ptr);
        return NULL;
    }
    else
        return realloc(ptr, nsize);
}

bool LuaSandbox::executeString(std::string text)
{
    #ifdef DEBUG_SANDBOX
    Util::PrintLine("executing: " + text.substr(0,20) + "...");
    #endif
    const char* temp = text.c_str();    
    m3d::Lock lock_sandbox(m_mutex_sandbox);
    return luaL_dostring(m_luaState,temp);
}

bool LuaSandbox::executeFile(std::string path)
{
    size_t length;
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
    size_t size = ftell(fp);
    rewind(fp);

    buffer = (char*)calloc(size, sizeof(char));
    fread(buffer,sizeof(char),size,fp);

    fclose(fp);
    
    return executeString(buffer);
}

int LuaSandbox::executeStringQueued(std::string text)
{
    #ifdef DEBUG_SANDBOX
    Util::PrintLine("queuing: " + text.substr(0,20) + "...");
    #endif

    m3d::Lock lock_code(m_mutex_lua);
    m_luaQueue.push(text);
    return m_luaQueue.size();
    
}

int LuaSandbox::executeFileQueued(std::string path)
{
    size_t length;
    char* buffer;
    std::string fullPath = "romfs:/";
    fullPath = fullPath.append(path);
    
    FILE* fp = fopen(fullPath.c_str(), "r");
    if(fp == NULL)
    {
        std::cerr << "Error: couldnt open file at '" << fullPath << "'" << std::endl;
        return -1;
    }

    fseek(fp,0L, SEEK_END);
    size_t size = ftell(fp);
    rewind(fp);

    buffer = (char*)calloc(size, sizeof(char));
    fread(buffer,sizeof(char),size,fp);
    fclose(fp);

    return executeStringQueued(buffer);
}

void LuaSandbox::setThreadState(int state)
{
    if(m_thread->isRunning())
    {
        m3d::Lock lock(m_mutex_threadState);
        m_threadState = state;
        executeString("_EXEC_STATE=" + std::to_string(state));
    }else
    {
        m_threadState = THREAD_CLOSE;
        executeString("_EXEC_STATE=" + std::to_string(THREAD_CLOSE));
    }
}

int LuaSandbox::getThreadState()
{
    if(m_thread->isRunning())
    {
        m3d::Lock lock(m_mutex_threadState);
        return m_threadState;
    }else{ return THREAD_CLOSE; }
}

bool LuaSandbox::tryGetDouble(std::string id, double* ptr)
{
    //  convert sting to const char*
    const char* n = id.c_str();

    //  push value unto the stack
    int ltype = lua_getglobal(m_luaState,n);

    //  convert value on the stack to a double 
    double value = lua_tonumber(m_luaState,-1);
    
    // value no longer needed, remove from the stack
    lua_remove(m_luaState,1);

    // throw an error if the type is wrong
    if(ltype != LUA_TNUMBER){
        return false;
    }
    *ptr = value;
    return true;
}

bool LuaSandbox::tryGetBool(std::string id, bool* ptr)
{
    //  convert sting to const char*
    const char* n = id.c_str();

    //  push value unto the stack
    int ltype = lua_getglobal(m_luaState,n);

    //  convert value on the stack to a double 
    bool value = lua_toboolean(m_luaState,-1);
    
    // value no longer needed, remove from the stack
    lua_remove(m_luaState,1);

    // throw an error if the type is wrong
    if(ltype != LUA_TNUMBER){
        return false;
    }
    *ptr = value;
    return true;
}

bool LuaSandbox::tryGetString(std::string id, std::string* ptr)
{
    //  convert sting to const char*
    const char* n = id.c_str();

    //  push value unto the stack
    int ltype = lua_getglobal(m_luaState,n);

    //  convert value on the stack to a double 
    std::string value = lua_tostring(m_luaState,-1);
    
    // value no longer needed, remove from the stack
    lua_remove(m_luaState,1);

    // throw an error if the type is wrong
    if(ltype != LUA_TNUMBER){
        return false;
    }
    *ptr = value;
    return true;
}

void LuaSandbox::bindAPI()
{
    
    for(std::pair<std::string, lua_CFunction> func : enabledFunctions)
    {
        lua_pushcfunction(m_luaState, func.second);
        lua_setglobal(m_luaState, func.first.c_str());
    }
    return;
}

void LuaSandbox::close()
{
    if(m_thread->isRunning())
    {
        setThreadState(THREAD_CLOSE);   
        m_thread->join();
    }
    lua_close(m_luaState);
    
}

void LuaSandbox::resetSandbox()
{
    close();
    initialize();
}

int LuaSandbox::getQueueSize()
{
    m3d::Lock lock_queue(m_mutex_lua);
    return m_luaQueue.size();
}

void LuaSandbox::clearQueue()
{
    m3d::Lock lock_queue(m_mutex_lua);
    while(!m_luaQueue.empty())
    {
        m_luaQueue.pop();
    }
}
