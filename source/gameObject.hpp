#pragma once
#include "IUpdateable.hpp"

#define DEFAULT_SIZE 40 
#define DEFAULT_COLOR m3d::Color(255,0,0)

class GameObject : public Updateable
{
protected:
    double x;
    double y;
    double target_x;
    double target_y;
    
    double angle;
    double target_angle;

    double xScale;
    double target_xScale;

    double yScale;
    double target_yScale;

    m3d::Color m_color;

public:
    virtual void initialize() = 0;
    virtual void update() = 0;
    virtual void draw() = 0;

    virtual void destroy()=0;
    virtual void moveTo(double x,double y)=0;
    virtual void Rotate(double deg)=0;

    void setAngle(double _angle)
    {
        angle = _angle;
    }
    double getAngle()
    {
        return angle;
    }

    virtual void setScale(double _x, double _y)
    {
        xScale = _x;
        yScale = _y;
    }
    m3d::Vector2f getScale()
    {
        m3d::Vector2f scale;
        scale.u = xScale;
        scale.v = yScale;
        return scale;
    }

    void setPosition(double _x, double _y)
    {
        x = _x;
        y = _y;
    }
    m3d::Vector2f getPosition()
    {
        m3d::Vector2f pos;
        pos.u = x;
        pos.v = y;
        return pos;
    }

    void setColor(m3d::Color);
    m3d::Color getColor();

    bool screenIntersect();

};