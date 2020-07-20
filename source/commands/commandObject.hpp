/**
 *  @file commandObject.hpp
 *  
 *  @brief Defines the CommandObject abstract class and the constant definitions used by it
 */
#pragma once
#include <stdlib.h>
#include <string>
#include <sstream>
#include <vector>

#include <m3dia.hpp>
#include "../m3diaLibCI/sprite.hpp"
#include "../resources.h"
#include "../gameManager.hpp"

#define MAX_PARAMS 3    /** Max number of Parameters per Command */
#define COM_PADDING 3   /** Internal vertical padding of commands */
#define COM_SPACING 5   /** External horizontal margin after parameters */
#define COM_TEXT_COLOR  m3d::Color(0,0,0)   /** Default command text color */
#define COM_LOCK_TINT   m3d::Color(100,100,100,100) /** Tint color of locked commands */
#define COM_SELECTED_TEXT_COLOR  m3d::Color(0,100,0)
#define COM_CLEAR_TINT  m3d::Color(255,255,255) 

/**
 *  @class CommandObject commandObject.hpp "commands/commandObject.hpp"
 *  @brief Abstract Class CommandObject
 *  
 *  Used to provide simple representations of lua commands and operations.\n
 *  Stores parameters as well as parameter names for the code editor, variable type is not needs as lua variables are typeless. 
 *  Each CommandObject will convert to some amount of Lua code via the @ref convertToLua() method, substituting in parameters where needed.  
 */
class CommandObject 
{
private:
    bool m_selected = false;        /** @brief Set true while the CommandObject is selected in the menu */
protected:
    bool m_isEditLocked = false;    /** @brief Set to true if the CommandObject is locked */
    bool m_isAddLocked = false;     /** @brief Set to true if new CommandObject can be added above it */

    /** 
     *  @brief Name of the command  
     *  
     *  Used to draw the name of the CommandObject
     */
    std::string m_name;   

    /**
     *  @brief Array of the CommandObjects current parameter values
     * 
     *  All CommandObjects declare an array of length @ref MAX_PARAMS
    */
    std::string m_params[MAX_PARAMS];
    
    /** @brief Background asset */
    m3dCI::Sprite m_background;

    /** @brief Text asset used to draw @ref m_name and @ref m_params */
	m3dCI::Text* m_text[MAX_PARAMS + 1] = { nullptr, nullptr, nullptr, nullptr };

    /** @brief Lock icon asset */
    m3dCI::Sprite m_lockIcon;

    /** @brief Current tint value, applies to the @ref m_background, while the blending is enabled */
    m3d::Color tint = m3d::Color();

public:

    /**
     *  @brief Initialize a CommandObject
     * 
     *  Each child of CommandObject must be inherit this.
     *  @param t_lockEdit assigned to @ref m_isEditLocked
     *  @param t_lockAdd assigned to @ref m_isAddLocked
     */
    CommandObject(bool t_lockEdit = false,bool t_lockAdd = false)
    {
        m_name="";
        m_isEditLocked = t_lockEdit;
        m_isAddLocked = t_lockAdd;
        m_text[0] = new m3dCI::Text(m_name);
        m_background = m3dCI::Sprite( *ResourceManager::getSprite("command_background.png"));
        m_background.setTint(COM_LOCK_TINT);
        m_lockIcon = m3dCI::Sprite( *ResourceManager::getSprite("command_lock.png"));
        m_lockIcon.setCenter(-108,7);
    }

    ~CommandObject(){}

    /**
     *  @brief returns the names of the CommandObject parameters
     *  
     *  This function is used to detect how many parameters a CommandObject has, 
     *  As well as what name to display on the edit screen.
     *  @returns a list of the parameter names.
     */
    virtual std::vector<std::string> getParamNames() 
    { 
        return  {"error"};
    }

    /**
     *  @brief Get parameter values
     * 
     *  @return returns array of current parameter values
     */
	std::string* getParams()
	{
		return m_params;
	}

    /**
     *  @brief Get the name of the CommandObject
     * 
     *  Useful for identifying command types
     *  @returns m_name
     */
	std::string getName()
	{
		return m_name;
	}
	
