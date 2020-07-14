#pragma once
#include "3ds.h"
#include <m3dia.hpp>
#include "../modules/module.hpp"
#include "../m3diaLibCI/sprite.hpp"
#include "../util.hpp"

class CameraModule : public Module
{
public:
    CameraModule(std::function<void(m3dCI::Sprite*)> callback);
    ~CameraModule();
    void onDraw();

protected:
    void Before();
    void During();

private:
    u8 * m_buffer;
    const int SCREEN_WIDTH = 400;
    const int SCREEN_HEIGHT = 240;
    void writePictureToFramebufferRGB565(void *fb, void *img, u16 x, u16 y, u16 width, u16 height);
};