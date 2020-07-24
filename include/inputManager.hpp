#pragma once
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <malloc.h>
#include <math.h>

#include "3ds.h"
#include <m3dia.hpp>

#define TOUCH_SAMPLES 10
#define TOUCH_EPSILON 5

class Input
{
private:

    bool _micInitialized;

    
    u32 _micbuf_size;
    u32 _micbuf_pos; 
    u8* _micbuf;

    u32 _micbuf_datasize;
    u32 _audiobuf_size;
    u32 _audiobuf_pos;
    u8* _audiobuf;

    /**
     *  @brief Stores locations of touches.
     * 
     *  _touchStates[0] is the origin of each drag. If there is no drag stored the current touch location\n
     *  _touchStates[1] the end point of the drag. If there is a drag stores the current touch location
     */
    m3d::Vector2f* _touchStates[2]; 

    /**
     *  @brief Stores the vector difference between both touch states.
     */
    m3d::Vector2f _touchDragDistance;

    /**
     *  @brief Stores the dragging state
     */
    bool _touchIsDragging;


    static Input* _instance;
    static Input* getInstance()
    {
        if(_instance == nullptr)
        {
            initialize();
        }
        return _instance;
    }
    Input(){}
    ~Input(){}

public:
    /**
     *  @brief Initialize the InputManager
     *  
     *  Initialize the Input Manager creating a new instance. This should only be called once in the app
     */
    static void initialize();

    /**
     *  @brief Update the InputManager
     * 
     *  During update the manager reads peripherals and updates their status, performing checks on their status.
     *  Should be at the start of each update cycle, before any accesses to the InputManager
     */
    static void update();

    /**
     *  @brief Check the state of a button
     * 
     *  @param btn 32-bit flag representation of the button
     *  @returns true if the button is active, false otherwise.
     */
    static bool btn( m3d::buttons::Button btn);
    
    /**
     *  @brief Check if a button has been pressed
     * 
     *  @param btn 32-bit flag representation of the button
     *  @returns true is the button is active this frame, but inactive in the last.
     *  false otherwise.
     */
    static bool btnPressed( m3d::buttons::Button btn);
    
    /**
     *  @brief Check if a button has been released
     * 
     *  @param btn 32-bit flag representation of the button
     *  @returns true if the button is inactive this frame, but active in the last.
     *  false otherwise.
     */
    static bool btnReleased( m3d::buttons::Button btn);

    /**
     *  @brief gets the state of the circle pad
     * 
     *  @returns floating point 2D vector of the circlepad position, with center as the origin.
     */
    static m3d::Vector2f* getCirclePad();

    /**
     *  @brief Reads the volume slider level
     * 
     *  @returns volume as an integer in the range [0 - 63]
     */
    static unsigned short int getVolume();

    /**
     *  @brief Tests for a touch, and returns the screen position
     * 
     *  @return If a touch is detected returns a vector2 with u=x and v=y. 
     *  Values are relative to the upperleft corner of the touch screen. If no touch was detected both axis are < 0
     */
    static m3d::Vector2f* touch();

    /**
     *  @todo hook to a module
     */
    static void recordMic(m3d::Parameter);
    
    /**
     *  @brief Reads the last addition to the micstream; the bytes inserted since the last frame.
     * 
     *  @todo  return a single sample of the microphone input
     */
    static void readMic();


    /**
     *  @brief Read Gyroscope 
     *  
     *  The gyroscope projects the rotation of the device along 3 axes
     *  @returns three axes of rotation: x,y,z
     */
    static m3d::Vector3f* getGyroscope();

    /**
     *  @brief Read the Accelerometer
     * 
     *  The accelerometer projects movement of the device along 3 axes
     *  @returns three axes of motion: x,y,z
     */
    static m3d::Vector3f* getAccelerometer();

    /**
     *  @brief Read a Drag
     * 
     *  Reads the distance of a drag, as a vector from the origin of the drag.\n
     *  distance vector of the touch from the tap on the screen.
     *  @returns The translation vector of a drag on the screen. {0,0} if a drag isnt active
     */
    static m3d::Vector2f getTouchDragVector();

    /**
     *  @brief Is the User Dragging on the touch screen
     * 
     *  If a touch continues and moves further than @ref TOUCH_EPSILON from the origin of the touch  
     *  @returns true if the user is dragging. false otherwise.
     */
    static bool isTouchDragging(){ return _instance->_touchIsDragging;}
    
    /**
     *  @brief Origin of the Drag
     *  
     *  @returns The origin point of a drag. Otherwise returns nullptr.
     */
    static m3d::Vector2f* getTouchDragOrigin();

};