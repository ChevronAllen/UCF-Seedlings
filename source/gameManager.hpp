#pragma once
#include <math.h>
#include "time.h"

#include <3ds.h>
#include <m3dia.hpp>

#include "scenes/scene.hpp"
#include "modules/modules.h"
#include "util.hpp"

#define GAMESTATE_DEFAULT 0x1
#define GAMESTATE_MIC 0x2
#define GAMESTATE_CAMERA 0x4



class GameManager
{
private:
    static GameManager * instance;
    
    static m3d::Applet *applet;
    static m3d::Screen *screen;

    time_t lastTime;
    time_t curTime;
    double deltaTime;

    Module *m_module = nullptr;

    GameManager()
    {
        lastTime = curTime = time(NULL);
        deltaTime = 0;
    }

    ~GameManager()
    {
        
    }

    static GameManager* getInstance()
    {
        return instance;
    }

public:
    static m3d::BoundingBox* ScreenBoundsTop;
    static m3d::BoundingBox* ScreenBoundsBottom;


    static void Initialize(m3d::Applet*, m3d::Screen*);
    static void Update();
    static void Draw();

    static double getDeltaTime()
    {
        return (1.0/60.0) ;
    }

    static m3d::Applet* getApplet(){ return applet;}
    static m3d::Screen* getScreen(){ return screen;}

    static void SetModule( Module *t_module);
    static Module* GetModule(){return instance->m_module;}
    static bool IsModuleRunning() {return instance->m_module != nullptr;}

};