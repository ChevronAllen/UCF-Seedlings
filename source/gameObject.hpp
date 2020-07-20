/**
 *  @file gameObject.hpp
 *  @brief Defines the GameObject Abstract class
 */


#pragma once
#include "IUpdateable.hpp"

/** 
 *  @def DEFAULT_SIZE
 *  @brief The default size of a GameObject 
 */
#define DEFAULT_SIZE 40 

/** 
 *  @def DEFAULT_COLOR
 *  @brief The default color of a GameObject 
 */
#define DEFAULT_COLOR m3d::Color(255,0,0)

/**
 *  @class GameObject "gameObject.hpp"
 *  @brief The GameObject Class
 *  
 *  Used to encapsulate updatable objects within a @ref Scene.
 *  These objects can be manipulated by the UserAPI.
 */
class GameObject : public Updateable
{
protected:
    double x;   /// Screen relative x-position
    double y;   /// Screen relative y-position
    double target_x;    /// A target x-position, usable for lerped movement
    double target_y;    /// A target y-position, usable for lerped movement
    
    double angle;           /// Angle used to draw the object
    double target_angle;    /// A target angle usable for lerped movement

    double xScale;          /// Horizontal scale of the object
    double target_xScale;   /// A target horizontal scale, uasable for lerped scaling

    double yScale;          /// Vertical scale of the object   
    double target_yScale;   /// A target vertical scale, uasable for lerped scaling

    m3d::Color m_color;     /// Color used to draw the object

public:

    /**
     *  @brief Initializes the GameObject's logical members
     * 
     *  Must be implimented by children
     */
    virtual void initialize() = 0;

    /**
     *  @brief Update the GameObject's logic
     * 
     *  Must be implimented by children
     */
    virtual void update() = 0;

    /**
     *  @brief Draw the GameObject
     * 
     *  Must be implemented by children
     */
    virtual void draw() = 0;

    /**
     *  @brief Destroy the GameObject
     * 
     *  Must be implemented by children. Handles cleaning up memory held by the object
     */
    virtual void destroy()=0;

    /**
     *  @brief Move the GameObject relative to its position
     * 
     *  Must be implimented by children. This function will recieve movement as steps.
     *  @param x [in] relative x movement
     *  @param y [in] relative y movement
     */
    virtual void moveTo(double x,double y)=0;

    /**
     *  @brief Rotate the GameObject relative to its current angle
     * 
     *  Must be implimented by children. This function will recieve movement as steps.
     *  @param deg [in] relative x movement
     */
    virtual void Rotate(double deg)=0;

    /**
     *  @brief Sets the angle 
     * 
     *  @param t_angle new angle
     */
    void setAngle(double t_angle)
    {
        angle = t_angle;
    }

    /**
     *  @brief Get the current angle
     *  @returns value of @ref angle
     */
    double getAngle()
    {
        return angle;
    }

    /**
     *  @brief Set the scale of the object
     * 
     *  May be re-implemented by children to customize behavior
     *  @param t_x new xScale value
     *  @param t_y new yScale value
     */
    virtual void setScale(double t_x, double t_y)
    {
        xScale = t_x;
        yScale = t_y;
    }

    /**
     *  @brief Get the current scale
     *  
     *  May be re-implemented by children to customize behavior
     *  @return a m3d::Vector2f representing the objects scale
     */
    virtual m3d::Vector2f getScale()
    {
        m3d::Vector2f scale;
        scale.u = xScale;
        scale.v = yScale;
        return scale;
    }
    
    /**
     *  @brief Set the Screen position of the object
     *  
     *  @param t_x x-axis component of the new position
     *  @param t_y y-axis component of the new position
     */
    void setPosition(double t_x, double t_y)
    {
        x = t_x;
        y = t_y;
    }

    /**
     *  @brief Get the current position
     *  
     *  @returns an m3d::Vector2f of the postion
     */
    m3d::Vector2f getPosition()
    {
        m3d::Vector2f pos;
        pos.u = x;
        pos.v = y;
        return pos;
    }

    /**
     *  @brief Set a new color
     * 
     *  @param t_color new m3d::Color value
     */
    void setColor(m3d::Color t_color)
    {
        m_color = t_color;
    }

    /**
     *  @brief Get the current color
     * 
     *  @returns value set to @ref m_color
     */
    m3d::Color getColor(); 

    //bool screenIntersect();

};