#pragma once
#include "commands/commandObject.hpp"

class GetXCommand : public CommandObject
{

public:
    GetXCommand(std::string varName = "var", bool t_lockEdit=false,bool t_lockAdd=false): CommandObject(t_lockEdit, t_lockAdd)
    {
        m_name="get x";
		setParam(0, varName);
    }

    ~GetXCommand();

    std::vector<std::string> getParamNames() {return { "Variable"};}

    std::string convertToLua()
    {
        return m_params[0] + " = get_x(current_object)\n"; 
    }

};

class GetYCommand : public CommandObject
{

public:
    GetYCommand(std::string varName = "var", bool t_lockEdit=false,bool t_lockAdd=false): CommandObject(t_lockEdit, t_lockAdd)
    {
        m_name="get y";
		setParam(0, varName);
    }

    ~GetYCommand();

    std::vector<std::string> getParamNames() {return {"Variable"};}

    std::string convertToLua()
    {
        return m_params[0] + " = get_y(current_object)\n"; 
    }

};

class SetXCommand : public CommandObject
{

public:
    SetXCommand(std::string t_value = 0,bool t_lockEdit=false,bool t_lockAdd=false): CommandObject(t_lockEdit, t_lockAdd)
    {
        m_name="set x";
		setParam(0, t_value);
    }

    ~SetXCommand();

    std::vector<std::string> getParamNames() {return {"value"};}

    std::string convertToLua()
    {
        return "set_x(current_object," + m_params[0] +")\n"; 
    }

};

class SetYCommand : public CommandObject
{

public:
    SetYCommand(std::string t_value = 0, bool t_lockEdit=false,bool t_lockAdd=false): CommandObject(t_lockEdit, t_lockAdd)
    {
        m_name="set y";
		setParam(0, t_value);
    }

    ~SetYCommand();

    std::vector<std::string> getParamNames() {return {"value"};}

    std::string convertToLua()
    {
        return "set_y( current_object," + m_params[0] +")\n"; 
    }

};