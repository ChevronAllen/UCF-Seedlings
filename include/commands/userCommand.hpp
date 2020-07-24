#pragma once
#include "commands/commandObject.hpp"

class UserCommand : public CommandObject
{

public:
    UserCommand(std::string t_param ="--",bool t_lockEdit=false,bool t_lockAdd=false): CommandObject(t_lockEdit, t_lockAdd)
    {
        m_name="lua";
		setParam(0, t_param);
    }

    ~UserCommand();

    std::vector<std::string> getParamNames() {return {"lua"};}


    std::string convertToLua()
    {
        return m_params[0] + "\n"; 
    }

};