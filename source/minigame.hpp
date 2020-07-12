/**
 *  @file minigame.hpp
 *  @brief Defines the minigame inherited class
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <m3dia.hpp>
#include <sstream>

#include "scene.hpp"
#include "sandbox.hpp"

#define DEBUG

#define setObjectName(name, id) ((void) 0)//executeInSandbox("name_table[\"" name "\"] = " + std::to_string(id))

class Minigame : public Scene
{
	private:
        int m_threadState = THREAD_RUNNING;
        

	protected:
		static bool winCond;
		m3d::Thread *m_sandboxThread;

	public:

		virtual bool checkWinCond() = 0;

		void toggleWinCond()
		{
			winCond = !winCond; 
		}

        /**
         *  @brief Default Constructor, should be inherited by child class constructors
         */
        Minigame()
        {                                   
            m_sandboxThread = LuaSandbox::Initialize(&m_threadState);
            
            #ifdef DEBUG
            std::stringstream t_debug;
            //t_debug << "new sandbox thread: " << m_sandboxThread ;
            Util::PrintLine(t_debug.str() ) ;
            #endif

            //m_sandboxThread->start();
        }

        /**
         *  @brief Default Destructor, should be inherited by child class destructor
         */
        ~Minigame()
        {
            //m3d::Lock lock(m_mutex_threadState);
            //m_sandboxThreadState = THREAD_CLOSE;
            //m_sandboxThread->join();
        }

		virtual void loadScene() = 0;
		virtual void loadWinScr() = 0;
		virtual void loadLoseScr() = 0;
		virtual void requestUI() = 0;
		virtual void closeGame() = 0;
	
		virtual void initialize() = 0;
		virtual void load()=0;
		virtual void unload()=0;
		virtual void update()=0;
		virtual void draw()=0;

		virtual void onEnter()=0;
		virtual void onExit()=0;
};





