#pragma once
#include "../commands/commandObject.hpp"

class SelectCommand : public CommandObject
{

public:
    SelectCommand(std::string t_param = "object",bool t_lockEdit=false,bool t_lockAdd=false): CommandObject(t_lockEdit, t_lockAdd)
    {
        m_name="select";
		setParam(0, t_param);
        m_background = m3dCI::Sprite( *ResourceManager::getSprite("command_background_var.png"));
        m_background.setTint(COM_LOCK_TINT);
    }

    ~SelectCommand();

    std::vector<std::string> getParamNames() {return {"Object Name"};}

    std::string convertToLua()
    {
        return "select_object(\"" + m_params[0] + "\")\n";
    }

};