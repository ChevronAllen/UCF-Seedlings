#pragma once
#include "commands/commandObject.hpp"

class LeftCommand : public CommandObject
{

public:
    LeftCommand(std::string t_param = "1",bool t_lockEdit=false,bool t_lockAdd=false): CommandObject(t_lockEdit, t_lockAdd)
    {
        m_name="left";
		setParam(0, t_param);
    }

    ~LeftCommand();

    std::vector<std::string> getParamNames() {return {"distance"};}

    std::string convertToLua()
    {
        return "move( current_object , -" + m_params[0] + ", 0)\n"; 
    }

};

class RightCommand : public CommandObject
{

public:
    RightCommand(std::string t_param = "1",bool t_lockEdit=false,bool t_lockAdd=false): CommandObject(t_lockEdit, t_lockAdd)
    {
        m_name="right";
		setParam(0, t_param);
    }

    ~RightCommand();

    std::vector<std::string> getParamNames() {return {"distance"};}

    std::string convertToLua()
    {
        return "move( current_object , " + m_params[0] + ", 0)\n"; 
    }

};

class UpCommand : public CommandObject
{

public:
    UpCommand(std::string t_param = "1",bool t_lockEdit=false,bool t_lockAdd=false): CommandObject(t_lockEdit, t_lockAdd)
    {
        m_name="up";
		setParam(0, t_param);
    }

    ~UpCommand();

    std::vector<std::string> getParamNames() {return {"distance"};}

    std::string convertToLua()
    {
        return "move( current_object ,  0, -" + m_params[0] + ")\n"; 
    }

};

class DownCommand : public CommandObject
{

public:
    DownCommand(std::string t_param = "1",bool t_lockEdit=false,bool t_lockAdd=false): CommandObject(t_lockEdit, t_lockAdd)
    {
        m_name="down";
		setParam(0, t_param);
    }

    ~DownCommand();

    std::vector<std::string> getParamNames() {return {"distance"};}

    std::string convertToLua()
    {
        return "move( current_object , 0, " + m_params[0] + ")\n";
    }

};