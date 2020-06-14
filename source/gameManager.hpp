#pragma once
#include "time.h"

#include <3ds.h>
#include <m3dia.hpp>

#include "scene.hpp"



class GameManager
{
private:
    static GameManager * instance;
    
    m3d::Applet *applet;
    m3d::Screen *screen;

    time_t lastTime;
    time_t curTime;
    double deltaTime;

    GameManager()
    {
        applet = new m3d::Applet();
        screen = new m3d::Screen();
        lastTime = curTime = time(NULL);
        deltaTime = 0;
    }

    ~GameManager()
    {
        
    }

    static GameManager* getInstance()
    {
        if(instance == NULL){
            Initialize();
        }

        return instance;
    }

public:
    static m3d::BoundingBox* ScreenBoundsTop;
    static m3d::BoundingBox* ScreenBoundsBottom;


    static void Initialize();
    static void Update();
    static double getDeltaTime()
    {
        return (1.0/60.0) ;
    }

    static m3d::Applet* getApplet(){return getInstance()->applet;}
    static m3d::Screen* getScreen(){return getInstance()->screen;}

    

};