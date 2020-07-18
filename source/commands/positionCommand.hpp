#pragma once
#include "../commands/commandObject.hpp"

class GetXCommand : public CommandObject
{

public:
    GetXCommand(bool t_lockEdit=false,bool t_lockAdd=false): CommandObject(t_lockEdit, t_lockAdd)
    {
        m_name="get x";
    }

    ~GetXCommand();

    std::vector<std::string> getParamNames() {return { "Variable"};}

    std::string convertToLua()
    {
        return m_params[0] + " = get_x()\n"; 
    }

};

class GetYCommand : public CommandObject
{

public:
    GetYCommand(bool t_lockEdit=false,bool t_lockAdd=false): CommandObject(t_lockEdit, t_lockAdd)
    {
        m_name="get y";
    }

    ~GetYCommand();

    std::vector<std::string> getParamNames() {return {"Variable"};}

    std::string convertToLua()
    {
        return m_params[0] + " = get_y()\n"; 
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
        return "set_x(" + m_params[0] +")\n"; 
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
        return "set_y(" + m_params[0] +")\n"; 
    }

};