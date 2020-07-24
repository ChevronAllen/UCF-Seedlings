/**
 *  @file circle.hpp
 *  @brief Defines the Circle Object
 */
#pragma once
#include "gameManager.hpp"
#include "resourceManager.hpp"
#include "gameObjects/gameObject.hpp"

/**
 *  @class CircleObject "gameObjects/circle.hpp"
 *  @brief
 *  
 */
class CircleObject : public GameObject
{

private:

    m3d::Circle* circle;
    m3d::Color color;

    double radius;

public:
    /**
     *  @brief Constructor of the Circle object
     * 
     *  @param t_x,t_y position of the object
     *  @param t_radius radius of the circle
     *  @param t_angle angle of the circle
     *  @param t_color color of the circle
     */
    CircleObject( double t_x = 0, double t_y = 0 , 
                  double t_radius = DEFAULT_SIZE, double t_angle = 0,
                  m3d::Color t_color = DEFAULT_COLOR)
    {
        name = "circle";
        x = t_x;
        y = t_y;
		color = t_color;
		radius = t_radius;
        xScale = t_radius;
        yScale = t_radius;
        angle = t_angle;
        circle = new m3d::Circle(x,y,radius,color);
    }

    ~CircleObject()
    {
        
    }

    void initialize()
    {
        updateShape();
    }

    void update() {}

    void updateShape()
    {
        circle->setPosition(x,y);
        circle->setRadius(xScale);        
        circle->setColor(color);        
    }

    void draw()
    {
        updateShape();
        m3d::Screen * screen = GameManager::getScreen();

        screen->drawTop(*circle);
    
    }

    void destroy()
    { 
        this->~CircleObject(); 
    }
    
    void moveTo(double t_x,double t_y)
    {
        x = t_x;
        y = t_y;
    }

    void Rotate(double deg){};

	BoundingBox getAABB()
	{
		return m3d::BoundingBox(x, y, radius * 2, radius * 2);
	}

	/**
		@brief Overrides the GameObject SetPosition function.
		Keeps the paddle within screen bounds.
	*/
	void setPosition(double t_x, double t_y)
	{
		x = t_x;
		y = t_y;
	}

	/**
		@brief Implement the GameObject setScale function.
		@param t_x X Scale
		@param t_y Y Scale
	*/
	void setScale(double t_x, double t_y)
	{
		xScale = t_x;
		yScale = t_y;

		//Can't change X and Y scales. Would need changed via m3d::Circle
		circle->setRadius(t_x * radius);
	}

	/**
		@brief Implement the GameObject setColor function.
		@param t_color Color to change to
	*/
	void setColor(m3d::Color t_color)
	{
		m_color = t_color;
		circle->setColor(t_color);
	}
};
