#include "inputManager.hpp"

    Input* Input::_instance = nullptr;
    
    void Input::initialize()
    {
        if(_instance == nullptr)
        {
            _instance = new Input();
        }
        
        HIDUSER_EnableGyroscope();          //  Enable Gyroscope
        HIDUSER_EnableAccelerometer();      //  Enable Accellerometer

        // Microphone Stream
        _instance->_micbuf_size = 0x30000;
        _instance->_micbuf_pos = 0; 
        _instance->_micbuf = static_cast<u8*>(memalign(0x1000, _instance->_micbuf_size));

        std::cout << "Initializing CSND...\n";
        if(R_FAILED(csndInit()))
        {
            _instance->_micInitialized = false;
            std::cout << "Could not initialize CSND.\n";
        } else std::cout << "CSND initialized.\n";

        std::cout << "Initializing MIC...\n";
        
        if(R_FAILED(micInit(_instance->_micbuf, _instance->_micbuf_size)))
        {
            _instance->_micInitialized = false;
            std::cout << "Could not initialize MIC.\n";
        } else std::cout << "MIC initialized.\n";
        
        _instance->_micbuf_datasize = micGetSampleDataSize();
        _instance->_audiobuf_size = 0x100000;
        _instance->_audiobuf_pos = 0;
        _instance->_audiobuf = static_cast<u8*>(linearAlloc(_instance->_audiobuf_size));

        _instance->_touchStates[0] = nullptr; 
        _instance->_touchStates[1] = nullptr; 
        
    }

    void Input::update()
    {
        touchPosition tpos;  
        hidTouchRead(&tpos);



       

        if(m3d::buttons::buttonPressed(m3d::buttons::Touch))
        {
            if(_instance->_touchStates[0] == nullptr)
            {
                _instance->_touchStates[0] = new m3d::Vector2f(); 
            }
            _instance->_touchStates[0]->u = tpos.px; 
            _instance->_touchStates[0]->v = tpos.py;

        }
        
        if(m3d::buttons::buttonDown(m3d::buttons::Touch))
        {
            if(_instance->_touchStates[1] == nullptr)
            {
                _instance->_touchStates[1] = new m3d::Vector2f(); 
            }
            _instance->_touchStates[1]->u = tpos.px; 
            _instance->_touchStates[1]->v = tpos.py;

            float dx = _instance->_touchStates[1]->u - _instance->_touchStates[0]->u;
            float dy = _instance->_touchStates[1]->v - _instance->_touchStates[0]->v;

            if(_instance->_touchIsDragging == false)
            {
                _instance->_touchDragDistance= {dx,dy};
                
                m3d::Vector2f dist =  {dx,dy};
                _instance->_touchIsDragging = sqrt( pow(dist.u,2) + pow(dist.v,2)) >= TOUCH_EPSILON;
            }
            
            _instance->_touchDragDistance= {dx,dy};

        }

        if(m3d::buttons::buttonReleased(m3d::buttons::Touch))
        {   
            _instance->_touchStates[0] = nullptr;
            _instance->_touchStates[1] = nullptr;

            _instance->_touchIsDragging = false;
        }
        
    }
    
    bool Input::btn(m3d::buttons::Button b) { return m3d::buttons::buttonDown(b); }
    bool Input::btnPressed(m3d::buttons::Button b) { return m3d::buttons::buttonPressed(b); }
    bool Input::btnReleased(m3d::buttons::Button b) { return m3d::buttons::buttonReleased(b); }

    m3d::Vector2f* Input::touch()
    {
        m3d::Vector2f* vector = new m3d::Vector2f();
        vector->u = -1;
        vector->v = -1;

        if(Input::btn(m3d::buttons::Touch))
        {
            vector->u = m3d::touch::getXPosition();
            vector->v = m3d::touch::getYPosition();
        }

        return vector;
    }

    m3d::Vector2f* Input::getGyroscope()
    {
        m3d::Vector2f* rate = new m3d::Vector2f();
        angularRate* vec = new angularRate();
        hidGyroRead(vec);

        rate->u = vec->x;
        rate->v = vec->y;

        return rate;
    }

    m3d::Vector3f* Input::getAccelerometer()
    {
        m3d::Vector3f* rate = new m3d::Vector3f();
        accelVector* vec = new accelVector();

        hidAccelRead(vec);
        rate->x = vec->x;
        rate->y = vec->y;
        rate->z = vec->z;

        return rate;
    }

    m3d::Vector2f* Input::getCirclePad()
    {
        m3d::Vector2f* vector = new m3d::Vector2f();
        circlePosition* pos = new circlePosition();

        hidCircleRead(pos);

        vector->u = pos->dx;
        vector->v = pos->dy;

        return vector;
    }

    unsigned short int Input::getVolume()
    {
        u8 volume;
        
        HIDUSER_GetSoundVolume(&volume);

        return volume;

    }
    
    void Input::recordMic(m3d::Parameter param)
    {
        double length = param.get<double>();
        MICU_StartSampling(MICU_ENCODING_PCM16_SIGNED, MICU_SAMPLE_RATE_16360, 0, _instance->_micbuf_datasize, true);
        
        while(length > 0)
        {
            
            length -= 0.001;
        }

        MICU_StopSampling();
    }

    m3d::Vector2f Input::getTouchDragVector()
    {
        if (getInstance()->_touchStates[0] == nullptr ||
            getInstance()->_touchStates[1] == nullptr)
        { 
            return {0,0};
        }

        return {
            (abs(_instance->_touchDragDistance.u) > TOUCH_EPSILON || _instance->_touchIsDragging) ? _instance->_touchDragDistance.u : 0 , 
            (abs(_instance->_touchDragDistance.v) > TOUCH_EPSILON || _instance->_touchIsDragging) ? _instance->_touchDragDistance.v : 0
        };
    }

    m3d::Vector2f* Input::getTouchDragOrigin()
    {
        m3d::Vector2f** states = getInstance()->_touchStates;

        if(states[0] == NULL)
        {
            return nullptr;
        }

        m3d::Vector2f * origin = new m3d::Vector2f(*(states[0]));

        return origin;
    }