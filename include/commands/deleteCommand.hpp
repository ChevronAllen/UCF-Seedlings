#pragma once
#include "commands/commandObject.hpp"

class DeleteCommand : public CommandObject
{

public:
    DeleteCommand(bool t_lockEdit=false,bool t_lockAdd=false): CommandObject(t_lockEdit, t_lockAdd)
    {
        m_name="delete";
        m_background = m3dCI::Sprite( *ResourceManager::getSprite("command_background_delete.png"));
        m_background.setTint(COM_LOCK_TINT);
    }

    ~DeleteCommand();

    std::vector<std::string> getParamNames() {return {};} 

    std::string convertToLua()
    {
        return "delete_object(current_object)\n"; 
    }

};