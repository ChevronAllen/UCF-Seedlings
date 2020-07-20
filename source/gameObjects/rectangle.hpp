/**
 *  @file rectangle.hpp
 */
#include "../gameObject.hpp"
#include "../gameManager.hpp"
#include "../resources.h"

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

public:
    /**
     *  @brief Constructor of the Rectangle object
     * 
     *  @param t_x,t_y position of the object
     *  @param t_xScale,t_yScale size of the object
     *  @param t_angle angle of the circle
     *  @param t_color color of the circle
     */
    RectangleObject( double t_x = 0, double t_y = 0 , 
                     double t_xScale = DEFAULT_SIZE, double t_yScale = DEFAULT_SIZE, double t_angle = 0,
                     m3d::Color t_color = DEFAULT_COLOR)
    {
        x = t_x;
        y = t_y;
        xScale = t_xScale;
        yScale = t_yScale;
        angle = t_angle;
        color = t_color;
        box = new m3d::Rectangle(x,y,xScale,yScale,color);
    }

    ~RectangleObject()
    {

    }

    void updateShape()
    {
        box->setPosition(x,y);
        box->setHeight(yScale);
        box->setWidth(xScale);
        
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
};
