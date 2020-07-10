#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <vector>
#include <math.h>
//#include <map>
//#include <any>

#include "lua/lua.hpp"
#include <m3dia.hpp>

#include "userAPI.hpp"
#include "util.hpp"

/// Memory capacity of the  sandbox in bytes
#define SANDBOX_MEM_CAPACITY 4096

#define THREAD_HALT     1
#define THREAD_RUNNING  0
#define THREAD_CLOSE   -1

//typedef std::map<std::string, std::any > LuaTable;

/*
    A Sandbox must be initialized, using new LuaSandbox().
    From there its member values can be used  to execute code 'chunks' and read global values from the environment
*/

/**  
 *  Lua Sandbox object
 * tracks memory size and capacity, handles Lua errors 
 * provides access functions to the Lua environment
 */
namespace LuaSandbox
{
    /**
     *  @brief Anonymous namespace used to protect 'private' members and functions
     *  
     */
    namespace{
        
        
        static unsigned long int m_memCapacity = 0; /// Maximum memory size in bytes

        static unsigned long int m_memSize = 0;     /// Current memory in use, in bytes
                
        static lua_State * m_sandbox;       /// Lua state object

        static m3d::Thread * m_thread = nullptr;    /// Lua thread

        static short int m_threadState = 0;         /// Thread state
        
        static std::string * m_currentChunk = nullptr;  /// Current running lua chunk

        static m3d::Mutex   m_mutex_thread,         /// Control access to @ref m_thread
                            m_mutex_threadState,    /// Control access to @ref m_threadState
                            m_mutex_memory,         /// Control access to sandbox memory
                            m_mutex_sandbox;        /// Control access to @ref sandbox execution

        static std::function<void()> m_preExecution, m_postExecution;
        

        /**
         * @brief Sandbox thread's main  function.
         * Only called by the minigameclass to initialize the sandboxThread
         * @param param m3d::Parameter, recieves a pointer to the threadState variable
         */
        void sandboxRuntime(m3d::Parameter param)
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
                    m_sandbox->executeString(t_lua);
                    m_currentChunk = nullptr;
                    lock_sandbox.~Lock();

                    m_postExecution();

                    setThreadState(THREAD_RUNNING);
                }

                m3d::Thread::sleep();
            }
            
        }

        /**
         *  Custom Lua memory allocation function
         *  @param ud user defined data object
         *  @param ptr pointer to the start of the target memory block
         *  @param osize original size of the target memory block
         *  @param nsize desired size oth the target memory block
         *  @returns new pointer to the start of the target memory block, returns null if no space could be made
         */
        static void * allocator(void *ud, void *ptr, size_t osize, size_t nsize)
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

        /**
         * @brief Bind all User API functions to the Lua state 
         */
        static void bindAPI();

        static const luaL_Reg m_custom_funcs[] = {
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

        /**
         *  @brief Loads the functions of @ref m_custom_funcs into the sandbox
         *  @param L lua state object
         *  @returns number of return values, always 1
         */
        LUAMOD_API int luaopen_custom (lua_State *L) 
        {
            m3d::Lock lock(m_mutex_sandbox);
            luaL_newlib(L, m_custom_funcs);
            return 1;
        }
    }

    static void setPreOp(std::function<void()>& func)
    {
        m_preExecution = func;
    }

    static void setPostOp(std::function<void()>& func)
    {
        m_postExecution = func;
    }

    /**
     *  @brief Set the state of the sandbox thread.
     *  Sets the state within both the native and lua environment
     *  @param state state to set
     */
    void setThreadState(int state)
    {
        //  Wait for thread state access
        m3d::Lock lock_state(m_mutex_threadState);
        m_threadState = state;
        lock_state.~Lock();

        //m_sandbox->executeString("_EXEC_STATE = " + std::to_string(state));
    }

    /**
     *  @brief Get the state of the sandbox thread
     */
    int getThreadState()
    {
        m3d::Lock lock_state(m_mutex_threadState);
        return m_threadState;
    }

    /**
     *  @brief Destroys the current sandbox environment
     */
    static void Destroy()
    {
        m3d::Lock lock_sandbox(m_mutex_sandbox);
        lua_close(m_sandbox);
    }
   
    /**
     *  @brief get the current memory capacity
     *  @returns current memory capacity (bytes)
     */
    static unsigned long int getMemCapacity()
    {
        m3d::Lock lock_mem(m_mutex_memory);
        return m_memCapacity;
    }

    /**
     *  @returns memory space in use
     */
    static unsigned long int getMemSize()
    {
        m3d::Lock lock_mem(m_mutex_memory);
        return m_memSize;
    }

    /**
     *  @brief Assign a new maximum memory capacity.
     *  @param capacity value to assign.
     */
    static void setMemCapacity(unsigned long int capacity)
    {
        m3d::Lock lock_mem(m_mutex_memory);
        m_memCapacity = capacity;
    }

    /**
     *  try to read the value of a double field with the given identifier
     *  @returns value assigned to the identifier in the lua environment
     *  
     *  @throw exception if variable either does not exist or, is of a different memory type
     */
    static void tryGetDouble(std::string varName, double* &ptr)
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

    /**
     *  try to read the value of a string field with the given identifier
     *  @returns value assigned to the identifier in the lua environment
     *  @throw exception if variable either does not exist or, is of a different memory type
     */
    static std::string tryGetString(std::string varName, std::string* &ptr)
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

    /**
     *  try to read the value of a boolean field with the given identifier
     *  @returns value assigned to the identifier in the lua environment
     *  @throw exception if variable either does not exist or, is of a different memory type
     */
    static bool tryGetBool(std::string varName, bool* &ptr)
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

    /**
     *  try to return a table with the given identifier
     *  @returns value assigned to the identifier in the lua environment
     *  @throw exception if variable either does not exist or, is of a different memory type
     */
    static void tryGetTable(std::string varName, const void** &ptr)
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

    /**
     *  attempts to execute a global function with some parameters
     *  @returns the number of results returned
     *  @throw exception if function either does not exist or is execution produced an error
     */
    //void executeGlobal( std::string, <params...> );

    /**
     *  Declare or Assign a value in the environment
     *  @param identifier must be unique to avoid overwriting 
     *  @param data to be assigned
     *  @returns the value assigned
     */
    int setGlobal(std::string , int );
    double setGlobal(std::string , double );
    std::string setGlobal( std::string , std::string );

    /**
     *  Execute a chunk of lua code. 
     *  @throw exception if the system runs out of memory while copying the codeblock
     *  @returns 1 if there are no errors, 0 otherwise.
     */
    int executeString(std::string );

    /**
     *  Execute a chunk of lua code. 
     *  @throw exception if the system runs out of memory while copying the codeblock
     *  @returns 1 if there are no errors, 0 otherwise.
     */
    int executeFile(std::string );

    static void Initialize()
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
        lock_sandbox.~Lock();

        //bindAPI();
        executeFile("lua/init_scene.lua");

        m_thread = new m3d::Thread();
    }
};



