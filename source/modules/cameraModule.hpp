/**
 *  @file defines the cameraModule
 *  The camera module provides an interface for users to preview the camera feed before taking a photo.
 *  This can be used in Minigames giving users fun ways to interact with games.
 */
#pragma once
#include <sstream>
#include "3ds.h"
#include <m3dia.hpp>
#include <png.h>
#include "../modules/module.hpp"
#include "../m3diaLibCI/sprite.hpp"
#include "../m3diaLibCI/texture.hpp"
#include "../util.hpp"

class CameraModule : public Module
{
public:
    /**
     *  @brief Camera Module Constructor
     *  @param t_callback a callback function to be called once the user takes a picture.
     */
    CameraModule(std::function<void(m3dCI::Sprite*)> t_callback);
    ~CameraModule();
    void onDraw();

protected:
    void initialize();
    void updateActions();

private:
    
    const int SCREEN_WIDTH = 400; // Width of the image
    const int SCREEN_HEIGHT = 240; // Height of the image
    const int SCREEN_SIZE = SCREEN_WIDTH * SCREEN_HEIGHT * 2; // Total area of a stereoscopic image
    
    u8 * m_buffer;
    u32 m_bufferSize;
    unsigned int m_camHandle;
    Handle m_camReceiveEvent = 0;
    std::function<void(m3dCI::Sprite*)> m_callback;
	
    C2D_Image m_image;
    C3D_Tex m_tex;


    void writePictureToFramebufferRGB565(void *fb, void *img, u16 x, u16 y, u16 width, u16 height);
    bool loadPng(const void* t_fp, bool t_buffer);
};