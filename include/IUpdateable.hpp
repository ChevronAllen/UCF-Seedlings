/**
 *  @file IUpdateable.hpp
 */
#pragma once
#include <3ds.h>
#include <m3dia.hpp>

/**
 *  @class Updatable "IUpdateable.hpp"
 *  @brief Abstract Updatable Class
 * 
 *  Used for classes which need to be calls and referenced on mass in the game loop
 */
class Updateable
{
    public:
    virtual void initialize() = 0;
    virtual void update() = 0;
    virtual void draw() = 0;
};