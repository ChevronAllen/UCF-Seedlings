#pragma once
#include "../commands/commandObject.hpp"

class ColorCommand : public CommandObject
{
protected:
    m3d::Color m_color;
public:
    ColorCommand(std::string t_name , m3d::Color t_color,bool t_lockEdit=false,bool t_lockAdd=false): CommandObject(t_lockEdit, t_lockAdd)
    {
        m_name = t_name;
        m_color = t_color;
    }

    ~ColorCommand();

    std::vector<std::string> getParamNames() {return {};}

    std::string convertToLua()
    {
        return "set_color( current_object, " +   
                            std::to_string( m_color.getRed() )   + ", " +
                            std::to_string( m_color.getGreen() ) + ", " +
                            std::to_string( m_color.getBlue() )  + ", " +
                            std::to_string( m_color.getAlpha() ) + ")\n"; 
    }

};