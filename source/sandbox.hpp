#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <vector>
#include <math.h>
#include <map>
#include <queue>


#include "lua/lua.hpp"

//#include "userAPI.hpp"

#ifdef DEBUG
#define DEBUG_SANDBOX
#endif

#define SANDBOX_MEM_CAPACITY 4096 /** Memory capacity of the  sandbox in bytes*/
#define THREAD_STACK (unsigned long long) 4096 /** Memory capacity of the sandbox thread stack in bytes*/

#define THREAD_HALT     1 /**Thread State Value. Pauses thread execution*/
#define THREAD_RUNNING  0 /**Thread State Value. Continues thread execution*/
#define THREAD_CLOSE   -1 /**Thread State Value. Closes the thread*/



/**  
 *  @brief LuaSandbox Object
 * 
 *  The LuaSandbox class handles all interactions with the Lua API lua_State object.
 *  Providing memory allocation, multithreaded execution , debug tools, and global variable access
 */
class LuaSandbox final
{

private:
    
    unsigned long int memCapacity; /// Maximum memory size in bytes
    unsigned long int memSize; /// Current memory in use, in bytes
    
    lua_State * m_luaState; /// Lua state object
    m3d::Thread * m_thread; /// Thread pointer
    int m_threadState; /// Thread State
    std::queue<std::string> m_luaQueue; /// Queue of lua chunks to execute
    m3d::Mutex  m_mutex_sandbox /**Control Access to lua_State object*/,
                m_mutex_threadState /**Control Access to thread state*/,
                m_mutex_allocation /**Control Access to sandbox's memory allocation*/,
                m_mutex_lua /**Control Access to lua queue*/;
    
    std::function<void()>   m_execBefore = [](){} /**Function executed before each queued sandbox execution*/,
                            m_execAfter = [](){} /**Function executed after each queued sandbox execution*/;


    /**
	 * @brief Sandbox thread's main  function.
     * 
	 * Only called by the minigameclass to initialize the sandboxThread
	 * @param param m3d::Parameter, recieves a pointer to the threadState variable
	 */
	void sandboxRuntime(m3d::Parameter param); 

    /**
     *  @brief Custom Lua memory allocation function
     * 
     *  @param ud user defined data object
     *  @param ptr pointer to the start of the target memory block
     *  @param osize original size of the target memory block
     *  @param nsize desired size oth the target memory block
     *  @returns new pointer to the start of the target memory block, returns null if no space could be made
     */
    static void * allocator(void *ud, void *ptr, size_t osize, size_t nsize);
    
    /** @brief Bind all User API functions to the Lua state 
     * 
     *  Adds all functions defined in @ref enabledFunctions to the sandbox environment
     */
    void bindAPI();

    /**
     *  @brief Initialized the lua_state and the sandbox thread
     * 
     *  @param before function to be executed before multithreaded executions.
     *  @param after function to be executed after multithreaded executions.
     */
    void initialize(std::function<void()> before, std::function<void()> after);

public:

    /** 
     *  @brief Constructs a LuaSandbox defining the pre and post execution functions.
     * 
     *  @param before function to be executed before queued Lua code
     *  @param after function to be executed after queued Lua code
     */
    LuaSandbox(std::function<void()>,std::function<void()>);

    /** 
     *  @brief handles the destruction of data structures within the Lua sandbox
     *  
     *  @warning Triggers the closure of the running thread, then waits for the thread to exit.
     */
    ~LuaSandbox();

    /**
     *  @brief Read the Sandbox's Memory capacity
     * 
     *  @returns memory capacity
     */
    unsigned long int getMemCapacity();

    /**
     *  @brief Set a new memory capacity
     */
    unsigned long int setMemCapacity();

    /**
     *  @brief Read the current Memory Size
     * 
     *  @returns memory space in use
     */
    unsigned long int getMemSize();

    /**
	 *  @brief Set the state of the sandbox thread.
     * 
	 *  Sets the state within both the native and lua environment
     *  @note use @ref THREAD_RUNNING, @ref THREAD_HALT, @ref THREAD_CLOSE definitions
     *  @warning may wait for the threadstate to unlock
	 *  @param state state to set
	 */
	void setThreadState(int state);

