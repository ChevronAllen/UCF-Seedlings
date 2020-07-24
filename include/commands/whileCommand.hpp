#pragma once
#include "commands/commandObject.hpp"

class WhileCommand : public CommandObject
{

public:
    WhileCommand(std::string t_param ="true",bool t_lockEdit=false,bool t_lockAdd=false): CommandObject(t_lockEdit, t_lockAdd)
    {
        m_name="while";
		setParam(0, t_param);
        m_background = m3dCI::Sprite( *ResourceManager::getSprite("command_background_branching.png"));
        m_background.setTint(COM_LOCK_TINT);
    }

    ~WhileCommand();

    std::vector<std::string> getParamNames() {return {"Condition"};}

    std::string convertToLua()
    {
        return "while (" + m_params[0] + ") do\n"; 
    }

};