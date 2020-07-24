/**
 *  @file TTT_Token.hpp
 *  @brief Defines the Tic-Tac-Toe Tokens
 */
#pragma once
#include <math.h>
#include "gameManager.hpp"
#include "resourceManager.hpp"
#include "scenes/TTT_config.h"
#include "gameObjects/gameObject.hpp"

/**
 *  @class TTT_X "gameObjects/circle.hpp"
 *  @brief
 *  
 */
class TTT_Token : public GameObject
{

private:

    m3dCI::Sprite* m_sprite;

public:
    /**
     *  @brief Constructor of the Circle object
     * 
     *  @param t_x,t_y position of the object
     *  @param t_radius radius of the circle
     *  @param t_angle angle of the circle
     *  @param t_color color of the circle
     */
    TTT_Token(bool t_cross = true, int t_row = 0, int t_col = 0 , 
                double t_angle = 0, m3d::Color t_color = DEFAULT_COLOR)
    {
        
        name = t_cross ? "X" : "O";
        x = TTT_X + (std::min( 3,std::max(0, t_row-1)) * TTT_CELL_SIZE);
        y = TTT_Y + (std::min( 3,std::max(0, t_col-1)) * TTT_CELL_SIZE);
        xScale = 1;
        yScale = 1;
        angle = t_angle;
        m_color = t_color;
        m_sprite = new m3dCI::Sprite( *(ResourceManager::getSprite( (t_cross) ? "TTT_X.png":"TTT_O.png" )) );
        
        #ifdef DEBUG_GAMEOBJECT
        Util::PrintLine("created new " + name + " at " + std::to_string(x) + ", " + std::to_string(y));
        #endif
    }

    ~TTT_Token()
    {
        if(m_sprite != nullptr)
        {
            delete m_sprite;
        }
    }

    void initialize()
    {
        
    }

    void update() {}

    m3d::BoundingBox getAABB()
    {
        return m3d::BoundingBox(x,y,TTT_DETECTOR_SIZE,TTT_DETECTOR_SIZE);
    }

    void draw()
    {
        
        m3d::Screen * screen = GameManager::getScreen();

        if(m_sprite != nullptr)
        {
            m_sprite->setPosition(x,y);
            m_sprite->setRotation(angle);
            screen->drawTop(*m_sprite);    
        }
    }

    void destroy()
    { 
        this->~TTT_Token(); 
    }
    
    void moveTo(double t_x,double t_y)
    {
        x = t_x;
        y = t_y;
    }

};
