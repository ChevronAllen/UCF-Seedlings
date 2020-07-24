#pragma once
#include "gameManager.hpp"
#include "resourceManager.hpp"
#include "gameObjects/gameObject.hpp"

class TextObject : public GameObject
{

private:

    m3dCI::Text* text;
    m3d::Color color;

	int fontSize, fontWeight;

public:
    /**
     *  @brief Constructor of the Text object
     * 
     *  @param t_text text to display
     *  @param t_x,t_y position of the object
     *  @param t_xScale,t_yScale size of the object
     *  @param t_angle angle of the circle
     *  @param t_color color of the circle
     */
    TextObject( std::string t_text = "TEXT", double t_x = 0, double t_y = 0 , 
                     double t_xScale = DEFAULT_SIZE, double t_yScale = DEFAULT_SIZE, double t_angle = 0,
                     m3d::Color t_color = DEFAULT_COLOR)
    {
        name = "text";
        x = t_x;
        y = t_y;
        xScale = t_xScale;
        yScale = t_yScale;
        angle = t_angle;
        color = t_color;

        text = new m3dCI::Text(t_text,color);

		fontSize = text->getFontSize();
		fontWeight = text->getFontWeight();
    }

    ~TextObject()
    {

    }

    void updateShape()
    {
        text->setPosition(x,y);
		text->setFontSize(xScale * fontSize);
		text->setFontWeight(yScale * fontWeight);
        
        text->setColor(color);        
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

        screen->drawTop(*text);
    
    }

    void destroy()
    { 
        this->~TextObject(); 
    }
    
    void moveTo(double t_x,double t_y)
    {
        x = t_x;
        y = t_y;
    }

    void Rotate(double deg){};

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
