#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <vector>
#include <math.h>
#include <map>


#include "lua/lua.hpp"
#include <m3dia.hpp>

#include "userAPI.hpp"
#include "util.hpp"

/// Memory capacity of the  sandbox in bytes
#define SANDBOX_MEM_CAPACITY 4096
#define THREAD_STACKSIZE (unsigned long long)4096 

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
class LuaSandbox final
{
private:     
    
    //static const luaL_Reg m_custom_funcs[];
    static unsigned long int m_memCapacity; /// Maximum memory size in bytes
    static unsigned long int m_memSize; /// Current memory in use, in bytes
            
    static lua_State *m_sandbox; /// Lua state object
    static short int m_threadState; /// Thread state
    static m3d::Thread *m_thread; /// Lua thread
    static std::string *m_currentChunk; /// Current running lua chunk

    static m3d::Mutex m_mutex_thread;         /// Control access to @ref m_thread
    static m3d::Mutex m_mutex_threadState;    /// Control access to @ref m_threadState
    static m3d::Mutex m_mutex_memory;         /// Control access to sandbox memory
    static m3d::Mutex m_mutex_sandbox;        /// Control access to @ref sandbox execution

    static std::function<void()>    m_preExecution,     /// function to be run before to an execution 
                                    m_postExecution;    /// function to be run after an execution

    /**
     *  Custom Lua memory allocation function
     *  @param ud user defined data object
     *  @param ptr pointer to the start of the target memory block
     *  @param osize original size of the target memory block
     *  @param nsize desired size oth the target memory block
     *  @returns new pointer to the start of the target memory block, returns null if no space could be made
     */
    static void * allocator(void *ud, void *ptr, size_t osize, size_t nsize);

    /**
     * @brief Sandbox thread's main  function.
     * Only called by the minigameclass to initialize the sandboxThread
     * @param param m3d::Parameter, recieves a pointer to the threadState variable
     */
    static void sandboxRuntime(m3d::Parameter param);

    /**
     *  @brief Loads the functions of @ref m_custom_funcs into the sandbox
     *  @param L lua state object
     *  @returns number of return values, always 1
     */
    static int luaopen_custom (lua_State *L);
    
public:
    

    

    /**
     *  @brief Initialize a new sandbox environment.
     *  If one exists this function will destroy it and create a new environment
     *  @param status 
     */
    static m3d::Thread * Initialize( int* status /** [in,out] */);

    static void SetPreOp(std::function<void()>& func);

    static void SetPostOp(std::function<void()>& func);

    /**
     *  @brief Set the state of the sandbox thread.
     *  Sets the state within both the native and lua environment
     *  @param state state to set
     */
    static void SetThreadState(int state);

    /**
     *  @brief Get the state of the sandbox thread
     */
    static int GetThreadState();

    /**
     *  @brief Destroys the current sandbox environment
     */
    static void Destroy();
   
    /**
     *  @brief get the current memory capacity
     *  @returns current memory capacity (bytes)
     */
    static unsigned long int getMemCapacity();    

    /**
     *  @returns memory space in use
     */
    static unsigned long int getMemSize();

    /**
     *  @brief Assign a new maximum memory capacity.
     *  @param capacity value to assign.
     */
    static void setMemCapacity(unsigned long int capacity);

    /**
     *  try to read the value of a double field with the given identifier
     *  @returns value assigned to the identifier in the lua environment
     *  
     *  @throw exception if variable either does not exist or, is of a different memory type
     */
    static void tryGetDouble(std::string varName, double* &ptr);

    /**
     *  try to read the value of a string field with the given identifier
     *  @returns value assigned to the identifier in the lua environment
     *  @throw exception if variable either does not exist or, is of a different memory type
     */
    static void tryGetString(std::string varName, std::string* &ptr);

    /**
     *  try to read the value of a boolean field with the given identifier
     *  @returns value assigned to the identifier in the lua environment
     *  @throw exception if variable either does not exist or, is of a different memory type
     */
    static void tryGetBool(std::string varName, bool* &ptr);

    /**
     *  try to return a table with the given identifier
     *  @returns value assigned to the identifier in the lua environment
     *  @throw exception if variable either does not exist or, is of a different memory type
     */
    static void tryGetTable(std::string varName, const void** &ptr);

    /**
     *  Declare or Assign a value in the environment
     *  @param identifier must be unique to avoid overwriting 
     *  @param data to be assigned
     *  @returns the value assigned
     */
    static bool setGlobal(std::string , int );
    static bool setGlobal(std::string , double );
    static bool setGlobal( std::string , std::string );

    /**
     *  Execute a chunk of lua code. 
     *  @throw exception if the system runs out of memory while copying the codeblock
     *  @returns 1 if there are no errors, 0 otherwise.
     */
    static bool ExecuteString(std::string );

    /**
     *  Execute a chunk of lua code. 
     *  @throw exception if the system runs out of memory while copying the codeblock
     *  @returns 1 if there are no errors, 0 otherwise.
     */
    static bool ExecuteFile(std::string);

    static bool ExecuteStringAsync(std::string);

    static bool ExecuteFileAsync(std::string);
};



