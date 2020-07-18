#pragma once
#include "../commands/commandObject.hpp"

class RectangleCommand : public CommandObject
{

public:
    RectangleCommand(std::string t_x = "0", std::string t_y = "0",bool t_lockEdit=false,bool t_lockAdd=false): CommandObject(t_lockEdit, t_lockAdd)
    {
        m_name="rect";
		setParam(0, t_x);
		setParam(1, t_y);
        m_background = m3dCI::Sprite( *ResourceManager::getSprite("command_background_instance.png"));
        m_background.setTint(COM_LOCK_TINT);
    }

    ~RectangleCommand();

    std::vector<std::string> getParamNames() {return {"x", "y"};}

    std::string convertToLua()
    {
        return "make_rectangle(" + m_params[0] + ", " +  m_params[1] +  ")\n"; 
    }

};

class CircleCommand : public CommandObject
{

public:
    CircleCommand(std::string t_x = "0", std::string t_y = "0",bool t_lockEdit=false,bool t_lockAdd=false): CommandObject(t_lockEdit, t_lockAdd)
    {
        m_name="circle";
		setParam(0, t_x);
		setParam(1, t_y);
        m_background = m3dCI::Sprite( *ResourceManager::getSprite("command_background_instance.png"));
        m_background.setTint(COM_LOCK_TINT);
    }

    ~CircleCommand();

    std::vector<std::string> getParamNames() {return {"x", "y"};}

    std::string convertToLua()
    {
        return "make_circle(" + m_params[0] + ", " +  m_params[1] +  ")\n"; 
    }

};

class TextCommand : public CommandObject
{

public:
    TextCommand(std::string t_text = "text", std::string t_x = "0", std::string t_y = "0", bool t_lockEdit=false,bool t_lockAdd=false): CommandObject(t_lockEdit, t_lockAdd)
    {
        m_name="text";
		//setParams(new std::string[3]{ t_x, t_y, t_text });
        setParam(0, t_text);
        m_background = m3dCI::Sprite( *ResourceManager::getSprite("command_background_instance.png"));
        m_background.setTint(COM_LOCK_TINT);
    }

    ~TextCommand();

    std::vector<std::string> getParamNames() {return {"Text"};}

    std::string convertToLua()
    {
        Util::PrintLine("make_text( 0, 0, " + m_params[0] + ")");
        return "make_text( 0, 0, " + m_params[0] + ")\n"; 
    }

};

class VarCommand : public CommandObject
{

public:
    VarCommand(std::string t_name = "text", std::string t_value = "nil", bool t_lockEdit=false,bool t_lockAdd=false): CommandObject(t_lockEdit, t_lockAdd)
    {
        m_name="var";
		setParam(0, t_name);
        setParam(1,t_value);
        m_background = m3dCI::Sprite( *ResourceManager::getSprite("command_background_var.png"));
        m_background.setTint(COM_LOCK_TINT);
    }

    ~VarCommand();

    std::vector<std::string> getParamNames() {return {"Name ","Value"};}

    std::string convertToLua()
    {
        return  m_params[0] + " = " + m_params[1] + "\n"; 
    }
};