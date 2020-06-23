#include "../gameObject.hpp"
#include "../gameManager.hpp"
#include "../resources.h"

class TerminalObject : public GameObject
{

private:
    m3d::Texture *texture;
    m3d::Sprite *sprite;

public:
    TerminalObject()
    {
        x = 10;
        y = 0;
        xScale = 1;
        yScale = 1;
        angle = 0;
    }

    ~TerminalObject()
    {
        texture = NULL;
    }

    void initialize()
    {

        texture = ResourceManager::loadTexture("gfx/Terminal.png");
        sprite = new m3d::Sprite();
        sprite->setTexture(*texture);
        sprite->setScale(xScale,yScale);
        sprite->setPosition(x,y);
    }

    void update() {

        if(m3d::buttons::buttonPressed(m3d::buttons::Right))
        {
            x += 10;
        }
        if(m3d::buttons::buttonPressed(m3d::buttons::Left))
        {
            x -= 10;
        }
        if(m3d::buttons::buttonPressed(m3d::buttons::Up))
        {
            y -= 10;
            if(y<0)
            {
              y=0;
            }
        }
        if(m3d::buttons::buttonPressed(m3d::buttons::Down))
        {
            y += 10;
            if(y>230)
            {
              y=230;
            }

        }
        sprite->setPosition(x,y);

    };

    void draw()
    {
        m3d::Screen * screen = GameManager::getScreen();
        screen->drawTop(*sprite);
    }

    void destroy(){ this->~TerminalObject(); }
    void moveTo(double x,double y){};
    void Rotate(double deg){};
};