	/**
	 *  @brief Get the state of the sandbox thread
     * 
     *  Reads the @ref m_threadState
     *  @note use @ref THREAD_RUNNING, @ref THREAD_HALT, @ref THREAD_CLOSE definitions
     *  @warning may wait for the threadstate to unlock
     *  @returns State of the sandbox thread
	 */
	int getThreadState();

    /**
     * @brief Change the pre and post execution functions
     */
    void setExecutionContext(   std::function<void()> before = [](){},
                                std::function<void()> after  = [](){})
    {
        m_execBefore = before;
        m_execBefore = after;
    }

    /**
     *  @brief Read the value of a global variable as a double.
     * 
     *  Try to read the value of a double field with the given identifier
     *  @returns value assigned to the identifier in the Lua environment
     *  @throw exception if variable either does not exist or, is of a different memory type
     */
    bool tryGetDouble(std::string, double* );

    /**
     *  @brief Read the value of a global variable as a string.
     * 
     *  try to read the value of a string field with the given identifier
     *  @returns value assigned to the identifier in the lua environment
     *  @throw exception if variable either does not exist or, is of a different memory type
     */
    bool tryGetString(std::string, std::string* );

    /**
     *  @brief Read the value of a global variable as a bool.
     * 
     *  try to read the value of a boolean field with the given identifier
     *  @returns value assigned to the identifier in the lua environment
     *  @throw exception if variable either does not exist or, is of a different memory type
     */
    bool tryGetBool( std::string, bool* );

    /**
     *  @brief Set the value of a global variable.
     * 
     *  Declare or Assign a value in the environment
     *  @param identifier must be unique to avoid overwriting 
     *  @param data to be assigned
     *  @returns the value assigned
     */
    bool setGlobal(std::string identifier, int* data);

    /**
     *  @brief Set the value of a global variable.
     * 
     *  Declare or Assign a value in the environment
     *  @param identifier must be unique to avoid overwriting 
     *  @param data to be assigned
     *  @returns the value assigned
     */
    bool setGlobal(std::string identifier, double* data);

    /**
     *  @brief Set the value of a global variable.
     * 
     *  Declare or Assign a value in the environment
     *  @param identifier must be unique to avoid overwriting 
     *  @param data to be assigned
     *  @returns the value assigned
     */
    bool setGlobal(std::string identifier, std::string* data);

    /**
     *  @brief Execute a chunk of lua code. 
     * 
     *  @warning will wait for the sandbox to be available 
     *  @throw exception if the system runs out of memory while copying the codeblock
     *  @returns false if execution was unsuccessful. true otherwise.
     */
    bool executeString(std::string );

    /**
     *  @brief Execute a chunk of lua code. 
     *  
     *  @throw exception if the system runs out of memory while copying the codeblock
     *  @returns false if execution was unsuccessful. true otherwise.
     */
    bool executeFile(std::string );

    /**
     *  @brief Execute a chunk of lua code. 
     * 
     *  @throw exception if the system runs out of memory while copying the codeblock
     *  @returns size of the queue.
     */
    int executeStringQueued(std::string text);

    /**
     *  @brief Execute a chunk of lua code. 
     * 
     *  @throw exception if the system runs out of memory while copying the codeblock
     *  @returns size of the queue.
     */
    int executeFileQueued(std::string path);

    /**
     *  Closes and waits on the sandbox thread, then closes the current lua_State.
     *  @warning this function calls a max length join() and will block the current thread indefinitely.
     */
    void close();

    /**
     *  @brief Closes and initializes the sandbox
     * 
     *  executes @ref close() then @ref initialize()
     */
    void resetSandbox();

    /**
     *  @brief Get the size of the Lua queue
     * 
     *  @warning locks access to the luaQueue
     */
    int getQueueSize();

    /**
     *  @brief Clear the Lua queue going to the thread
     * 
     *  @warning locks access to the luaQueue
     */
    void clearQueue();
};



