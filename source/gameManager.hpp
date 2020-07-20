/**
 *  @file gameManager.hpp
 *  @brief Defines the @ref GameManager class
 */
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
    
    static GameManager * instance; /// Current GameManager Instance
    

    static m3d::Applet *applet; /// Current Applet
    static m3d::Screen *screen; /// Current Screen

    time_t lastTime;    /**  Last captured timeslot */
    time_t curTime;     /**  Current timestamp */
    double deltaTime;   /**  Difference between @ref lastTime and @ref curTime in seconds*/

    Module *m_module = nullptr;

    GameManager()
    {
        lastTime = curTime = time(NULL);
        deltaTime = 0;
    }

    ~GameManager()
    {
        
    }

    /**
     *  @brief Get the current GameManager instance
     *  @returns pointer to the instance
     */
    static GameManager* getInstance()
    { 
        return instance;
    }

public:
    /**Bounding Box of the top screen */
    static m3d::BoundingBox* ScreenBoundsTop;
    /**Bounding Box of the bottom screen */
    static m3d::BoundingBox* ScreenBoundsBottom;

    /**
     *  @brief Initialize The GameManager
     *  
     *  @param t_applet pointer to the Main applet
     *  @param t_screen pointer to the Main Screen Object
     */
    static void Initialize(m3d::Applet* t_applet, m3d::Screen* t_screen);

    /**
     *  @brief Update GameManager members
     */
    static void Update();
    static void Draw();
    
    /**
     *  @brief Get the time difference since the last frame
     *  
     *  @returns return @ref deltaTime
     */
    static double getDeltaTime()
    {
        return (1.0/60.0) ;
    }

    /**
     *  @return returns pointer to the stored m3d::Applet
     */
    static m3d::Applet* getApplet(){ return applet;}
    
    /**
     *  @return returns pointer to the stored m3d::Screen
     */
    static m3d::Screen* getScreen(){ return screen;}

    static void SetModule( Module *t_module);
    static Module* GetModule(){return instance->m_module;}
    static bool IsModuleRunning() {return instance->m_module != nullptr;}

};