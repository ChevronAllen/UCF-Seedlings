#pragma once
#include "commands/commandObject.hpp"

class RotateCommand : public CommandObject
{

public:
    
	RotateCommand(std::string t_angle = "90", bool t_lockEdit = false, bool t_lockAdd = false) : CommandObject(t_lockEdit, t_lockAdd)
    {
        m_name="rotate";
		setParam(0, t_angle);
    }

    ~RotateCommand();

    std::vector<std::string> getParamNames() {return {"angle"};}

    std::string convertToLua()
    {
        return "rotate_object(current_object," + m_params[0] + ")\n"; 
    }

};



