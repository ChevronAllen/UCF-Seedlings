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
public:

	/**
	 *  @brief Structure used to hold all data needed for a set of audio.
	 *  @param psize -> Size of the audio buffer
	 *  @param linear -> Type of memory allocation. true uses linearAlloc, false uses memalign
	 */
	struct AudioData
	{
		u32 size = 0,
			pos = 0;
		u8* buffer = nullptr;

		//default left for blank constructors
		AudioData()
		{

		}

		AudioData(u32 psize, bool linear = false)
		{
			size = psize;
			if (psize != 0x0)
			{
				if (linear)
					buffer = static_cast<u8*>(linearAlloc(size));
				else
					buffer = static_cast<u8*>(memalign(0x1000, size));
			}
		}
	};
private:

    bool _micInitialized;
    
	AudioData _micbuf;
	AudioData _recordingbuf;

    u32 _micbuf_datasize;

    m3d::Vector2f* _touchStates[2];
    m3d::Vector2f _touchDragDistance;
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
     *  Initialize the Input Manager creating a new instance. This should only be called once in the app
     */
    static void initialize();

    /**
     *  Updates the Input Manager, during update the manager reads peripherals and updates their status.
     *  performing checks on their status.
     *  Should be at the start of each update cycle, before any accesses to Input
     */
    static void update();

    /**
     *  @brief 
     *  @returns 
     */
    static bool btn( m3d::buttons::Button );
    
    /**
     *  @brief 
     *  @returns 
     */
    static bool btnPressed( m3d::buttons::Button );
    
    /**
     *  @brief 
     *  @returns 
     */
    static bool btnReleased( m3d::buttons::Button );

    /**
     *  @brief 
     *  @returns 
     */
    static m3d::Vector2f* getCirclePad();

    /**
     *  @brief reads the volume slider level
     *  @returns volume level from 0 - 63
     */
    static unsigned short int getVolume();

    /**
     *  @brief tests for a touch, and returns the screen position
     *  @return if a touch is detected returns a vector2 with u=x,v=u. If no touch was detected both axis are < 0
     */
    static m3d::Vector2f* touch();

    /**
     *  @brief 
     *  @returns 
     */
    static m3d::Vector2f* getGyroscope();

    /**
     *  @brief 
     *  @returns 
     */
    static m3d::Vector3f* getAccelerometer();

    /**
     *  @brief 
     *  @returns 
     */
    static m3d::Vector2f getTouchDragVector();

    /**
     *  @brief 
     *  @returns 
     */
    static bool isTouchDragging(){ return _instance->_touchIsDragging;}
    
    /**
     *  @returns if touch is dragging, returns a Vector2f pointer. Otherwise returns nullptr.
     */
    static m3d::Vector2f* getTouchDragOrigin();

	/**
	 *  @brief Records input from the Mic until stopRecordMic() is called or the buffer limit is hit
	 *  @returns Returns if it was able to begin recording or not
	 */
	static bool recordMic();

	/**
	 *  @brief Checks if the microphone data is being recorded
	 *  @returns if the mic is being recorded
	 */
	static bool isMicRecording();

	/**
	 *  @brief Ends the microphone recording if one was active
	 *  @returns the captured audio from the recording
	 */
	static AudioData stopMicRecording();

	/**
	 *  @brief Plays the entire Microphone Recoring back
     *  @param data -> The audio track to play
	 *  @returns if it was successfully able to start the audio playback.
	 */
	static bool playAudio(AudioData data);

	/**
	 *  @brief Detects the end of a audio track
	 *  @returns if the current playback has completed (true) or if there is more in the buffer (false)
	 */
	static bool reachedEndOfPlayback();
};