    /**
     *  @brief Set a parameter
     * 
     *  @param index index of the parameter from 0 to ( @ref MAX_PARAMS - 1)
     *  @param str new parameter value
     */
	void setParam(int index, std::string str)
	{
		if (str == "")
			return;

		m_params[index] = str;

		if (m_text[index + 1] == nullptr)
		{
			m_text[index + 1] = new m3dCI::Text(str);

			m_text[index + 1]->setColor(COM_TEXT_COLOR);
			m_text[index + 1]->setFontWeight(0.6f);
			m_text[index + 1]->setFontSize(0.6f);
		}

		m_text[index + 1]->setText(str);
	}
    
    /**
     *  @brief Set all parameter values
     * 
     *  @param t_params string array of size @ref MAX_PARAMS
     */
    void setParams(std::string t_params[MAX_PARAMS])
    {
		for (int i = 0; i < MAX_PARAMS; i++)
		{
			m_params[i] = t_params[i];

			if (m_text[i + 1] == nullptr)
			{
				m_text[i + 1] = new m3dCI::Text(t_params[i]);

				m_text[i + 1]->setColor(COM_TEXT_COLOR);
				m_text[i + 1]->setFontWeight(0.6f);
				m_text[i + 1]->setFontSize(0.6f);
			}

			m_text[i + 1]->setText(t_params[i]);
        }
    }

    /**
     *  @brief Translate CommandObject into Lua
     * 
     *  Each child of Command Object should implement its own version.
     *  @warning It's recommended to end the string with a '\\n' character 
     *  @return Lua string
     */
    virtual std::string convertToLua()
    {
        return "";
    }

    /**
     *  @brief Bulk Conversion of Lua commands
     * 
     *  @return Lua string
     */
    static std::string ConvertBulk(std::vector<CommandObject*> t_list)
    {   
        std::stringstream stream;
        for (CommandObject* cmd : t_list)
        {
            stream << /*"if (not IsRunning()) then return end\n" <<*/ cmd->convertToLua() ;
        }
        return stream.str();
    }

    /**
     *  @brief Draws the CommandObject
     * 
     *  Draw the CommandObject using m3d::RenderContext t_context at screen position
     *  ( t_x , t_y ). Both are provided by the @ref m3dCI::CommandLister.
     *  @param t_x x position of the upper-left corner
     *  @param t_y y position of the upper-left corner
     *  @param t_context Render context of the Command
     */
    virtual void draw(double t_x, double t_y, m3d::RenderContext t_context)
    {
        m3d::Screen* scr = GameManager::getScreen();
        unsigned short int paramCount = getParamNames().size();

		m_background.setPosition(t_x, t_y);
        m_lockIcon.setPosition(t_x, t_y);
        if(m_isEditLocked)
        {
            m_background.setBlend(0.5f);
        }else
        {
            m_background.setBlend(0.f);
        }
        m_background.draw(t_context);
		

        if(m_isAddLocked)
        {
            m_lockIcon.draw(t_context); 
        }


        m_text[0]->setText(m_name);
        m_text[0]->setColor(m_selected? COM_SELECTED_TEXT_COLOR:COM_TEXT_COLOR);
        m_text[0]->setFontWeight(0.6f);
		m_text[0]->setFontSize(0.6f);

		int t_yCursor = t_y + COM_PADDING - 3;
		int t_xCursor = COM_PADDING + 12;

		m_text[0]->setPosition(t_xCursor, t_yCursor);
		m_text[0]->draw(t_context);

		t_xCursor += m_text[0]->getWidth() + (2 * COM_SPACING);

        int t_paramStartX = t_xCursor - COM_SPACING;

        for (unsigned int i = 1; i < paramCount + 1; i++)
        {
            if(m_text[i] != nullptr)
            {
				m_text[i]->setColor(m_selected ? COM_SELECTED_TEXT_COLOR : COM_TEXT_COLOR);
				m_text[i]->setPosition(t_xCursor, t_yCursor);
                m_text[i]->draw(t_context);
                t_xCursor += m_text[i - 1]->getWidth() + COM_SPACING;
            }
        }

        
    }

    /**
     *  @brief Get edit lock state
     *  @returns value of m_isEditLocked
     */
	bool IsEditLocked()
	{
		return m_isEditLocked;
	}

    /**
     *  @brief Get add lock state
     *  @returns value of m_isAddLocked
     */
	bool IsAddlocked()
	{
		return m_isAddLocked;
	}

    void setSelected(bool selected)
    {
		m_selected = selected;
    }
};

