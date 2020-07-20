#include "../gameObject.hpp"
#include "../gameManager.hpp"
#include "../resources.h"

class TextObject : public GameObject
{

private:

    m3dCI::Text* text;
    m3d::Color color;

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
        x = t_x;
        y = t_y;
        xScale = t_xScale;
        yScale = t_yScale;
        angle = t_angle;
        color = t_color;
        text = new m3dCI::Text(t_text,color);
    }

    ~TextObject()
    {

    }

    void updateShape()
    {
        text->setPosition(x,y);
        //text->setHeight(yScale);
        //text->setWidth(xScale);
        
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
};
