#pragma once
#include "../commands/commandObject.hpp"

class ScaleCommand : public CommandObject
{

public:
    // TODO: Design such that x or y = -1, maintains that scale.
    ScaleCommand(std::string t_x , std::string t_y , bool t_lockEdit=false,bool t_lockAdd=false): CommandObject(t_lockEdit, t_lockAdd)
    {
        m_name="scale";
		setParam(0, t_x);
		setParam(1, t_y);
    }

    ~ScaleCommand();

    std::vector<std::string> getParamNames() {return {"x scale", "y scale"};}

    std::string convertToLua()
    {
        return "scale_object(" + m_params[0] + "," + m_params[0] + ")\n"; 
    }

};

class Get_ScaleXCommand : public CommandObject
{

public:
    // TODO: Design such that x or y = -1, maintains that scale.
    Get_ScaleXCommand(std::string t_varName = "temp", bool t_lockEdit=false, bool t_lockAdd=false): CommandObject(t_lockEdit, t_lockAdd)
    {
        m_name="get x scale";
		setParam(0, t_varName);

    }

    ~Get_ScaleXCommand();

    std::vector<std::string> getParamNames() {return {"Variable"};}

    std::string convertToLua()
    {
        return "scale_object(" + m_params[0] + "," + m_params[0] + ")\n"; 
    }

};

class Get_ScaleYCommand : public CommandObject
{

public:
    // TODO: Design such that x or y = -1, maintains that scale.
    Get_ScaleYCommand(std::string t_varName = "temp", bool t_lockEdit=false,bool t_lockAdd=false): CommandObject(t_lockEdit, t_lockAdd)
    {
        m_name="get y scale";
		setParam(0, t_varName);
    }

    ~Get_ScaleYCommand();

    std::vector<std::string> getParamNames() {return {"Variable"};}

    std::string convertToLua()
    {
        return "scale_object(" + m_params[0] + "," + m_params[0] + ")\n"; 
    }

};




