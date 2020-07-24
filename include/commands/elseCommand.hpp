#pragma once
#include "commands/commandObject.hpp"

class ElseCommand : public CommandObject
{

public:
    ElseCommand(bool t_lockEdit=false,bool t_lockAdd=false): CommandObject(t_lockEdit, t_lockAdd)
    {
        m_name="else";
        m_background = m3dCI::Sprite( *ResourceManager::getSprite("command_background_branching.png"));
        m_background.setTint(COM_LOCK_TINT);
    }

    ~ElseCommand();

    std::vector<std::string> getParamNames() {return {};}


    std::string convertToLua()
    {
        return "else\n"; 
    }

};