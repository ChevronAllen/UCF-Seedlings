/**
 *  @file module.hpp
 *  Defines the basic behavior of a module 
 */
#pragma once

/** Module Class
 *  @brief Blocking module that runs until it's complete.
 *  Only one Module can be running at a time. While active the Game Loop doesnt run 
 *  the SceneManager.
 */
class Module
{
    bool m_init = false; /// Is set to true after initialize() is run
protected:
    bool m_finished = false; /// Is manually set to true when the module is ready to close
    virtual void initialize(); /// Runs before the first updateAction()
    virtual void updateActions(); /// Run once ber update cycle

public:
    Module(){}
    /**
     *  Base Destructor
     */
    virtual ~Module(){};

    /**
     *  Public getter for the private member m_finished 
     *  @returns returns true if the module is ready to be closed. Otherwise false.
     */
    bool isFinished(){return m_finished;}

    /**
     *  @brief update function to be run once per cycle.
     *  Manages execution of the initialize() and updateActions() functions
     */
    void onUpdate()
    {
        //  Run initialize once  
        if(!m_init)
        {
            initialize();
            m_init = true;
        }

        updateActions();
    }

    /**
     *  @brief Draw elements unique to the module.
     *  called in the main loop only while the the module is active.
     */
    virtual void onDraw();
};