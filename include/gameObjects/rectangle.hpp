/**
 *  @file rectangle.hpp
 */
#pragma once
#include "gameManager.hpp"
#include "resourceManager.hpp"
#include "gameObjects/gameObject.hpp"

/**
 *  @class RectangleObject "gameObject/rectangle.hpp"
 *  @brief Filled Rectangle 
 * 
 */
class RectangleObject : public GameObject
{

private:

    m3d::Rectangle* box;
    m3d::Color color;
	int width, height;

public:
    /**
     *  @brief Constructor of the Rectangle object
     * 
     *  @param t_x, t_y position of the object
     *  @param t_width, Width size of the object
     *  @param t_height, Height size of the object
     *  @param t_angle angle of the circle
     *  @param t_color color of the circle
     */
    RectangleObject( double t_x = 0, double t_y = 0 , 
                     double t_width = DEFAULT_SIZE, double t_height = DEFAULT_SIZE, double t_angle = 0,
                     m3d::Color t_color = DEFAULT_COLOR)
    {
        name = "rectangle";
        x = t_x;
        y = t_y;
        width = t_width;
        height = t_height;
        angle = t_angle;
        color = t_color;

		xScale = 1;
		yScale = 1;

        box = new m3d::Rectangle(x,y,xScale,yScale,color);
    }

    ~RectangleObject()
    {

    }

    void updateShape()
    {
        box->setPosition(x,y);
        box->setHeight(yScale);

		box->setWidth(width * xScale);
		box->setHeight(height * yScale);
        
        box->setColor(color);        
    }

    void initialize()
    {
        updateShape();
    }

    void update() {


    }

    void draw()
    {
        updateShape();
        m3d::Screen * screen = GameManager::getScreen();

        screen->drawTop(*box);
    
    }

    void destroy()
    { 
        this->~RectangleObject(); 
    }
    
    void moveTo(double t_x,double t_y)
    {
        x = t_x;
        y = t_y;
    }

    void Rotate(double deg){};

	BoundingBox getAABB()
	{
		return m3d::BoundingBox(x, y, box->getWidth(), box->getHeight());
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
	}

	/**
		@brief Implement the GameObject setColor function.
		@param t_color Color to change to
	*/
	void setColor(m3d::Color t_color)
	{
		m_color = t_color;
	}
};
