#pragma once
#include "commands/commandObject.hpp"

class LoopCommand : public CommandObject
{
private:
    static unsigned int m_counter;
public:
    LoopCommand(std::string t_param ="1",bool t_lockEdit=false,bool t_lockAdd=false): CommandObject(t_lockEdit, t_lockAdd)
    {
        m_name="loop";
		setParam(0, t_param);
        m_background = m3dCI::Sprite( *ResourceManager::getSprite("command_background_branching.png"));
        m_background.setTint(COM_LOCK_TINT);
    }

    ~LoopCommand();

    std::vector<std::string> getParamNames() {return {"Count"};}

    std::string convertToLua()
    {
        std::string varName("LOOP_" + std::to_string(m_counter));
        return "local " + varName + " = " + m_params[0] +" \nwhile ( " + varName + " > 0 ) do \n" + varName + "= " + varName + " - 1 \n"; 
    }

};