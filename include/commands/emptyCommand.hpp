#pragma once
#include "commands/commandObject.hpp"

class EmptyCommand : public CommandObject
{

public:
    EmptyCommand(bool t_lockEdit=false,bool t_lockAdd=false): CommandObject(true, false)
    {
        m_name="--";
    }

    ~EmptyCommand();

    std::vector<std::string> getParamNames() {return {};}


    std::string convertToLua()
    {
        return "--\n"; 
    }

};