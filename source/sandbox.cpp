#include "sandbox.hpp"

/*
static lua_State * m_sandbox = nullptr; 

static m3d::Thread * m_thread = nullptr;       

static std::string * m_currentChunk = nullptr;
*/
int LuaSandbox::executeString(std::string text)
{
//  TODO: Needs a more thorough test
    // Temporary implementation, unprotected
    const char* temp = text.c_str();
    //Util::getInstance()->PrintLine(temp);
    
    return luaL_dostring(m_sandbox,temp);
}

int LuaSandbox::executeFile(std::string path)
{
    //  TODO: Needs a more thorough test
    // Temporary implementation, unprotected
    
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
    
    
    return luaL_dostring(m_sandbox,buffer);
}

