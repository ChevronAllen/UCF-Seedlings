#include "../gameObject.hpp"
#include "../gameManager.hpp"
#include "../resources.h"

class TestObject : public GameObject
{

private:
    m3d::Texture *texture;
    m3d::Sprite *sprite;

public:
    TestObject()
    {
        x = 50;
        y = 200;
        xScale = 2;
        yScale = 2;
        angle = 0;
    }

    ~TestObject()
    {
        texture = NULL;
        delete(sprite);
    }

    void initialize() 
    {
        
        texture = ResourceManager::getTexture("gfx/error.png");
        sprite = new m3d::Sprite();
        sprite->setTexture(*texture);
        sprite->setCenter(10,10);
        sprite->setScale(xScale,yScale);
    }

    void update() {
        
        if(m3d::buttons::buttonDown(m3d::buttons::L))
        {
            angle -= 90 * GameManager::getDeltaTime();
        }
        if(m3d::buttons::buttonDown(m3d::buttons::R))
        {
            angle += 90 * GameManager::getDeltaTime();
        }

        if(m3d::buttons::buttonDown(m3d::buttons::X))
        {
            xScale += 2 * GameManager::getDeltaTime();
        }
        if(m3d::buttons::buttonDown(m3d::buttons::Y))
        {
            yScale += 2 * GameManager::getDeltaTime();
        }

        if(m3d::buttons::buttonDown(m3d::buttons::Right))
        {
            x += 40 * GameManager::getDeltaTime();
        }
        if(m3d::buttons::buttonDown(m3d::buttons::Left))
        {
            x -= 40 * GameManager::getDeltaTime();
        }
        if(m3d::buttons::buttonDown(m3d::buttons::Up))
        {
            y -= 40 * GameManager::getDeltaTime();
        }
        if(m3d::buttons::buttonDown(m3d::buttons::Down))
        {
            y += 40 * GameManager::getDeltaTime();
        }
        sprite->setPosition(x,y);
        sprite->setRotation(angle);
        sprite->setScale(xScale,yScale);
    };
    
    void draw()
    {
        m3d::Screen * screen = GameManager::getScreen();
 
        sprite->setPosition(x,y);
        screen->drawTop(*sprite);

    }

    void destroy(){ this->~TestObject(); }
    void moveTo(double x,double y){};
    void Rotate(double deg){};
};