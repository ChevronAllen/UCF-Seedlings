#pragma once
#include "commands/commandObject.hpp"

class IfCommand : public CommandObject
{

public:
    IfCommand(std::string t_param = "true" ,bool t_lockEdit=false,bool t_lockAdd=false): CommandObject(t_lockEdit, t_lockAdd)
    {
        m_name="if";
		setParam(0, t_param);
        
        m_background = m3dCI::Sprite( *ResourceManager::getSprite("command_background_branching.png"));
        m_background.setTint(COM_LOCK_TINT);
    }

    ~IfCommand();

    std::vector<std::string> getParamNames() {return {"Condition"};}


    std::string convertToLua()
    {
        return "if (" + m_params[0] + ") then\n"; 
    }

};