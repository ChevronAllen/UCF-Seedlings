#pragma once
#include <3ds.h>
#include <m3dia.hpp>

class Updateable
{
    public:
    virtual void initialize() = 0;
    virtual void update() = 0;
    virtual void draw() = 0;
};