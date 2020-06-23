#pragma once
#include <math.h>

//#include "core.h"
#include "gameManager.hpp"
#include "util.hpp"

m3d::BoundingBox* GameManager::ScreenBoundsTop = NULL;
m3d::BoundingBox* GameManager::ScreenBoundsBottom = NULL;
GameManager* GameManager::instance = NULL;
m3d::Applet* GameManager::applet = nullptr;
m3d::Screen* GameManager::screen = nullptr;

void GameManager::Initialize(m3d::Applet* t_applet, m3d::Screen* t_screen )
{
    if(instance == NULL)
    {
        instance = new GameManager();
    }

    //if(applet == nullptr){ applet = new m3d::Applet(); }
    //if(screen == nullptr){ screen = new m3d::Screen(false); }
    applet = t_applet;
    screen = t_screen;
    
    ScreenBoundsTop = new m3d::BoundingBox(0,0,400,240);
    ScreenBoundsBottom = new m3d::BoundingBox(40,241,320,240);
}

void GameManager::Update()
{
    getInstance();

    instance->lastTime = instance->curTime;
    instance->curTime = time(0);
    instance->deltaTime = abs( difftime(instance->lastTime, instance->curTime));
    
    if (buttonDown(m3d::buttons::Button::Start) && buttonDown(m3d::buttons::Button::Select))
    {
        //instance->applet->exit();
    }
	
}

