#include "gameObject.hpp"
#include "gameManager.hpp"
#include "resourceManager.hpp"

class TriangleObject : public GameObject
{

private:

    m3d::Triangle* triangle;
    m3d::Color color;

    double radius;

public:
    TriangleObject( double t_x = 0, double t_y = 0 , 
                  double t_length = DEFAULT_SIZE, double t_angle = 0,
                  m3d::Color t_color = DEFAULT_COLOR)
    {
        name = "triangle";
        x = t_x;
        y = t_y;
        xScale = t_length;
        yScale = t_length;
        angle = t_angle;
        triangle = new m3d::Triangle(x,y,x,y,x,y,color);
    }

    ~TriangleObject()
    {
        
    }

    // TODO: Untested
    void updateShape()
    {   
        double theta = fmod(90 + angle,360);

        triangle->setX1Pos( x + xScale * cos(theta) );
        triangle->setY1Pos( y + yScale * sin(theta) );

        theta = fmod((theta + 120), 360);
        triangle->setX2Pos( x + xScale * cos(theta) );
        triangle->setY2Pos( y + yScale * sin(theta) );
        
        theta = fmod((theta + 120) , 360);
        triangle->setX3Pos( x + xScale * cos(theta) );
        triangle->setY3Pos( y + yScale * sin(theta) );

        triangle->setColor(color);        
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

        screen->drawTop(*triangle);
    
    }

    void destroy()
    { 
        this->~TriangleObject(); 
    }
    
    void moveTo(double t_x,double t_y)
    {
        x = t_x;
        y = t_y;
    }

    void Rotate(double deg){};

	BoundingBox getAABB()
	{
		//TODO
		return BoundingBox(-1, -1, -1, -1);
	}
};
