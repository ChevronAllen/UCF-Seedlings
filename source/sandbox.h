#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <vector>
#include <math.h>
//#include <map>
//#include <any>

#include "lua/lua.hpp"

/// Memory capacity of the  sandbox in bytes
#define SANDBOX_MEM_CAPACITY 4096

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
class LuaSandbox
{

private:
    ///  Maximum memory size in bytes
    unsigned long int memCapacity;

    ///  Current memory in use, in bytes
    unsigned long int memSize;

    ///  Head of the allocated memory block
    void* memHead;
    
    ///  Lua state object
    lua_State * state;    

public:
    /**
     *  Used to track memory blocks which have been allocated
     */
    typedef struct allocated_memory_block{
        void* head;     /// starting address of the memory block
        size_t size;    /// size of the block in bytes.

        // End of memory block
        void* end(){ return (void*)((int)head + (int)size);}


        friend inline bool operator ==  (allocated_memory_block a, allocated_memory_block b);
        friend inline bool operator !=  (allocated_memory_block a, allocated_memory_block b);
        friend inline bool operator <   (allocated_memory_block a, allocated_memory_block b);
        friend inline bool operator >   (allocated_memory_block a, allocated_memory_block b);
        friend inline bool operator <=  (allocated_memory_block a, allocated_memory_block b);
        friend inline bool operator >=  (allocated_memory_block a, allocated_memory_block b);

        allocated_memory_block(void* _ptr,size_t _size)
        {
            head = _ptr;
            size = _size;
        }
        
    }memBlock;

private:
    /// List of allocateed blocks
    std::vector<memBlock*> blockList;

    /**
     *  Sum of all active memory blocks
     *  @returns number of bytes in use
     */
    size_t getTotalMemoryUsed();

    /**
     *  Custom Lua memory allocation function
     *  @param ud user defined data object
     *  @param ptr pointer to the start of the target memory block
     *  @param osize original size of the target memory block
     *  @param nsize desired size oth the target memory block
     *  @returns new pointer to the start of the target memory block, returns null if no space could be made
     */
    void * allocator(void *ud, void *ptr, size_t osize, size_t nsize);

    /**
     *  Search the block list for a memory block with the same head pointer
     *  @param ptr pointer used to identify a block
     *  @returns allocated memory block if found otherwise NULL
     */
    memBlock* searchBlockList(void* );
    
    /**  Bind all User API functions to the Lua state */
    void bindAPI();


public:

    LuaSandbox()
    {
        state = luaL_newstate();
        memSize = 0;
        memCapacity = SANDBOX_MEM_CAPACITY;
        memHead = calloc(memCapacity, sizeof(void*) ) ;
        if(memHead == NULL)
        {
            std::cerr << "Error: memory allocation error, not enough space \n";
        }
        bindAPI();
    }

    ~LuaSandbox()
    {
        lua_close(state);
        free(memHead);
    }


    
    /**
     *  @returns memory capacity
     */
    unsigned long int getMemCapacity();

    /**
     *  @returns memory space in use
     */
    unsigned long int getMemSize();

    /**
     *  Set a new memory capacity
     */
    unsigned long int setMemCapacity();

    /**
     *  try to read the value of a double field with the given identifier
     *  @returns value assigned to the identifier in the lua environment
     *  @throw exception if variable either does not exist or, is of a different memory type
     */
    double tryGetDouble(std::string );

    /**
     *  try to read the value of a string field with the given identifier
     *  @returns value assigned to the identifier in the lua environment
     *  @throw exception if variable either does not exist or, is of a different memory type
     */
    std::string tryGetString(std::string );

    /**
     *  try to read the value of a boolean field with the given identifier
     *  @returns value assigned to the identifier in the lua environment
     *  @throw exception if variable either does not exist or, is of a different memory type
     */
    bool tryGetBool( std::string );

    /**
     *  try to return a table with the given identifier
     *  @returns value assigned to the identifier in the lua environment
     *  @throw exception if variable either does not exist or, is of a different memory type
     */
    //void tryGetTable( std::string );

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
     */
    void executeString(std::string );

    /**
     *  Execute a chunk of lua code. 
     *  @throw exception if the system runs out of memory while copying the codeblock
     */
    void executeFile(std::string );

    void close();
};



